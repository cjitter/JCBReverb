//==============================================================================
//
//  Copyright 2025 Juan Carlos Blancas
//  This file is part of JCBReverb and is licensed under the GNU General Public License v3.0 or later.
//
//==============================================================================

//==============================================================================
// INCLUDES
//==============================================================================
// Módulos JUCE
#include <juce_graphics/juce_graphics.h>

// Librerías estándar C++
#include <mutex>
#include <algorithm>

// Archivos del proyecto
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "Components/Windows/CreditsWindow.h"
#include "Components/Windows/CodeWindow.h"
#include "Helpers/UTF8Helper.h"
#include "BinaryData.h"

//==============================================================================
// LISTENER CLASSES IMPLEMENTATION
//==============================================================================

// Base class for parameter listeners with thread-safe GUI updates
class ParameterListenerBase : public juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit ParameterListenerBase(JCBReverbAudioProcessorEditor* e) : editor(e) {}
    virtual ~ParameterListenerBase() = default;
    
protected:
    JCBReverbAudioProcessorEditor* editor;
};

// Listener para cambios en el parámetro y_FILTERS (activación de filtros HPF/LPF)
class JCBReverbAudioProcessorEditor::SidechainParameterListener : public ParameterListenerBase
{
public:
    explicit SidechainParameterListener(JCBReverbAudioProcessorEditor* e) : ParameterListenerBase(e) {}
    void parameterChanged(const juce::String& parameterID, float newValue) override
    {
        juce::ignoreUnused(newValue);
        juce::MessageManager::callAsync([safeEditor = juce::Component::SafePointer(editor), parameterID]() {
            if (! safeEditor) return;
            if (parameterID == "y_FILTERS")
                safeEditor->updateSidechainComponentStates();
            else if (parameterID == "q_ONOFFEQ")
                safeEditor->updateEqComponentStates();
            else if (parameterID == "r_ONOFFCOMP")
                safeEditor->updateCompComponentStates();
        });
    }
};


//==============================================================================
// CONSTRUCTOR Y DESTRUCTOR
//==============================================================================
JCBReverbAudioProcessorEditor::JCBReverbAudioProcessorEditor (JCBReverbAudioProcessor& p, juce::UndoManager& um)
    : AudioProcessorEditor (&p), 
      processor (p), 
      undoManager (um),
      spectrumAnalyzer(processor.apvts),          // Inicializar spectrum analyzer
      inputMeterL([]() { return -100.0f; }),      // Safe dummy value for input meters  
      inputMeterR([]() { return -100.0f; }),      // Safe dummy value for input meters
      outputMeterL([]() { return -100.0f; }),     // Safe dummy value for output meters
      outputMeterR([]() { return -100.0f; })      // Safe dummy value for output meters
{
    // Inicializar LookAndFeel personalizado para botones
    soloButtonLAF = std::make_unique<SoloButtonLookAndFeel>();
    reversedGradientButtonLAF = std::make_unique<ReversedGradientButtonLookAndFeel>();
    tealGradientButtonLAF = std::make_unique<TealGradientButtonLookAndFeel>();
    coralGradientButtonLAF = std::make_unique<CoralGradientButtonLookAndFeel>();
    
    // Configurar todos los componentes
    setupBackground();
    setupKnobs();
    setupMeters();
    // setupSidechainControls();
    setupPresetArea();
    setupUtilityButtons();
    setupParameterButtons();
    setupRightTabs();

    // Agregar título y versión - mismo estilo que ExpansorGate
    auto titleFont = juce::Font(juce::FontOptions(22.0f));
    titleLink.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    titleLink.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    titleLink.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    titleLink.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    
    // Detectar si estamos en Logic Pro para mostrar solo la versión
    juce::String titleText;
    
    // Verificar si el host es Logic Pro
    juce::PluginHostType hostInfo;
    if (hostInfo.isLogic()) {
        titleText = "v1.0.0-alpha.2";  // Solo versión para Logic Pro
    } else {
        titleText = "JCBReverb v1.0.0-alpha.2";  // Nombre completo para otros DAWs
    }

    titleLink.setButtonText(titleText);
    // NO agregar tooltip individual - solo usar la ventana general de tooltips
    // El tooltip se actualiza dinámicamente en updateTooltips() usando getTooltipText("title")
    titleLink.setTooltip("");
    
    // Configurar el click para mostrar créditos
    titleLink.onClick = [this]() {
        showCredits();
    };
    
    addAndMakeVisible(titleLink);
    
    // Agregar analizador de espectro
    addAndMakeVisible(spectrumAnalyzer);
    spectrumAnalyzer.setVisible(true);
    
    // Agregar visualización de forma de onda
    addAndMakeVisible(waveformDisplay);
    waveformDisplay.setVisible(false);  // Inicialmente oculto, FFT es el modo por defecto

    // Agregar tooltip
    addAndMakeVisible(tooltipComponent);
    tooltipComponent.setAlwaysOnTop(true);
    tooltipComponent.showTip(JUCE_UTF8("Pasa el mouse sobre los controles\npara ver ayuda detallada"));

    // Establecer tamaño inicial con restricciones
    auto savedSize = processor.getSavedSize();
    int initialWidth = savedSize.x > 0 ? savedSize.x : DEFAULT_WIDTH;
    int initialHeight = savedSize.y > 0 ? savedSize.y : DEFAULT_HEIGHT;
    
    setSize(initialWidth, initialHeight);
    setResizable(true, true);
    
    // Inicializar el estado del tamaño basado en las dimensiones iniciales
    if (initialWidth == DEFAULT_WIDTH && initialHeight == DEFAULT_HEIGHT) {
        currentSizeState = GuiSizeState::Current;
    } else if (initialWidth == MIN_WIDTH && initialHeight == MIN_HEIGHT) {
        currentSizeState = GuiSizeState::Minimum;
    } else if (initialWidth == MAX_WIDTH && initialHeight == MAX_HEIGHT) {
        currentSizeState = GuiSizeState::Maximum;
    } else {
        // Para tamaños personalizados, usar estado Current por defecto
        currentSizeState = GuiSizeState::Current;
        lastCustomSize = {initialWidth, initialHeight};
    }

    // Establecer límites de redimensionado - valores exactos de JCBExpansorGate
    setResizeLimits(MIN_WIDTH, MIN_HEIGHT, MAX_WIDTH, MAX_HEIGHT);
    getConstrainer()->setFixedAspectRatio(ASPECT_RATIO);
    
    // Inicializar cache de contenido de código para thread safety
    initializeCodeContentCache();
    
    // Timer para resetear indicadores de clip cada cierto tiempo
    clipResetCounter = 0;

    // Configurar estado inicial del idioma
    if (processor.getTooltipLanguageEnglish()) {
        currentLanguage = TooltipLanguage::English;
        utilityButtons.tooltipLangButton.setButtonText("eng");
        utilityButtons.tooltipLangButton.setColour(juce::TextButton::textColourOffId, DarkTheme::accentSecondary);
    } else {
        currentLanguage = TooltipLanguage::Spanish;
        utilityButtons.tooltipLangButton.setButtonText("esp");
        utilityButtons.tooltipLangButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    }

    // Actualizar todos los tooltips basado en idioma inicial
    updateAllTooltips();

    // Configurar estados iniciales
    updateButtonStates();
    updateFilterButtonText();  // Establecer texto inicial de botones de filtro

    // Actualizar valores de sliders desde APVTS para evitar problemas al cargar sesión
    // Usar MessageManager::callAsync para ejecución thread-safe sin delay
    juce::MessageManager::callAsync([safeThis = juce::Component::SafePointer<JCBReverbAudioProcessorEditor>(this)]() {
        if (safeThis) {
            safeThis->updateSliderValues();
        }
    });
    
    // Configurar estado inicial del tooltip toggle y language button
    bool initialTooltipState = processor.getTooltipEnabled();
    tooltipsEnabled = initialTooltipState;
    tooltipComponent.setTooltipsEnabled(tooltipsEnabled);
    utilityButtons.tooltipToggleButton.setToggleState(tooltipsEnabled, juce::dontSendNotification);
    
    // Habilitar/deshabilitar botón de idioma según estado de tooltips
    utilityButtons.tooltipLangButton.setEnabled(tooltipsEnabled);
    utilityButtons.tooltipLangButton.setAlpha(tooltipsEnabled ? 1.0f : 0.25f);
    
    // Aplicar estados iniciales de todos los modos en el orden correcto
    //updateButtonStates();

    // CRASH FIX: Configurar las funciones reales de los medidores DESPUÉS de toda la inicialización
    // Esto evita accesos prematuros a valores atómicos del processor durante la construcción
    inputMeterL.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsInputValue(0) : -100.0f; });
    inputMeterR.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsInputValue(1) : -100.0f; });
    outputMeterL.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsOutputValue(0) : -100.0f; });
    outputMeterR.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsOutputValue(1) : -100.0f; });

    // Registrar listener para y_FILTERS (thread-safe para automatización del host)
    sidechainParameterListener = std::make_unique<SidechainParameterListener>(this);
    processor.apvts.addParameterListener("y_FILTERS", sidechainParameterListener.get());
    // También escuchar los toggles de EQ y COMP para actualizar alfa/enable
    processor.apvts.addParameterListener("q_ONOFFEQ", sidechainParameterListener.get());
    processor.apvts.addParameterListener("r_ONOFFCOMP", sidechainParameterListener.get());
    
    // Connect spectrum analyzer callback to processor
    processor.setSpectrumAnalyzerCallback([this](float sample) {
        spectrumAnalyzer.pushNextSampleIntoFifo(sample);
    });
    
    // Connect sample rate change callback
    processor.setSampleRateChangedCallback([this](double newSampleRate) {
        spectrumAnalyzer.setSampleRate(newSampleRate);
    });
    
    // Initialize spectrum analyzer with current sample rate
    spectrumAnalyzer.setSampleRate(processor.getCurrentSampleRate());

    // CRASH FIX: Iniciar timer AL FINAL para evitar acceso prematuro a valores atómicos
    // El timer debe iniciarse después de que todo esté completamente inicializado
    startTimerHz(TIMER_HZ);
    // Restaurar pestaña activa desde el estado del APVTS y aplicar visibilidad
    if (processor.apvts.state.hasProperty("ui_right_tab"))
    {
        int tab = (int) processor.apvts.state.getProperty("ui_right_tab");
        currentRightTab = (tab == 1) ? RightPanelTab::COMP : RightPanelTab::EQ;
    }
    updateRightPanelVisibility();

    // Restaurar modo de display (FFT / Waveform) desde processor.displayModeIsFFT
    if (! processor.displayModeIsFFT)
    {
        // Modo Waveform activo
        currentDisplayMode = DisplayMode::Waveform;
        spectrumAnalyzer.setVisible(false);
        waveformDisplay.setVisible(true);
        utilityButtons.runGraphicsButton.setButtonText("wave");
        utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId,
                                                  DarkTheme::accent.withAlpha(0.3f));
        utilityButtons.zoomButton.setAlpha(1.0f);
        utilityButtons.zoomButton.setEnabled(true);
        utilityButtons.zoomButton.setButtonText(waveformDisplay.getZoomEnabled() ? "zoom x2" : "zoom");
    }
    else
    {
        // Modo FFT activo
        currentDisplayMode = DisplayMode::FFT;
        spectrumAnalyzer.setVisible(true);
        waveformDisplay.setVisible(false);
        utilityButtons.runGraphicsButton.setButtonText("FFT");
        utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId,
                                                  juce::Colours::transparentBlack);
        utilityButtons.zoomButton.setAlpha(1.0f);
        utilityButtons.zoomButton.setEnabled(true);
        utilityButtons.zoomButton.setButtonText(spectrumAnalyzer.getZoomEnabled() ? "zoom x2" : "zoom");
    }
}

//==============================================================================
// IMPLEMENTACIÓN DE SOLOBUTTONLOOKANDFEEL
//==============================================================================
void JCBReverbAudioProcessorEditor::SoloButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    
    // Si el botón está activado (toggle ON), dibujar gradiente invertido basado en banda Mid
    if (auto* toggleButton = dynamic_cast<juce::TextButton*>(&button))
    {
        if (toggleButton->getToggleState())
        {
            // Usar siempre el color de banda Mid (valor fijo 1.0f) con gradiente invertido
            
            // Crear gradiente INVERTIDO para SOLO: morado intenso a la izquierda, violeta claro a la derecha
            juce::ColourGradient gradient(
                lowBandColour.interpolatedWith(highBandColour, 0.5f).withAlpha(0.15f),  // Mezcla morado a la izquierda
                bounds.getX(), bounds.getCentreY(),
                lowBandColour.withAlpha(0.20f),  // Púrpura puro a la derecha
                bounds.getRight(), bounds.getCentreY(),
                false
            );
            
            // Añadir punto intermedio para transición más suave
            gradient.addColour(0.5, lowBandColour.interpolatedWith(highBandColour, 0.25f).withAlpha(0.18f));
            
            g.setGradientFill(gradient);
            g.fillRoundedRectangle(bounds, 3.0f);
            
            // Borde sutil - usar color de banda Mid
            g.setColour(lowBandColour.interpolatedWith(highBandColour, 0.5f).withAlpha(0.3f));
            g.drawRoundedRectangle(bounds.reduced(0.5f), 3.0f, 1.0f);
        }
        else
        {
            // Botón desactivado - fondo muy sutil con gradiente tenue
            juce::ColourGradient gradient(
                lowBandColour.interpolatedWith(highBandColour, 0.5f).withAlpha(0.03f),
                bounds.getX(), bounds.getCentreY(),
                lowBandColour.withAlpha(0.05f),
                bounds.getRight(), bounds.getCentreY(),
                false
            );
            
            g.setGradientFill(gradient);
            g.fillRoundedRectangle(bounds, 3.0f);
            
            // Borde muy sutil cuando está desactivado
            g.setColour(DarkTheme::border.withAlpha(0.15f));
            g.drawRoundedRectangle(bounds.reduced(0.5f), 3.0f, 0.5f);
        }
    }
    else
    {
        // Fallback para otros tipos de botones
        g.setColour(backgroundColour);
        g.fillRoundedRectangle(bounds, 3.0f);
    }
}

//==============================================================================
// IMPLEMENTACIÓN DE REVERSEDGRADIENTBUTTONLOOKANDFEEL
//==============================================================================

void JCBReverbAudioProcessorEditor::ReversedGradientButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    
    // Si el botón está activado (toggle ON), dibujar gradiente invertido
    if (auto* toggleButton = dynamic_cast<juce::TextButton*>(&button))
    {
        if (toggleButton->getToggleState())
        {
            // Crear gradiente invertido: púrpura a la izquierda, azul a la derecha
            juce::ColourGradient gradient(
                lowBandColour.withAlpha(0.0f),   // Púrpura a la izquierda - completamente transparente
                bounds.getX(), bounds.getCentreY(),
                highBandColour.withAlpha(0.0f),  // Azul a la derecha - completamente transparente
                bounds.getRight(), bounds.getCentreY(),
                false
            );
            
            // Añadir punto intermedio para transición más suave
            gradient.addColour(0.5, 
                highBandColour.interpolatedWith(lowBandColour, 0.5f).withAlpha(0.0f));
            
            g.setGradientFill(gradient);
            g.fillRoundedRectangle(bounds, 2.0f);
            
            // Añadir borde sutil como DOWNSAMPLE y SOLO BAND
            juce::Colour borderColour = lowBandColour.interpolatedWith(highBandColour, 0.5f);
            g.setColour(borderColour.withAlpha(0.15f));  // Borde muy sutil
            g.drawRoundedRectangle(bounds.reduced(0.5f), 2.0f, 1.0f);
        }
    }
}

//==============================================================================
// IMPLEMENTACIÓN DE TEALGRADIENTBUTTONLOOKANDFEEL
//==============================================================================

void JCBReverbAudioProcessorEditor::TealGradientButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    
    // Para el botón TILT PRE/POST usar gradiente de verde agua pálido
    const juce::Colour tealColour{0xFFA6DAD5};
    
    // Siempre dibujar gradiente, independientemente del estado del toggle
    // Crear gradiente de teal: oscuro a la izquierda, claro a la derecha
    juce::ColourGradient gradient(
        tealColour.darker(0.2f).withAlpha(0.25f),   // Teal oscuro a la izquierda - más transparente
        bounds.getX(), bounds.getCentreY(),
        tealColour.brighter(0.2f).withAlpha(0.25f),  // Teal claro a la derecha - más transparente
        bounds.getRight(), bounds.getCentreY(),
        false
    );
    
    // Añadir punto intermedio para transición más suave
    gradient.addColour(0.5, 
        tealColour.withAlpha(0.20f));
    
    g.setGradientFill(gradient);
    g.fillRoundedRectangle(bounds, 2.0f);
}

//==============================================================================
// IMPLEMENTACIÓN DE CORALGRADIENTBUTTONLOOKANDFEEL
//==============================================================================

void JCBReverbAudioProcessorEditor::CoralGradientButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    
    // Si el botón está activado (toggle ON), dibujar gradiente rojo coral
    if (auto* toggleButton = dynamic_cast<juce::TextButton*>(&button))
    {
        if (toggleButton->getToggleState())
        {
            // Crear gradiente de rojo coral: oscuro a la izquierda, claro a la derecha
            juce::ColourGradient gradient(
                coralColour.darker(0.2f).withAlpha(0.15f),   // Coral oscuro a la izquierda - más transparente
                bounds.getX(), bounds.getCentreY(),
                coralColour.brighter(0.2f).withAlpha(0.15f),  // Coral claro a la derecha - más transparente
                bounds.getRight(), bounds.getCentreY(),
                false
            );
            
            // Añadir punto intermedio para transición más suave
            gradient.addColour(0.5, 
                coralColour.withAlpha(0.13f));
            
            g.setGradientFill(gradient);
            g.fillRoundedRectangle(bounds, 2.0f);
        }
    }
}


JCBReverbAudioProcessorEditor::~JCBReverbAudioProcessorEditor()
{
    // CRÍTICO: Detener timer PRIMERO para prevenir crashes durante destrucción
    stopTimer();

    processor.setSpectrumAnalyzerCallback({});
    processor.setSampleRateChangedCallback({});
    
    // Desregistrar listeners de parámetros antes de destruir
    if (sidechainParameterListener) {
        processor.apvts.removeParameterListener("y_FILTERS", sidechainParameterListener.get());
        processor.apvts.removeParameterListener("q_ONOFFEQ", sidechainParameterListener.get());
        processor.apvts.removeParameterListener("r_ONOFFCOMP", sidechainParameterListener.get());
    }

    sidechainControls.hpfSlider.setLookAndFeel(nullptr);
    sidechainControls.lpfSlider.setLookAndFeel(nullptr);
    sidechainControls.scButton.setLookAndFeel(nullptr);

    leftKnobs.reflectSlider.setLookAndFeel(nullptr);
    leftKnobs.dampSlider.setLookAndFeel(nullptr);
    leftKnobs.sizeSlider.setLookAndFeel(nullptr);
    leftKnobs.drywetSlider.setLookAndFeel(nullptr);
    leftKnobs.stSlider.setLookAndFeel(nullptr);
    leftKnobs.freezeButton.setLookAndFeel(nullptr);

    // Reset LAF for newly added right-side controls
    eqControls.lsfSlider.setLookAndFeel(nullptr);
    eqControls.pfSlider.setLookAndFeel(nullptr);
    eqControls.hsfSlider.setLookAndFeel(nullptr);
    eqControls.lsgSlider.setLookAndFeel(nullptr);
    eqControls.pgSlider.setLookAndFeel(nullptr);
    eqControls.hsgSlider.setLookAndFeel(nullptr);
    eqControls.eqOnButton.setLookAndFeel(nullptr);

    compControls.thdSlider.setLookAndFeel(nullptr);
    compControls.ratioSlider.setLookAndFeel(nullptr);
    compControls.atkSlider.setLookAndFeel(nullptr);
    compControls.relSlider.setLookAndFeel(nullptr);
    compControls.gainSlider.setLookAndFeel(nullptr);
    compControls.compOnButton.setLookAndFeel(nullptr);
    compControls.pumpButton.setLookAndFeel(nullptr);

    // Tabs (EQ/COMP)
    rightTabs.eqTab.setLookAndFeel(nullptr);
    rightTabs.compTab.setLookAndFeel(nullptr);

    // Limpiar LookAndFeel del editor principal
    setLookAndFeel(nullptr);
}

//==============================================================================
// OVERRIDES DE JUCE
//==============================================================================
void JCBReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // El background se maneja por el componente backgroundImage
}

void JCBReverbAudioProcessorEditor::paintOverChildren (juce::Graphics& g)
{
    // Usar las mismas coordenadas que la transfer function display
    float x = 460.0f * 700.0f / 1247.0f;  // ≈ 258
    float y = 73.0f * 200.0f / 353.0f + 4.0f;    // ≈ 41 + 4 píxeles
    float w = 335.0f * 700.0f / 1247.0f;  // ≈ 188
    float h = 205.0f * 200.0f / 353.0f - 5.0f;   // ≈ 116 - 5 píxeles
    auto transferBounds = getScaledBounds(x, y, w, h).toFloat();

    // Texto BYPASS
    if (isBypassed && bypassTextVisible) {
        g.setColour(juce::Colours::transparentWhite.withAlpha(0.85f));
        g.setFont(juce::Font(juce::FontOptions(transferBounds.getHeight() * 0.4f))
                  .withStyle(juce::Font::bold));
        g.drawText("BYPASS", transferBounds, juce::Justification::centred);
    }

    // Las etiquetas de BAND ahora se manejan con componentes Label separados
}

void JCBReverbAudioProcessorEditor::resized()
{
    // Guardar tamaño de ventana
    processor.setSavedSize({getWidth(), getHeight()});

    // guardar como tamaño personalizado para poder volver a él
    int currentWidth = getWidth();
    int currentHeight = getHeight();

    if (currentWidth != DEFAULT_WIDTH && currentWidth != MIN_WIDTH && currentWidth != MAX_WIDTH &&
        currentHeight != DEFAULT_HEIGHT && currentHeight != MIN_HEIGHT && currentHeight != MAX_HEIGHT) {
        // Es un tamaño personalizado - guardarlo
        lastCustomSize = {currentWidth, currentHeight};
    }

    // El background llena toda el área
    backgroundImage.setBounds(getLocalBounds());

    // === METERS CON SLIDERS DE TRIM/MAKEUP ===
    // Meters de entrada (lado izquierdo)
    inputMeterL.setBounds(getScaledBounds(2, 42, 12, 117));
    inputMeterR.setBounds(getScaledBounds(12, 42, 12, 117));

    // Slider de trim superpuesto a los meters de entrada
    trimSlider.setBounds(getScaledBounds(2, 40, 22, 130));
    // Slider de makeup superpuesto a los meters de salida
    makeupSlider.setBounds(getScaledBounds(677, 40, 22, 130));

    // Medidores de salida (lado derecho)
    outputMeterL.setBounds(getScaledBounds(677, 42, 12, 117));
    outputMeterR.setBounds(getScaledBounds(687, 42, 12, 117));
    
    // === VISUALIZACIÓN CENTRAL (SPECTRUM ANALYZER) ===
    // Posicionar componentes de visualización en el centro del plugin
    const int displayX = 260;  // Después de los knobs izquierdos
    const int displayY = 44;   // Alineado con los medidores
    const int displayW = 180;  // Ancho del área central
    const int displayH = 114;  // Altura similar a los medidores
    
    spectrumAnalyzer.setBounds(getScaledBounds(displayX, displayY, displayW, displayH));
    waveformDisplay.setBounds(getScaledBounds(displayX, displayY, displayW, displayH));

    // Posicionar HPF/LPF en la parte superior central + botón FILTERS - 285, 5, 36, 36
    sidechainControls.hpfSlider.setBounds(getScaledBounds(290, 3, 39, 39));
    sidechainControls.lpfSlider.setBounds(getScaledBounds(383, 3, 39, 39));
    {
        const int buttonWidth = 50;
        const int centerX = 355;
        sidechainControls.scButton.setBounds(getScaledBounds(centerX - buttonWidth/2, 14, buttonWidth, 15));
    }

    // Posición leftKnobs
    leftKnobs.reflectSlider.setBounds(getScaledBounds(44, 47, 53, 53));
    leftKnobs.sizeSlider.setBounds(getScaledBounds(92, 47, 53, 53));
    leftKnobs.dampSlider.setBounds(getScaledBounds(142, 47, 53, 53));

    leftKnobs.drywetSlider.setBounds(getScaledBounds(65, 102, 53, 53));
    leftKnobs.stSlider.setBounds(getScaledBounds(120, 102, 53, 53));
    leftKnobs.freezeButton.setBounds(getScaledBounds(200, 93, 55, 16));

    // === Right tabs (EQ / COMP) ===
    rightTabs.eqTab.setBounds(getScaledBounds(453, 80, 25, 16));
    rightTabs.compTab.setBounds(getScaledBounds(451, 103, 30, 16));

    // === EQ (two rows on right): top = gains, bottom = freqs ===
    // Place activation button just inside right panel, left of the 3 columns
    eqControls.eqOnButton.setBounds(getScaledBounds(485, 95, 35, 12));
    // Top row: Gains (LSG, PG, HSG)
    eqControls.lsgSlider.setBounds(getScaledBounds(510, 48, 50, 50));
    eqControls.pgSlider.setBounds (getScaledBounds(560, 48, 50, 50));
    eqControls.hsgSlider.setBounds(getScaledBounds(610, 48, 50, 50));
    // Bottom row: Freqs (LSF, PF, HSF)
    eqControls.lsfSlider.setBounds(getScaledBounds(510, 102, 50, 50));
    eqControls.pfSlider.setBounds (getScaledBounds(560, 102, 50, 50));
    eqControls.hsfSlider.setBounds(getScaledBounds(610, 102, 50, 50));

    // === COMP layer (same area; toggled by tab) ===
    compControls.compOnButton.setBounds(getScaledBounds(485, 95, 35, 12));
    compControls.pumpButton.setBounds (getScaledBounds(615, 115, 40, 15));
    // Top row: THD, RATIO, GAIN
    compControls.thdSlider.setBounds  (getScaledBounds(510, 48, 50, 50));
    compControls.ratioSlider.setBounds(getScaledBounds(560, 48, 50, 50));
    compControls.gainSlider.setBounds (getScaledBounds(610, 48, 50, 50));
    // Bottom row: ATK, REL
    compControls.atkSlider.setBounds  (getScaledBounds(510, 102, 50, 50));
    compControls.relSlider.setBounds  (getScaledBounds(560, 102, 50, 50));

    // === PRESET AREA (TOP LEFT) ===
    presetArea.saveButton.setBounds(getScaledBounds(5, 15, 20, 12));  // Alineado con undo
    presetArea.saveAsButton.setBounds(getScaledBounds(27, 15, 25, 12));
    presetArea.deleteButton.setBounds(getScaledBounds(54, 15, 25, 12));
    presetArea.backButton.setBounds(getScaledBounds(81, 15, 14, 12));
    presetArea.nextButton.setBounds(getScaledBounds(98, 15, 14, 12));
    presetArea.presetMenu.setBounds(getScaledBounds(114, 15, 95, 12));

    // Botones A/B junto al menú de preset
    topButtons.abStateButton.setBounds(getScaledBounds(213, 15, 18, 12));
    topButtons.abCopyButton.setBounds(getScaledBounds(233, 15, 22, 12));

    // === BOTONES DE UTILIDAD (INFERIOR IZQUIERDA) ===
    utilityButtons.undoButton.setBounds(getScaledBounds(30, 175, 22, 12));
    utilityButtons.redoButton.setBounds(getScaledBounds(52, 175, 22, 12));
    utilityButtons.resetGuiButton.setBounds(getScaledBounds(76, 175, 30, 12));
    utilityButtons.runGraphicsButton.setBounds(getScaledBounds(108, 175, 30, 12));
    utilityButtons.zoomButton.setBounds(getScaledBounds(140, 175, 30, 12));
    // Mover botones de tooltip y lenguaje donde estaba el diagram
    utilityButtons.tooltipToggleButton.setBounds(getScaledBounds(172, 175, 30, 12));
    utilityButtons.tooltipLangButton.setBounds(getScaledBounds(204, 175, 22, 12));

    // Botones DIAGRAM y BYPASS - Centrados en rectángulo inferior
    const int bottomButtonsY = 165;  // Fila superior del rectángulo inferior
    const int bottomCenterX = 358;  // Centro horizontal del plugin para botones inferiores
    const int totalButtonWidth = 44 + 10 + 50;  // DIAGRAM + gap + BYPASS
    const int buttonsStartX = bottomCenterX - (totalButtonWidth / 2);
    // DIAGRAM y BYPASS centrados horizontalmente
    centerButtons.diagramButton.setBounds(getScaledBounds(buttonsStartX, bottomButtonsY, 44, 12));
    parameterButtons.bypassButton.setBounds(getScaledBounds(buttonsStartX + 52, bottomButtonsY, 44, 12));

    // Calcular posición central para el grupo de botones "POR HACER"
    const int todoStartX = 503;    // Movido a la derecha para mejor centrado en el rectángulo
    const int todoY = 175;       // Mismo Y que botones de utilidad
    utilityButtons.hqButton.setBounds(getScaledBounds(todoStartX, todoY, 18, 12));
    utilityButtons.dualMonoButton.setBounds(getScaledBounds(todoStartX + 20, todoY, 23, 12));
    utilityButtons.stereoLinkedButton.setBounds(getScaledBounds(todoStartX + 45, todoY, 23, 12));
    utilityButtons.msButton.setBounds(getScaledBounds(todoStartX + 70, todoY, 18, 12));
    // Botón MIDI posicionado a la derecha del botón M/S
    utilityButtons.midiLearnButton.setBounds(getScaledBounds(todoStartX + 90, todoY, 23, 12));

    // === TÍTULO Y VERSIÓN (CENTRO INFERIOR) ===
    // Centrado debajo de los botones DIAGRAM y BYPASS
    const int titleY = 180;  // Desplazado hacia abajo para dar espacio
    const int centerX = 353;  // Centro del plugin
    titleLink.setBounds(getScaledBounds(centerX - 48, titleY, 98, 15));

    // Tooltip en esquina superior derecha - ajustado al rectángulo visible
    tooltipComponent.setBounds(getScaledBounds(448, 0, 230, 42));

    // Actualizar factor de escala del tooltip basado en el tamaño de la ventana
    float scaleFactor = (float)getWidth() / (float)DEFAULT_WIDTH;
    tooltipComponent.setScaleFactor(scaleFactor);

    // Redimensionar el overlay del diagrama si está visible
    if (diagramOverlay != nullptr)
    {
        diagramOverlay->setBounds(getLocalBounds());
        diagramOverlay->invalidateClickableAreasCache(); // Invalidar cache para regenerar con nuevas coordenadas escaladas
    }

    // Redimensionar el overlay de créditos si está visible
    if (creditsOverlay != nullptr)
    {
        creditsOverlay->setBounds(getLocalBounds());
    }

    // Redimensionar y reposicionar la ventana de código si está visible
    if (codeWindow != nullptr && codeWindow->isVisible())
    {
        // Recalcular tamaño responsivo
        int windowWidth = static_cast<int>(getWidth() * 0.35f);
        int windowHeight = static_cast<int>(getHeight() * 0.50f);

        // Limitar tamaños
        windowWidth = juce::jlimit(350, 600, windowWidth);
        windowHeight = juce::jlimit(250, 450, windowHeight);

        // Recentrar la ventana
        int x = getWidth() / 2 - windowWidth / 2;
        int y = getHeight() / 2 - windowHeight / 2;

        codeWindow->setBounds(x, y, windowWidth, windowHeight);
    }
}

void JCBReverbAudioProcessorEditor::timerCallback()
{
    // CRASH FIX: Verificar que el processor esté completamente inicializado
    // antes de acceder a valores atómicos
    if (!processor.isInitialized()) {
        return;
    }

    // Sistema universal de decay para todos los DAWs
    applyMeterDecayIfNeeded();
    
    // Actualizar visualización de forma de onda si está en modo Waveform
    if (currentDisplayMode == DisplayMode::Waveform)
    {
        std::vector<float> inputSamples, processedSamples;
        processor.getWaveformData(inputSamples, processedSamples);
        waveformDisplay.updateWaveformData(inputSamples, processedSamples);
        
        // Actualizar parámetros de visualización
        if (auto* dryWetParam = processor.apvts.getRawParameterValue("b_DRYWET"))
        {
            // APVTS devuelve 0..1 (ya normalizado). No dividir por 100.
            waveformDisplay.setDryWetMix(dryWetParam->load());
        }
        
        if (auto* sizeParam = processor.apvts.getRawParameterValue("e_SIZE"))
        {
            waveformDisplay.setReverbSize(sizeParam->load());  // Ya está en rango 0-1
        }
        
        if (auto* reflectParam = processor.apvts.getRawParameterValue("c_REFLECT"))
        {
            waveformDisplay.setReflectAmount(reflectParam->load());  // Ya está en rango 0-1
        }

        // Indicar FREEZE para resaltar la cola en la visualización
        if (auto* freezeParam = processor.apvts.getRawParameterValue("g_FREEZE"))
        {
            waveformDisplay.setFreeze(freezeParam->load() > 0.5f);
        }

        // DAMP
        if (auto* dampParam = processor.apvts.getRawParameterValue("d_DAMP"))
        {
            waveformDisplay.setDampAmount(dampParam->load());
        }
    }

    updateMeters();

    // Actualizar estado visual de botones undo/redo
    bool canUndo = undoManager.canUndo();
    bool canRedo = undoManager.canRedo();

    // Actualizar apariencia del botón undo
    utilityButtons.undoButton.setEnabled(canUndo);
    utilityButtons.undoButton.setAlpha(canUndo ? 1.0f : 0.3f);
    utilityButtons.undoButton.setColour(juce::TextButton::textColourOffId,
                                       canUndo ? DarkTheme::textPrimary : DarkTheme::textSecondary);

    // Actualizar apariencia del botón redo
    utilityButtons.redoButton.setEnabled(canRedo);
    utilityButtons.redoButton.setAlpha(canRedo ? 1.0f : 0.3f);
    utilityButtons.redoButton.setColour(juce::TextButton::textColourOffId,
                                       canRedo ? DarkTheme::textPrimary : DarkTheme::textSecondary);

    // Actualizar texto y tooltip del botón A/B copy dinámicamente
    if (processor.getIsStateA()) {
        topButtons.abCopyButton.setButtonText("A-B");
        topButtons.abCopyButton.setTooltip(getTooltipText("abcopyatob"));
    } else {
        topButtons.abCopyButton.setButtonText("B-A");
        topButtons.abCopyButton.setTooltip(getTooltipText("abcopybtoa"));
    }

    // Resetear indicadores de clip cada 3 segundos (180 frames a 60Hz)
    clipResetCounter++;
    if (clipResetCounter >= 180) {
        processor.resetClipIndicators();
        clipResetCounter = 0;
    }

    // Pasar el estado de Logic parado al display
    // Determinar si el procesamiento está inactivo
    // Usar sistema híbrido optimizado (timestamp + playhead + audio tail)
    bool isProcessingInactive = !processor.isPlaybackActive();

    // bool isProcessingInactive = processor.getIsLogicStopped();

    // Actualizar datos de waveform y obtener gain reduction para el medidor
    if (!isBypassed && !isProcessingInactive)
    {
            // DISTORTION: No hay gain reduction - eliminar else branch
    }
    else
    {
        // Si está en bypass o Logic está parado, no hay reducción
        maxGainReductionFromBuffer = 0.0f;
    }

    // Debug overlay: update counters each frame (lightweight atomics)
    //{
        //const int fs = processor.getDiagFailsafeCount();
        //const int rs = processor.getDiagGenResets();
        //debugLabel.setText(juce::String::formatted("FS:%d  RS:%d", fs, rs), juce::dontSendNotification);
    //}
}

void JCBReverbAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &utilityButtons.undoButton)
    {
        undoManager.undo();
    }
    else if (button == &utilityButtons.redoButton)
    {
        undoManager.redo();
    }
    else if (button == &utilityButtons.resetGuiButton)
    {
        // Resetear tamaño de GUI, no parámetros
        resetGuiSize();
    }
    else if (button == &parameterButtons.bypassButton)
    {
        const bool bypassActive = parameterButtons.bypassButton.getToggleState();
        if (bypassActive) {
            // // BYPASS desactiva SOLO SC y DIAGRAM
            // if (centerButtons.diagramButton.getToggleState()) {
            //     centerButtons.diagramButton.setToggleState(false, juce::dontSendNotification);
            //     hideDiagram();
            // }
        }
        updateButtonStates();

        // Reactivar control de bypass interno de Gen: z_BYPASS (sin smoothing en Gen)
        if (auto* st = processor.getPluginState())
        {
            for (int i = 0; i < JCBReverb::num_params(); ++i)
            {
                if (juce::String(JCBReverb::getparametername(st, i)) == "z_BYPASS")
                {
                    JCBReverb::setparameter(st, i, bypassActive ? 1.f : 0.f, nullptr);
                    break;
                }
            }
        }

        // UI: actualizar estado visual de medidores en modo bypass
        outputMeterL.setBypassMode(bypassActive);
        outputMeterR.setBypassMode(bypassActive);
    }
    else if (button == &sidechainControls.scButton)
    {
        // Actualizar estado visual de sliders HPF/LPF inmediatamente para clicks manuales
        updateSidechainComponentStates();
    }
    else if (button == &rightTabs.eqTab)
    {
        currentRightTab = RightPanelTab::EQ;
        updateRightPanelVisibility();
        processor.apvts.state.setProperty("ui_right_tab", 0, nullptr);
    }
    else if (button == &rightTabs.compTab)
    {
        currentRightTab = RightPanelTab::COMP;
        updateRightPanelVisibility();
        processor.apvts.state.setProperty("ui_right_tab", 1, nullptr);
    }
    else if (button == &eqControls.eqOnButton)
    {
        updateEqComponentStates();
    }
    else if (button == &compControls.compOnButton)
    {
        updateCompComponentStates();
    }
    else if (button == &compControls.pumpButton)
    {
        // Sincronizar explícitamente el parámetro x_PUMP con el estado del botón
        if (auto* pumpParam = processor.apvts.getParameter("x_PUMP"))
        {
            if (auto* boolParam = dynamic_cast<juce::AudioParameterBool*>(pumpParam))
                boolParam->setValueNotifyingHost(compControls.pumpButton.getToggleState() ? 1.0f : 0.0f);
        }
    }
    else if (button == &leftKnobs.freezeButton)
    {
        // No se requiere acción adicional, el attachment maneja el parámetro
    }
    else if (button == &utilityButtons.runGraphicsButton)
    {
        toggleDisplayMode();
    }
    // Botones de gestión de presets
    else if (button == &presetArea.saveButton)
    {
        // Desactivar botones momentáneos antes de guardar
        parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
            // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);
        savePresetFile();
    }
    else if (button == &presetArea.saveAsButton)
    {
        // Desactivar botones momentáneos antes de guardar
        parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
            // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);
        saveAsPresetFile();
    }
    else if (button == &presetArea.deleteButton)
    {
        // Desactivar botones momentáneos antes de mostrar el diálogo
        parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
            // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);
        deletePresetFile();
    }
    else if (button == &presetArea.backButton)
    {
        // Desactivar botones momentáneos antes de cambiar preset
        parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
            // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);
        selectPreviousPreset();
    }
    else if (button == &presetArea.nextButton)
    {
        // Desactivar botones momentáneos antes de cambiar preset
        parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
            // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);
        selectNextPreset();
    }
    else if (button == &utilityButtons.tooltipToggleButton)
    {
        // Alternar visibilidad del tooltip
        tooltipsEnabled = utilityButtons.tooltipToggleButton.getToggleState();
        tooltipComponent.setTooltipsEnabled(tooltipsEnabled);

        // Guardar estado del tooltip al processor
        processor.setTooltipEnabled(tooltipsEnabled);

        // Habilitar/deshabilitar botón de idioma basado en estado del tooltip
        utilityButtons.tooltipLangButton.setEnabled(tooltipsEnabled);
        utilityButtons.tooltipLangButton.setAlpha(tooltipsEnabled ? 1.0f : 0.25f);
    }
    else if (button == &utilityButtons.tooltipLangButton)
    {
        // Alternar idioma
        currentLanguage = (currentLanguage == TooltipLanguage::Spanish) ?
                         TooltipLanguage::English : TooltipLanguage::Spanish;

        // Actualizar texto del botón
        utilityButtons.tooltipLangButton.setButtonText(
            currentLanguage == TooltipLanguage::Spanish ? "esp" : "eng");

        // Actualizar color del botón basado en el idioma
        if (currentLanguage == TooltipLanguage::English) {
            // Color azul para inglés
            utilityButtons.tooltipLangButton.setColour(juce::TextButton::textColourOffId, DarkTheme::accentSecondary);
        } else {
            // Color por defecto para español
            utilityButtons.tooltipLangButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
        }

        // Guardar preferencia de idioma
        processor.setTooltipLanguageEnglish(currentLanguage == TooltipLanguage::English);

        // Actualizar todos los tooltips con el nuevo idioma
        updateAllTooltips();
        // Por botones "por hacer"
        updateTodoButtonTexts();
    }
    else if (button == &utilityButtons.hqButton)
    {
        // POR HACER: Implementar oversampling HQ
    }
    else if (button == &utilityButtons.dualMonoButton)
    {
        // Manejar exclusividad de botones de modo estéreo
        if (utilityButtons.dualMonoButton.getToggleState())
        {
            // utilityButtons.stereoLinkedButton.setToggleState(false, juce::dontSendNotification); // LINK siempre está activo
            utilityButtons.msButton.setToggleState(false, juce::dontSendNotification);
        }
    }
    /* Botón LINK siempre está ON y deshabilitado - no necesita manejador
    else if (button == &utilityButtons.stereoLinkedButton)
    {
        // Manejar exclusividad de botones de modo estéreo
        if (utilityButtons.stereoLinkedButton.getToggleState())
        {
            utilityButtons.dualMonoButton.setToggleState(false, juce::dontSendNotification);
            utilityButtons.msButton.setToggleState(false, juce::dontSendNotification);
        }
    }
    */
    else if (button == &utilityButtons.msButton)
    {

        // Manejar exclusividad de botones de modo estéreo
        if (utilityButtons.msButton.getToggleState())
        {
            utilityButtons.dualMonoButton.setToggleState(false, juce::dontSendNotification);
            // utilityButtons.stereoLinkedButton.setToggleState(false, juce::dontSendNotification); // LINK siempre está activo
        }
    }
    else if (button == &topButtons.abStateButton)
    {

        // Alternar estado A/B
        processor.toggleAB();

        // Actualizar texto del botón para mostrar estado actual
        topButtons.abStateButton.setButtonText(processor.getIsStateA() ? "A" : "B");

        // Retroalimentación visual con colores más evidentes
        if (processor.getIsStateA()) {
            // A = Púrpura/Violeta
            topButtons.abStateButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff9E35B0));  // Purple
            topButtons.abStateButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xff9E35B0));  // Mismo color para evitar brillo
            topButtons.abStateButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
        } else {
            // B = Azul
            topButtons.abStateButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2196f3));  // Blue
            topButtons.abStateButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xff2196f3));  // Mismo color para evitar brillo
            topButtons.abStateButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
        }

        repaint();
    }
    else if (button == &topButtons.abCopyButton)
    {
        // Copiar estado actual al otro
        if (processor.getIsStateA()) {
            processor.copyAtoB();
            // Retroalimentación visual - destello púrpura a azul
            topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2196f3));  // Destello azul
            topButtons.abCopyButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
            // Usar SafePointer para prevenir crashes si el editor se destruye antes de que se dispare el timer
            juce::Component::SafePointer<JCBReverbAudioProcessorEditor> safeThis(this);
            juce::Timer::callAfterDelay(300, [safeThis]() {
                if (safeThis) {
                    safeThis->topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
                    safeThis->topButtons.abCopyButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
                }
            });
        } else {
            processor.copyBtoA();
            // Retroalimentación visual - destello azul a púrpura
            topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff9E35B0));  // Destello púrpura
            topButtons.abCopyButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
            // Usar SafePointer para prevenir crashes si el editor se destruye antes de que se dispare el timer
            juce::Component::SafePointer<JCBReverbAudioProcessorEditor> safeThis(this);
            juce::Timer::callAfterDelay(300, [safeThis]() {
                if (safeThis) {
                    safeThis->topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
                    safeThis->topButtons.abCopyButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
                }
            });
        }
    }
    else if (button == &utilityButtons.midiLearnButton)
    {
        //POR HACER: Implementar modo MIDI learn
    }
    else if (button == &utilityButtons.zoomButton)
    {
        // Zoom functionality depending on display mode
        if (currentDisplayMode == DisplayMode::FFT)
        {
            // FFT zoom functionality - toggle zoom range
            bool currentZoom = spectrumAnalyzer.getZoomEnabled();
            bool newZoom = !currentZoom;

            spectrumAnalyzer.setZoomEnabled(newZoom);

            if (newZoom)
            {
                utilityButtons.zoomButton.setButtonText("zoom x2");
                utilityButtons.zoomButton.setToggleState(true, juce::dontSendNotification);
            }
            else
            {
                utilityButtons.zoomButton.setButtonText("zoom");
                utilityButtons.zoomButton.setToggleState(false, juce::dontSendNotification);
            }
        }
        else if (currentDisplayMode == DisplayMode::Waveform)
        {
            // Waveform zoom functionality - toggle vertical zoom
            bool currentZoom = waveformDisplay.getZoomEnabled();
            bool newZoom = !currentZoom;

            waveformDisplay.setZoomEnabled(newZoom);

            if (newZoom)
            {
                utilityButtons.zoomButton.setButtonText("zoom x2");
                utilityButtons.zoomButton.setToggleState(true, juce::dontSendNotification);
            }
            else
            {
                utilityButtons.zoomButton.setButtonText("zoom");
                utilityButtons.zoomButton.setToggleState(false, juce::dontSendNotification);
            }
        }
    }
    else if (button == &centerButtons.diagramButton)
    {
        // Anti-rebote para evitar clicks múltiples
        juce::uint32 currentTime = juce::Time::getMillisecondCounter();
        if (currentTime - lastDiagramButtonTime < DIAGRAM_BUTTON_DEBOUNCE_MS)
        {
            return;  // Ignorar clicks muy rápidos
        }
        lastDiagramButtonTime = currentTime;

        // Alternar diagrama basado en visibilidad actual
        bool diagramWillBeActivated = (diagramOverlay == nullptr || !diagramOverlay->isVisible());

        // Comportamiento exclusivo: solo desactivar otros cuando DIAGRAM se va a activar
        if (diagramWillBeActivated) {
            // DIAGRAM desactiva BYPASS y SOLO SC cuando se activa
            parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
                        // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);
        }

        // Ejecutar el alternado
        if (diagramOverlay != nullptr && diagramOverlay->isVisible())
        {
            hideDiagram();
        }
        else
        {
            showDiagram();
        }
    }
}

//==============================================================================
// PARAMETER LISTENER - Sincronización con automatización del HOST
//==============================================================================

void JCBReverbAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{
}

//==============================================================================
// MANEJO DE PARÁMETROS Y EVENTOS
//==============================================================================
//==============================================================================
// GESTIÓN DE ESTADO DE PARÁMETROS
//==============================================================================
void JCBReverbAudioProcessorEditor::handleParameterChange()
{
    // No hacer nada si estamos cargando un preset
    if (isLoadingPreset) {
        return;
    }

    if (presetArea.presetMenu.getSelectedId() > 0) {
        // Un preset está seleccionado del menú - deseleccionar y mostrar con asterisco
        juce::String currentPresetName = presetArea.presetMenu.getText();

        presetArea.presetMenu.setSelectedId(0);
        processor.setLastPreset(0);

        // Mostrar el nombre del preset con asterisco en cursiva
        auto modifiedText = currentPresetName + "*";
        presetArea.presetMenu.setTextWhenNothingSelected(modifiedText);
        presetArea.presetMenu.setTextItalic(true);

        // Guardar el estado visual en el processor
        processor.setPresetDisplayText(modifiedText);
        processor.setPresetTextItalic(true);

    } else {
        // No hay preset seleccionado - verificar el texto actual
        juce::String currentText = presetArea.presetMenu.getTextWhenNothingSelected();

        // Si está vacío, no hacer nada
        if (currentText.isEmpty()) {
            presetArea.presetMenu.setTextWhenNothingSelected("");
            presetArea.presetMenu.setTextItalic(false);
            processor.setPresetDisplayText("");
            processor.setPresetTextItalic(false);
        }
        // Si es DEFAULT, permitir que se marque como modificado
        else if (currentText == "DEFAULT") {
            auto modifiedText = "DEFAULT*";
            presetArea.presetMenu.setTextWhenNothingSelected(modifiedText);
            presetArea.presetMenu.setTextItalic(true);
            processor.setPresetDisplayText(modifiedText);
            processor.setPresetTextItalic(true);
        }
        // Si ya tiene asterisco, no hacer nada más
        else if (!currentText.endsWith("*")) {
            // Agregar asterisco al preset no seleccionado
            auto modifiedText = currentText + "*";
            presetArea.presetMenu.setTextWhenNothingSelected(modifiedText);
            presetArea.presetMenu.setTextItalic(true);

            // Guardar el estado visual en el processor
            processor.setPresetDisplayText(modifiedText);
            processor.setPresetTextItalic(true);
        }
    }

    // No crear UI aquí. Solo actualizar estados visuales si es necesario.
}

//==============================================================================
// MÉTODOS DE SETUP Y CONFIGURACIÓN
//==============================================================================
void JCBReverbAudioProcessorEditor::setupKnobs()
{
    // === FILTROS DE ENTRADA ===
    // Slider HPF
    sidechainControls.hpfSlider.setName("hpf");
    sidechainControls.hpfSlider.setComponentID("hpf");
    sidechainControls.hpfSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sidechainControls.hpfSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, 16);
    sidechainControls.hpfSlider.setLookAndFeel(&sliderLAFBig);  // Usar LAF grande como ExpansorGate
    sidechainControls.hpfSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.hpfSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.hpfSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    sidechainControls.hpfSlider.setTextBoxIsEditable(true);
    sidechainControls.hpfSlider.setEnabled(true);  // Inicialmente habilitado
    sidechainControls.hpfSlider.setAlpha(1.0f);  // Inicialmente visible
    sidechainControls.hpfSlider.setDoubleClickReturnValue(true, 100.0f);  // Default 100 Hz
    sidechainControls.hpfSlider.setPopupDisplayEnabled(false, false, this);
    sidechainControls.hpfSlider.setNumDecimalPlacesToDisplay(0);
    // Formato de texto personalizado para frecuencia
    sidechainControls.hpfSlider.textFromValueFunction = [](double value) {
        if (value < 1000.0)
            return juce::String(static_cast<int>(value));
        else
            return juce::String(value / 1000.0, 1) + "k";
    };
    sidechainControls.hpfSlider.setTextValueSuffix(" Hz");
    sidechainControls.hpfSlider.setRange(20.0, 5000.0, 1.0);
    sidechainControls.hpfSlider.setSkewFactorFromMidPoint(500.0);  // 500 Hz en el centro visual
    addAndMakeVisible(sidechainControls.hpfSlider);
    if (auto* param = processor.apvts.getParameter("l_HPF"))
    {
        sidechainControls.hpfAttachment = std::make_unique<CustomSliderAttachment>(
            *param, sidechainControls.hpfSlider, &undoManager);
        sidechainControls.hpfAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    // Slider LPF
    sidechainControls.lpfSlider.setName("lpf");
    sidechainControls.lpfSlider.setComponentID("lpf");
    sidechainControls.lpfSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sidechainControls.lpfSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, 16);
    sidechainControls.lpfSlider.setLookAndFeel(&sliderLAFBig);  // Usar LAF grande como ExpansorGate
    sidechainControls.lpfSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.lpfSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.lpfSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    sidechainControls.lpfSlider.setTextBoxIsEditable(true);
    sidechainControls.lpfSlider.setEnabled(true);  // Inicialmente habilitado
    sidechainControls.lpfSlider.setAlpha(1.0f);  // Inicialmente visible
    sidechainControls.lpfSlider.setDoubleClickReturnValue(true, 12000.0f);  // Nuevo default 5kHz
    sidechainControls.lpfSlider.setPopupDisplayEnabled(false, false, this);
    sidechainControls.lpfSlider.setNumDecimalPlacesToDisplay(0);
    // Formato de texto personalizado para frecuencia
    sidechainControls.lpfSlider.textFromValueFunction = [](double value) {
        if (value < 1000.0)
            return juce::String(static_cast<int>(value));
        else
            return juce::String(value / 1000.0, 1) + "k";
    };
    sidechainControls.lpfSlider.setTextValueSuffix(" Hz");
    sidechainControls.lpfSlider.setRange(100.0, 20000.0, 1.0);
    sidechainControls.lpfSlider.setSkewFactorFromMidPoint(5000.0);  // 5kHz en el centro
    addAndMakeVisible(sidechainControls.lpfSlider);
    if (auto* param = processor.apvts.getParameter("k_LPF"))
    {
        sidechainControls.lpfAttachment = std::make_unique<CustomSliderAttachment>(
            *param, sidechainControls.lpfSlider, &undoManager);
        sidechainControls.lpfAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    // Botón FILTERS (antes SC) - VISIBLE para activar/desactivar filtros
    sidechainControls.scButton.setClickingTogglesState(true);
    sidechainControls.scButton.setLookAndFeel(&smallButtonLAF);  // Usar LAF básico
    sidechainControls.scButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    sidechainControls.scButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Ahora manejado por LAF
    sidechainControls.scButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    sidechainControls.scButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    sidechainControls.scButton.addListener(this);
    addAndMakeVisible(sidechainControls.scButton);
    sidechainControls.scAttachment = std::make_unique<UndoableButtonAttachment>(
        *processor.apvts.getParameter("y_FILTERS"), sidechainControls.scButton, &undoManager);
    sidechainControls.scAttachment->onParameterChange = [this]()
    {
        handleParameterChange();
    };

    // Establecer estado inicial de los filtros
    updateSidechainComponentStates();

    // === PARTE IZQUIERDA ===
    // === REFLECT (c_REFLECT) === (exact MODE styling with new range and % display)
    leftKnobs.reflectSlider.setComponentID("reflect");
    leftKnobs.reflectSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftKnobs.reflectSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 100, 16);
    leftKnobs.reflectSlider.setLookAndFeel(&sliderLAFBig);
    leftKnobs.reflectSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftKnobs.reflectSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);
    leftKnobs.reflectSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFFFFFF));
    leftKnobs.reflectSlider.setRange(0.1, 1.0, 0.01);
    leftKnobs.reflectSlider.setSkewFactorFromMidPoint(0.77);  // 0.77 aparece en la mitad del knob
    leftKnobs.reflectSlider.setDoubleClickReturnValue(true, 0.766); // 74 % visual
    leftKnobs.reflectSlider.setPopupDisplayEnabled(false, false, this);
    leftKnobs.reflectSlider.setTextBoxIsEditable(true);
    leftKnobs.reflectSlider.setNumDecimalPlacesToDisplay(0);
    leftKnobs.reflectSlider.textFromValueFunction = [](double value) {
        const double pct = juce::jlimit(0.0, 1.0, (value - 0.1) / (1.0 - 0.1));
        const int p = juce::roundToInt(pct * 100.0);
        return juce::String(p) + " %";
    };
    leftKnobs.reflectSlider.valueFromTextFunction = [](const juce::String& text) {
        auto t = text.trim();
        if (t.endsWith("%")) t = t.dropLastCharacters(1).trim();
        const double p = juce::jlimit(0.0, 100.0, t.getDoubleValue());
        return 0.1 + (p / 100.0) * (1.0 - 0.1);
    };
    leftKnobs.reflectSlider.setTooltip(getTooltipText("reflect"));
    addAndMakeVisible(leftKnobs.reflectSlider);
    if (auto* paramReflect = processor.apvts.getParameter("c_REFLECT"))
    {
        leftKnobs.reflectAttachment = std::make_unique<CustomSliderAttachment>(
            *paramReflect, leftKnobs.reflectSlider, &undoManager);
        leftKnobs.reflectAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    leftKnobs.sizeSlider.setComponentID("size");
    leftKnobs.sizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftKnobs.sizeSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    leftKnobs.sizeSlider.setLookAndFeel(&sliderLAFBig);
    leftKnobs.sizeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftKnobs.sizeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFFFFFF));    leftKnobs.sizeSlider.setDoubleClickReturnValue(true, 1.5);  // Valor por defecto 1.5
    leftKnobs.sizeSlider.setPopupDisplayEnabled(false, false, this);
    leftKnobs.sizeSlider.setTextBoxIsEditable(true);
    leftKnobs.sizeSlider.setNumDecimalPlacesToDisplay(1);
    leftKnobs.sizeSlider.setRange(0.1, 4.0, 0.01);
    leftKnobs.sizeSlider.setSkewFactorFromMidPoint(1.0); // Concentrar rango útil en valores bajos
    addAndMakeVisible(leftKnobs.sizeSlider);
    if (auto* param = processor.apvts.getParameter("e_SIZE"))
    {
        leftKnobs.sizeAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftKnobs.sizeSlider, &undoManager);
        leftKnobs.sizeAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    leftKnobs.drywetSlider.setComponentID("drywet");
    leftKnobs.drywetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftKnobs.drywetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    leftKnobs.drywetSlider.setLookAndFeel(&sliderLAFBig);
    leftKnobs.drywetSlider.setTextBoxIsEditable(true);
    leftKnobs.drywetSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftKnobs.drywetSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFB1CAF6));  // Azul pálido como output
    leftKnobs.drywetSlider.setDoubleClickReturnValue(true, 0.5);  // Default: 100% (o_DRYWET = 1.0)
    leftKnobs.drywetSlider.setPopupDisplayEnabled(false, false, this);
    leftKnobs.drywetSlider.setRange(0.0, 1.0, 0.01);  // Rango interno 0.0-1.0
    leftKnobs.drywetSlider.textFromValueFunction = [](double value) {
        return juce::String(static_cast<int>(value * 101)) + " %";
    };
    leftKnobs.drywetSlider.valueFromTextFunction = [](const juce::String& text) {
        auto trimmed = text.trim();
        // Eliminar símbolo de porcentaje si existe
        if (trimmed.endsWith("%"))
            trimmed = trimmed.dropLastCharacters(1).trim();

        // Convertir a número y normalizar de 0-100 a 0-1
        auto percentage = trimmed.getDoubleValue();
        return juce::jlimit(0.0, 1.0, percentage / 100.0);
    };
    addAndMakeVisible(leftKnobs.drywetSlider);
    if (auto* param = processor.apvts.getParameter("b_DRYWET"))
    {
        leftKnobs.drywetAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftKnobs.drywetSlider, &undoManager);
        leftKnobs.drywetAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    leftKnobs.dampSlider.setComponentID("damp");
    leftKnobs.dampSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftKnobs.dampSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    leftKnobs.dampSlider.setLookAndFeel(&sliderLAFBig);
    leftKnobs.dampSlider.setTextBoxIsEditable(true);
    leftKnobs.dampSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftKnobs.dampSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFFFFFF));
    leftKnobs.dampSlider.setRange(0.1, 0.95, 0.01);
    leftKnobs.dampSlider.setDoubleClickReturnValue(true, 0.10);    // 0% visual (Gen 0.1)
    leftKnobs.dampSlider.setPopupDisplayEnabled(false, false, this);
    // Funciones de conversión para mostrar porcentajes
    leftKnobs.dampSlider.textFromValueFunction = [](double value) {
        const double pct = juce::jlimit(0.0, 1.0, (value - 0.1) / (0.95 - 0.1));
        const int p = juce::roundToInt(pct * 100.0);
        return juce::String(p) + " %";
    };
    leftKnobs.dampSlider.valueFromTextFunction = [](const juce::String& text) {
        juce::String cleanText = text.trimEnd().upToLastOccurrenceOf("%", false, false);
        double pct = juce::jlimit(0.0, 100.0, cleanText.getDoubleValue()) / 100.0;
        return 0.1 + pct * (0.95 - 0.1);
    };

    addAndMakeVisible(leftKnobs.dampSlider);
    if (auto* param = processor.apvts.getParameter("d_DAMP"))
    {
        leftKnobs.dampAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftKnobs.dampSlider, &undoManager);
        leftKnobs.dampAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    leftKnobs.stSlider.setComponentID("stereo");
    leftKnobs.stSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftKnobs.stSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
    leftKnobs.stSlider.setLookAndFeel(&sliderLAFBig);

    leftKnobs.stSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftKnobs.stSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFB1CAF6));  // Azul pálido como output

    leftKnobs.stSlider.setTextBoxIsEditable(true);
    leftKnobs.stSlider.setEnabled(true);
    leftKnobs.stSlider.setDoubleClickReturnValue(true, 0.425f);
    leftKnobs.stSlider.setPopupDisplayEnabled(false, false, this);
    // Range aligned to parameter: 0..0.85. Paso 0.005 permite 0.425 exacto
    leftKnobs.stSlider.setRange(0.0, 0.85, 0.005);
    //leftKnobs.stSlider.setSkewFactorFromMidPoint(0.5);
    // Funciones de conversión para mostrar porcentajes
    leftKnobs.stSlider.setTextValueSuffix({}); // sin sufijo; lo añadimos nosotros
    leftKnobs.stSlider.textFromValueFunction = [](double v)
    {
        const double maxV = 0.85;
        // Snap al 50% para evitar mostrar 51% por redondeos
        if (std::abs(v - 0.425) < 1.0e-3) {
            return juce::String(50) + " %";
        }
        double pct = (v / maxV) * 100.0;
        int ipct = juce::roundToInt(pct + 1.0e-6);
        ipct = juce::jlimit(0, 100, ipct);
        return juce::String(ipct) + " %";
    };
    leftKnobs.stSlider.valueFromTextFunction = [](const juce::String& text)
    {
        // extraer número de "42 %" o "42"
        double pct = text.retainCharacters("0123456789.-").getDoubleValue();
        pct = juce::jlimit(0.0, 100.0, pct);
        return (pct / 100.0) * 0.85; // devolvemos 0..0.85
    };


    addAndMakeVisible(leftKnobs.stSlider);
    if (auto* param = processor.apvts.getParameter("f_ST"))
    {
        leftKnobs.stAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftKnobs.stSlider, &undoManager);
        leftKnobs.stAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    leftKnobs.freezeButton.setClickingTogglesState(true);
    leftKnobs.freezeButton.setLookAndFeel(&smallButtonLAF);  // Usar LAF básico
    leftKnobs.freezeButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    leftKnobs.freezeButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    leftKnobs.freezeButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    // Cuando FREEZE está activo, colorear el texto en #36C0A6
    leftKnobs.freezeButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFF36C0A6));
    leftKnobs.freezeButton.addListener(this);
    addAndMakeVisible(leftKnobs.freezeButton);
    leftKnobs.freezeAttachment = std::make_unique<UndoableButtonAttachment>(
        *processor.apvts.getParameter("g_FREEZE"), leftKnobs.freezeButton, &undoManager);
    leftKnobs.freezeAttachment->onParameterChange = [this]() { handleParameterChange(); };

    // === EQ CONTROLS (top-right) ===
    // EQ ON button (q_ONOFFEQ)
    eqControls.eqOnButton.setClickingTogglesState(true);
    eqControls.eqOnButton.setLookAndFeel(&smallButtonLAF);
    eqControls.eqOnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    eqControls.eqOnButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    // Texto del activador EQ: ON morado #8F86D0; OFF blanco pálido (alfa 0.5)
    eqControls.eqOnButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.5f));
    eqControls.eqOnButton.setColour(juce::TextButton::textColourOnId,  juce::Colour(0xFF8F86D0));
    eqControls.eqOnButton.addListener(this);
    addAndMakeVisible(eqControls.eqOnButton);
    if (auto* paramEQ = processor.apvts.getParameter("q_ONOFFEQ"))
    {
        eqControls.eqOnAttachment = std::make_unique<UndoableButtonAttachment>(*paramEQ, eqControls.eqOnButton, &undoManager);
        eqControls.eqOnAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    // Asegurar que el botón quede por encima de la malla FFT para clics
    eqControls.eqOnButton.toFront(true);

    auto setupHzSlider = [this](CustomSlider& s, const char* paramID, double dblClick, std::unique_ptr<CustomSliderAttachment>& outAtt) {
        s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
        s.setLookAndFeel(&sliderLAFBig);
        s.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        s.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFFFFFF));
        s.setDoubleClickReturnValue(true, dblClick);
        s.setPopupDisplayEnabled(false, false, this);
        s.setNumDecimalPlacesToDisplay(0);
        s.textFromValueFunction = [](double value) {
            if (value < 1000.0) return juce::String(static_cast<int>(value));
            return juce::String(value / 1000.0, 1) + "k";
        };
        s.setTextValueSuffix(" Hz");
        addAndMakeVisible(s);
        if (auto* param = processor.apvts.getParameter(paramID))
        {
            outAtt = std::make_unique<CustomSliderAttachment>(*param, s, &undoManager);
            outAtt->onParameterChange = [this]() { handleParameterChange(); };
        }
    };

    auto setupDbSlider = [this](CustomSlider& s, const char* paramID, double dblClick, std::unique_ptr<CustomSliderAttachment>& outAtt) {
        s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, 16);
        s.setLookAndFeel(&sliderLAFBig);
        s.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        s.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFFFFFF));
        s.setDoubleClickReturnValue(true, dblClick);
        s.setPopupDisplayEnabled(false, false, this);
        s.setNumDecimalPlacesToDisplay(0);
        s.setTextValueSuffix(" dB");
        addAndMakeVisible(s);
        if (auto* param = processor.apvts.getParameter(paramID))
        {
            outAtt = std::make_unique<CustomSliderAttachment>(*param, s, &undoManager);
            outAtt->onParameterChange = [this]() { handleParameterChange(); };
        }
    };

    // EQ frequencies
    setupHzSlider(eqControls.lsfSlider, "n_LOWFREQ", 250.0, eqControls.lsfAttachment);
    setupHzSlider(eqControls.pfSlider,  "o_PEAKFREQ", 1500.0, eqControls.pfAttachment);
    setupHzSlider(eqControls.hsfSlider, "p_HIFREQ",  8600.0, eqControls.hsfAttachment);
    // Colorear cajas de texto de EQ en #7F78A2 (más claro)
    eqControls.lsfSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF7F78A2));
    eqControls.pfSlider .setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF7F78A2));
    eqControls.hsfSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF7F78A2));
    // EQ gains
    setupDbSlider(eqControls.lsgSlider, "h_LOWGAIN", 0.0, eqControls.lsgAttachment);
    setupDbSlider(eqControls.pgSlider,  "i_PEAKGAIN", 0.0, eqControls.pgAttachment);
    setupDbSlider(eqControls.hsgSlider, "j_HIGAIN", 0.0, eqControls.hsgAttachment);
    // Colorear cajas de texto de gains EQ en #7F78A2
    eqControls.lsgSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF7F78A2));
    eqControls.pgSlider .setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF7F78A2));
    eqControls.hsgSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF7F78A2));
    // Ensanchar la caja de texto para que quepa "+12.34 dB" sin constricción
    eqControls.lsgSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 64, 16);
    eqControls.pgSlider.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 64, 16);
    eqControls.hsgSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 64, 16);
    // Mostrar signo + en ganancias positivas de EQ
    // Mostrar con 2 decimales; evitar "-0.00" usando umbral de cero
    auto plusDb2 = [](double v) {
        const double eps = 0.005; // ~0.5 centésimas
        double vv = (std::abs(v) < eps) ? 0.0 : v;
        if (vv == 0.0)
            return juce::String("0.00");
        return juce::String::formatted("%+0.2f", vv);
    };
    // Asegurar sufijo visible desde el inicio
    eqControls.lsgSlider.setTextValueSuffix(" dB");
    eqControls.pgSlider.setTextValueSuffix(" dB");
    eqControls.hsgSlider.setTextValueSuffix(" dB");
    eqControls.lsgSlider.setNumDecimalPlacesToDisplay(2);
    eqControls.pgSlider.setNumDecimalPlacesToDisplay(2);
    eqControls.hsgSlider.setNumDecimalPlacesToDisplay(2);
    eqControls.lsgSlider.textFromValueFunction = plusDb2;
    eqControls.pgSlider.textFromValueFunction  = plusDb2;
    eqControls.hsgSlider.textFromValueFunction = plusDb2;
    // Forzar refresco del texto inicial para mostrar "dB" desde el principio
    eqControls.lsgSlider.setValue(eqControls.lsgSlider.getValue(), juce::dontSendNotification);
    eqControls.pgSlider.setValue (eqControls.pgSlider.getValue(),  juce::dontSendNotification);
    eqControls.hsgSlider.setValue(eqControls.hsgSlider.getValue(), juce::dontSendNotification);

    // === COMP CONTROLS (bottom-right) ===
    // COMP ON button (r_ONOFFCOMP)
    compControls.compOnButton.setClickingTogglesState(true);
    compControls.compOnButton.setLookAndFeel(&smallButtonLAF);
    compControls.compOnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    compControls.compOnButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    // Texto del activador COMP: ON amarillo suave; OFF blanco pálido más tenue
    compControls.compOnButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.5f));
    compControls.compOnButton.setColour(juce::TextButton::textColourOnId,  juce::Colour(0xFFDCCF6E));
    compControls.compOnButton.addListener(this);
    addAndMakeVisible(compControls.compOnButton);
    if (auto* paramC = processor.apvts.getParameter("r_ONOFFCOMP"))
    {
        compControls.compOnAttachment = std::make_unique<UndoableButtonAttachment>(*paramC, compControls.compOnButton, &undoManager);
        compControls.compOnAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    // THD (dB)
    setupDbSlider(compControls.thdSlider, "s_THD", -18.0, compControls.thdAttachment);

    // RATIO (t_RATIO)
    compControls.ratioSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    compControls.ratioSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, 16);
    compControls.ratioSlider.setLookAndFeel(&sliderLAFBig);
    compControls.ratioSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    compControls.ratioSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFDCCF6E));
    compControls.ratioSlider.setDoubleClickReturnValue(true, 4.0);
    compControls.ratioSlider.setPopupDisplayEnabled(false, false, this);
    compControls.ratioSlider.setNumDecimalPlacesToDisplay(1);
    compControls.ratioSlider.textFromValueFunction = [](double v) { return juce::String(v, v < 10.0 ? 1 : 0) + ":1"; };
    addAndMakeVisible(compControls.ratioSlider);
    if (auto* paramR = processor.apvts.getParameter("t_RATIO"))
    {
        compControls.ratioAttachment = std::make_unique<CustomSliderAttachment>(*paramR, compControls.ratioSlider, &undoManager);
        compControls.ratioAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    // ATK, REL (ms)
    auto setupMsSlider = [this](CustomSlider& s, const char* paramID, double dblClick, std::unique_ptr<CustomSliderAttachment>& outAtt) {
        s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
        s.setLookAndFeel(&sliderLAFBig);
        s.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        s.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFFFFFF));
        s.setDoubleClickReturnValue(true, dblClick);
        s.setPopupDisplayEnabled(false, false, this);
        s.setNumDecimalPlacesToDisplay(0);
        s.setTextValueSuffix(" ms");
    addAndMakeVisible(s);
        if (auto* param = processor.apvts.getParameter(paramID))
        {
            outAtt = std::make_unique<CustomSliderAttachment>(*param, s, &undoManager);
            outAtt->onParameterChange = [this]() { handleParameterChange(); };
        }
    };
    setupMsSlider(compControls.atkSlider, "u_ATK", 110.0,   compControls.atkAttachment);
    setupMsSlider(compControls.relSlider, "v_REL", 750.0, compControls.relAttachment);
    // Ajustar skews/decimales: ATK centro 110 ms; REL centro 250 ms; ambos 1 decimal
    compControls.atkSlider.setSkewFactorFromMidPoint(110.0);
    compControls.atkSlider.setNumDecimalPlacesToDisplay(1);
    compControls.relSlider.setSkewFactorFromMidPoint(250.0);
    compControls.relSlider.setNumDecimalPlacesToDisplay(1);
    // Colorear cajas de texto de COMP en amarillo suave
    compControls.thdSlider  .setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFDCCF6E));
    compControls.atkSlider  .setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFDCCF6E));
    compControls.relSlider  .setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFDCCF6E));
    compControls.gainSlider .setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFDCCF6E));

    // GAIN (dB) — 2 decimales, sin sufijo duplicado
    setupDbSlider(compControls.gainSlider, "w_MAKEUP", 0.0, compControls.gainAttachment);
    // Ensanchar caja de texto
    compControls.gainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 64, 16);
    // Asegurar sufijo visible desde el inicio
    compControls.gainSlider.setTextValueSuffix(" dB");
    compControls.gainSlider.setNumDecimalPlacesToDisplay(2);
    compControls.gainSlider.textFromValueFunction = [](double v) {
        const double eps = 0.005;
        double vv = (std::abs(v) < eps) ? 0.0 : v;
        if (vv == 0.0)
            return juce::String("0.00");
        return juce::String::formatted("%+0.2f", vv);
    };
    // Refrescar texto inicial
    compControls.gainSlider.setValue(compControls.gainSlider.getValue(), juce::dontSendNotification);
    // Asegurar color de texto amarillo (puede ser sobrescrito por setupDbSlider)
    compControls.gainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFDCCF6E));

    // PUMP toggle (x_PUMP)
    compControls.pumpButton.setClickingTogglesState(true);
    compControls.pumpButton.setLookAndFeel(&smallButtonLAF);
    // Asegurar captura de clicks (por si algún overlay interfiere)
    compControls.pumpButton.setInterceptsMouseClicks(true, true);
    compControls.pumpButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    compControls.pumpButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    // Estado visual del PUMP: OFF más pálido, ON amarillo
    compControls.pumpButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.5f));
    compControls.pumpButton.setColour(juce::TextButton::textColourOnId,  juce::Colour(0xFFDCCF6E));
    compControls.pumpButton.addListener(this);
    addAndMakeVisible(compControls.pumpButton);
    if (auto* paramPump = processor.apvts.getParameter("x_PUMP"))
    {
        compControls.pumpAttachment = std::make_unique<UndoableButtonAttachment>(*paramPump, compControls.pumpButton, &undoManager);
        compControls.pumpAttachment->onParameterChange = [this]() { handleParameterChange(); };
        // Refrescar texto/estado visual si cambia por automation/preset
        // (No se necesita acceso a 'this' en este momento)
        compControls.pumpAttachment->onStateChange = [](bool /*isOn*/) {
            // El color del texto ya depende del toggle y está configurado
        };
    }

    // Asegurar estados iniciales coherentes (habilitación de PUMP según COMP)
    updateCompComponentStates();
}

void JCBReverbAudioProcessorEditor::setupRightTabs()
{
    // Pestañas de capa derecha: EQ y COMP
    rightTabs.eqTab.setClickingTogglesState(true);
    rightTabs.eqTab.setLookAndFeel(&tabButtonLAF);
    rightTabs.eqTab.setToggleState(true, juce::dontSendNotification); // EQ activo por defecto
    // Fondo transparente para tabs; color solo en texto
    rightTabs.eqTab.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightTabs.eqTab.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    // Texto: activo morado vibrante (#8F86D0), inactivo más pálido (alfa 0.5)
    rightTabs.eqTab.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.5f));
    rightTabs.eqTab.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFF8F86D0));
    rightTabs.eqTab.addListener(this);
    addAndMakeVisible(rightTabs.eqTab);

    rightTabs.compTab.setClickingTogglesState(true);
    rightTabs.compTab.setLookAndFeel(&tabButtonLAF);
    rightTabs.compTab.setToggleState(false, juce::dontSendNotification);
    rightTabs.compTab.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightTabs.compTab.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    // Texto: activo amarillo, inactivo más pálido (alfa 0.5)
    rightTabs.compTab.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.5f));
    rightTabs.compTab.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFFDCCF6E));
    rightTabs.compTab.addListener(this);
    addAndMakeVisible(rightTabs.compTab);
}

void JCBReverbAudioProcessorEditor::setupMeters()
{
    // Medidores de entrada
    addAndMakeVisible(inputMeterL);
    addAndMakeVisible(inputMeterR);
    // Medidor GR

    // Medidores de salida
    addAndMakeVisible(outputMeterL);
    addAndMakeVisible(outputMeterR);

    // Sliders de trim/makeup (reverb): a_INPUT y m_OUTPUT
    trimSlider.setComponentID("a_INPUT");
    addAndMakeVisible(trimSlider);
    if (auto* param = processor.apvts.getParameter("a_INPUT"))
    {
        trimAttachment = std::make_unique<CustomSliderAttachment>(*param, trimSlider, &undoManager);
        trimAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    // Slider de makeup (salida)
    makeupSlider.setComponentID("m_OUTPUT");
    addAndMakeVisible(makeupSlider);
    if (auto* param = processor.apvts.getParameter("m_OUTPUT"))
    {
        makeupAttachment = std::make_unique<CustomSliderAttachment>(*param, makeupSlider, &undoManager);
        makeupAttachment->onParameterChange = [this]() { handleParameterChange(); };
        makeupSlider.setSkewFactorFromMidPoint(0.0);  // Centrar 0 dB visualmente
    }
}

void JCBReverbAudioProcessorEditor::setupPresetArea()
{
    // Botón Save - estilo transparente
    presetArea.saveButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    presetArea.saveButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    presetArea.saveButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    presetArea.saveButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    presetArea.saveButton.addListener(this);
    addAndMakeVisible(presetArea.saveButton);
    // Tooltip actualizado via getTooltipText("save") en updateAllTooltips()

    // Botón Save As - estilo transparente
    presetArea.saveAsButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    presetArea.saveAsButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    presetArea.saveAsButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    presetArea.saveAsButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    presetArea.saveAsButton.addListener(this);
    addAndMakeVisible(presetArea.saveAsButton);
    // Tooltip actualizado via getTooltipText("saveas") en updateAllTooltips()

    // Botón Delete - estilo transparente
    presetArea.deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    presetArea.deleteButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    presetArea.deleteButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    presetArea.deleteButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    presetArea.deleteButton.addListener(this);
    addAndMakeVisible(presetArea.deleteButton);
    // Tooltip actualizado via getTooltipText("delete") en updateAllTooltips()

    // Botón Back - estilo transparente
    presetArea.backButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    presetArea.backButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    presetArea.backButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    presetArea.backButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    presetArea.backButton.addListener(this);
    addAndMakeVisible(presetArea.backButton);
    // Tooltip actualizado via getTooltipText("back") en updateAllTooltips()

    // Botón Next - estilo transparente
    presetArea.nextButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    presetArea.nextButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    presetArea.nextButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    presetArea.nextButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    presetArea.nextButton.addListener(this);
    addAndMakeVisible(presetArea.nextButton);
    // Tooltip actualizado via getTooltipText("next") en updateAllTooltips()

    // Menú de preset - usando CustomComboBox como en JCBExpansorGate
    presetArea.presetMenu.setJustificationType(juce::Justification::centred);
    presetArea.presetMenu.setTextWhenNothingSelected("");
    presetArea.presetMenu.setTextWhenNoChoicesAvailable("No presets");

    // Configurar onChange para cargar presets
    presetArea.presetMenu.onChange = [this]() {
        int selectedId = presetArea.presetMenu.getSelectedId();
        if (selectedId == 0) return;

        // CRÍTICO: Establecer flag de carga PRIMERO para prevenir transacciones de undo
        isLoadingPreset = true;

        // Guard de scope para asegurar que el flag siempre se resetea
        struct LoadingGuard {
            bool& flag;
            LoadingGuard(bool& f) : flag(f) { flag = true; }
            ~LoadingGuard() { flag = false; }
        } guard(isLoadingPreset);

        // NOTA: El historial de undo se borrará al final para evitar grabar cambios de parámetros

        // Buscar el nombre real del preset usando el mapeo
        juce::String presetName;
        if (presetIdToNameMap.find(selectedId) != presetIdToNameMap.end()) {
            presetName = presetIdToNameMap[selectedId];
        } else {
            // Si no está en el mapeo, intentar obtenerlo del texto del menú (fallback)
            presetName = presetArea.presetMenu.getText();
            if (presetName.isEmpty()) {
                presetArea.presetMenu.setSelectedId(0);
                return;
            }
        }

        // Ignorar separadores
        if (presetName.startsWith("---")) {
            presetArea.presetMenu.setSelectedId(0);
            return;
        }

        if (presetName == "DEFAULT") {
            // Preset DEFAULT: Resetear todos los parámetros a sus valores por defecto definidos
            // Usar acceso directo a parámetros para actualizaciones inmediatas y confiables

            // Deshabilitar undo durante la carga de preset
            isLoadingPreset = true;

            // 1) Resetear TODOS los parámetros del APVTS a sus valores por defecto
            {
                auto& params = processor.getParameters();
                for (auto* p : params)
                {
                    if (auto* withID = dynamic_cast<juce::AudioProcessorParameterWithID*>(p))
                    {
                        if (auto* ranged = processor.apvts.getParameter(withID->paramID))
                        {
                            float def = ranged->getDefaultValue(); // normalizado 0..1
                            ranged->beginChangeGesture();
                            ranged->setValueNotifyingHost(def);
                            ranged->endChangeGesture();
                        }
                    }
                }
            }

            // Establecer todos los parámetros a sus valores por defecto usando gesture mechanism
            // Esto replica el mismo mecanismo usado por CustomSliderAttachment (doble-click)
            // COMENTADO: Reset de sliders de distorsión que no existen
            /*
            if (auto* param = processor.apvts.getParameter("k_INPUT")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                trimSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("a_DRYWET")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                leftBottomKnobs.drywetSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("e_CEILING")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                leftKnobs.ceilingSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("b_DRIVE")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightBottomKnobs.driveSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("d_MODE")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                reflectControls.reflectSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("l_OUTPUT")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                makeupSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("j_HPF")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                sidechainControls.hpfSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("k_LPF")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                sidechainControls.lpfSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("l_SC")) {
                float defaultValue = param->getDefaultValue();
                bool toggleState = defaultValue >= 0.5f;
                sidechainControls.scButton.setToggleState(toggleState, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("o_BAND")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                sidechainControls.bandSlider.setValue(realValue, juce::sendNotificationSync);
            }
            */
            // SIEMPRE salir de bypass al cargar DEFAULT
            parameterButtons.bypassButton.setToggleState(false, juce::sendNotificationSync);
            // COMENTADO: Más resets de controles de distorsión que no existen
            /*
            if (auto* param = processor.apvts.getParameter("h_BITSON")) {
                float defaultValue = param->getDefaultValue();
                bool toggleState = defaultValue >= 0.5f;
                rightBottomKnobs.bitButton.setToggleState(toggleState, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("i_TILT")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightTopControls.tiltSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("c_DC")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightBottomKnobs.dcSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("g_BITS")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightTopControls.bitsSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("n_DOWNSAMPLEON")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 0 (OFF)
                bool toggleState = defaultValue >= 0.5f; // false = OFF
                rightTopControls.downsampleButton.setToggleState(toggleState, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("p_TILTPOS")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 0 (PRE)
                bool toggleState = defaultValue >= 0.5f; // false = PRE
                rightTopControls.tiltPosButton.setToggleState(toggleState, juce::sendNotificationSync);
                rightTopControls.tiltPosButton.setButtonText(toggleState ? "POST" : "PRE");
            }
            if (auto* param = processor.apvts.getParameter("p_DISTON")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 1 (ON)
                bool toggleState = defaultValue >= 0.5f; // true = ON
                rightBottomKnobs.distOnButton.setToggleState(toggleState, juce::sendNotificationSync);
                rightBottomKnobs.distOnButton.setButtonText(toggleState ? "ON" : "OFF");
            }
            if (auto* param = processor.apvts.getParameter("m_DOWNSAMPLE")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 0 (0%)
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightTopControls.downsampleSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("p_BANDSOLO")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 0 (SOLO off)
                bool toggleState = defaultValue >= 0.5f; // false = SOLO off
                sidechainControls.bandSoloButton.setToggleState(toggleState, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("p_SAFELIMITON")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 0 (OFF)
                bool toggleState = defaultValue >= 0.5f; // false = OFF
                rightTopControls.safeLimitButton.setToggleState(toggleState, juce::sendNotificationSync);
                rightTopControls.safeLimitButton.setButtonText("LIM");
            }
            */
            // COMENTADO: Más resets de controles de distorsión
            /*
            if (auto* param = processor.apvts.getParameter("q_TONEON")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 0 (OFF)
                bool toggleState = defaultValue >= 0.5f; // false = OFF
                leftBottomKnobs.toneLpfButton.setToggleState(toggleState, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("r_TONEFREQ")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 12000 Hz
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                leftBottomKnobs.toneFreqSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("s_TILTON")) {
                float defaultValue = param->getDefaultValue(); // defaultValue = 1 (ON)
                bool toggleState = defaultValue >= 0.5f; // true = ON
                rightTopControls.tiltOnButton.setToggleState(toggleState, juce::sendNotificationSync);
            }
            */

            // DEFAULT: activar vista Wave
            applyDisplayMode(false);

            // Reactivar undo después carga de preset
            isLoadingPreset = false;

            // IMPORTANTE: Forzar la sincronización directa de Gen~ para asegurar valores correctos de los parámetros
            // Esto replica la misma sincronización realizada durante la instanciación del plugin
            for (int i = 0; i < JCBReverb::num_params(); i++) {
                auto paramName = juce::String(JCBReverb::getparametername(processor.getPluginState(), i));
                if (auto* param = processor.apvts.getRawParameterValue(paramName)) {
                    float value = param->load();

                    // Aplicar la misma validación que en parameterChanged()
                    if (paramName == "b_DRIVE" && value < 1.0f) {
                        value = 1.0f;  // Drive mínimo 1x
                    }
                    if (paramName == "d_MODE" && value > 7.0f) {
                        value = 7.0f;   // Mode máximo 7
                    }

                    JCBReverb::setparameter(processor.getPluginState(), i, value, nullptr);
                }
            }
        }
        else if (presetName.startsWith("Rooms_") || presetName.startsWith("Bass_") || presetName.startsWith("Drums_") ||
                 presetName.startsWith("Guitars_") || presetName.startsWith("Voces_") ||
                 presetName.startsWith("Fx_") || presetName.startsWith("Synth_") ||
                 presetName.startsWith("General_")) {
            // Es un factory preset con prefijo de categoría - cargar desde BinaryData
            juce::String resourceName = presetName + "_preset";

            // Buscar el recurso en BinaryData
            for (int i = 0; i < BinaryData::namedResourceListSize; ++i) {
                if (resourceName == BinaryData::namedResourceList[i]) {
                    // Cargar el preset desde BinaryData
                    int dataSize = 0;
                    const char* data = BinaryData::getNamedResource(BinaryData::namedResourceList[i], dataSize);

                    if (data != nullptr && dataSize > 0) {
                        // Parsear el XML desde memoria
                        juce::String xmlContent(data, dataSize);
                        juce::XmlDocument xmlDoc(xmlContent);
                        std::unique_ptr<juce::XmlElement> xmlState(xmlDoc.getDocumentElement());

                        if (xmlState != nullptr && xmlState->hasTagName(processor.apvts.state.getType())) {
                            auto stateTree = juce::ValueTree::fromXml(*xmlState);
                            processor.apvts.replaceState(stateTree);

                            // Restaurar estado del modo de visualización FFT/WAVE si está presente
                            auto uiSettings = stateTree.getChildWithName("UISettings");
                            if (uiSettings.isValid()) {
                                bool isFFT = uiSettings.getProperty("displayModeIsFFT", false);
                                applyDisplayMode(isFFT);
                            }

                            // SIEMPRE salir de bypass al cargar factory preset
                            parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
                        }
                    }
                    break;
                }
            }
        }
        else {
            // Es un user preset - cargar desde archivo
            juce::File presetFile = getPresetsFolder().getChildFile(presetName + ".preset");

            if (presetFile.existsAsFile()) {
                juce::XmlDocument xmlDoc(presetFile);
                std::unique_ptr<juce::XmlElement> xmlState(xmlDoc.getDocumentElement());

                if (xmlState != nullptr && xmlState->hasTagName(processor.apvts.state.getType())) {
                    auto stateTree = juce::ValueTree::fromXml(*xmlState);
                    processor.apvts.replaceState(stateTree);

                    // Restaurar estado del modo de visualización FFT/WAVE si está presente
                    auto uiSettings = stateTree.getChildWithName("UISettings");
                    if (uiSettings.isValid()) {
                        bool isFFT = uiSettings.getProperty("displayModeIsFFT", false);
                        applyDisplayMode(isFFT);
                    }

                    // SIEMPRE salir de bypass al cargar user preset
                    parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
                            // MAXIMIZER: No tiene m_SOLOSC
                }
            }
        }

        // Actualizar estado en processor
        processor.setLastPreset(selectedId);

        // Para mostrar en el menú, usar nombre limpio sin prefijos
        juce::String displayName = presetName;
        if (presetName.startsWith("Rooms_")) {
            displayName = "[F] " + presetName.substring(6).replace("_", " ");
        } else if (presetName.startsWith("Bass_")) {
            displayName = "[F] " + presetName.substring(5).replace("_", " ");
        } else if (presetName.startsWith("Drums_")) {
            displayName = "[F] " + presetName.substring(6).replace("_", " ");
        } else if (presetName.startsWith("Guitars_")) {
            displayName = "[F] " + presetName.substring(8).replace("_", " ");
        } else if (presetName.startsWith("Voces_")) {
            displayName = "[F] " + presetName.substring(6).replace("_", " ");
        } else if (presetName.startsWith("Fx_")) {
            displayName = "[F] " + presetName.substring(3).replace("_", " ");
        } else if (presetName.startsWith("Synth_")) {
            displayName = "[F] " + presetName.substring(6).replace("_", " ");
        } else if (presetName.startsWith("General_")) {
            displayName = "[F] " + presetName.substring(8).replace("_", " ");
        }

        processor.setPresetDisplayText(displayName);
        processor.setPresetTextItalic(false);
        presetArea.presetMenu.setTextItalic(false);

        // Actualizar sliders desde APVTS
        updateSliderValues();

        // IMPORTANTE: Actualizar también los botones desde APVTS (fix para presets Factory/User)
        updateButtonValues();

        // Actualizar la gráfica de transferencia con los valores actuales

        // Borrar el historial de undos DESPUÉS de haber establecido todos los valores.
        // Esto previene que los cambios de parámetros se registren en el historial de undo
        undoManager.clearUndoHistory();

        // Nota: el flag isLoadingPreset se resetea automáticamente por el destructor LoadingGuard
    };

    addAndMakeVisible(presetArea.presetMenu);

    // Inicializar menú de presets
    refreshPresetMenu();

    // Configurar el texto inicial del menú según el estado guardado
    auto savedText = processor.getPresetDisplayText();
    auto isItalic = processor.getPresetTextItalic();
    if (!savedText.isEmpty()) {
        presetArea.presetMenu.setTextWhenNothingSelected(savedText);
        presetArea.presetMenu.setTextItalic(isItalic);
    }
}

void JCBReverbAudioProcessorEditor::setupUtilityButtons()
{
    // Undo - estilo transparente
    utilityButtons.undoButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.undoButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.undoButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    utilityButtons.undoButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.undoButton.addListener(this);
    addAndMakeVisible(utilityButtons.undoButton);

    // Redo - estilo transparente
    utilityButtons.redoButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.redoButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.redoButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    utilityButtons.redoButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.redoButton.addListener(this);
    addAndMakeVisible(utilityButtons.redoButton);

    // Establecer el estado inicial de los botones de undo/redo (normalmente desactivados al inicio)
    utilityButtons.undoButton.setAlpha(0.3f);
    utilityButtons.undoButton.setEnabled(false);
    utilityButtons.redoButton.setAlpha(0.3f);
    utilityButtons.redoButton.setEnabled(false);

    // Reiniciar GUI - estilo transparente
    utilityButtons.resetGuiButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.resetGuiButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.resetGuiButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    utilityButtons.resetGuiButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.resetGuiButton.addListener(this);
    addAndMakeVisible(utilityButtons.resetGuiButton);
    // Tooltip actualizado via getTooltipText("resetgui") en updateAllTooltips()

    // El botón de bypass se ha movido a parameterButtons

    // Ejecutar gráficos - botón normal (no toggle) para control manual completo
    utilityButtons.runGraphicsButton.setClickingTogglesState(false);
    utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);  // Inicial: transparente (modo FFT por defecto)
    utilityButtons.runGraphicsButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    utilityButtons.runGraphicsButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.runGraphicsButton.addListener(this);
    addAndMakeVisible(utilityButtons.runGraphicsButton);
    // Tooltip actualizado via getTooltipText("graphics") en updateAllTooltips()

    // Botón toggle de tooltip - estilo transparente
    utilityButtons.tooltipToggleButton.setClickingTogglesState(true);
    utilityButtons.tooltipToggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.tooltipToggleButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.tooltipToggleButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    utilityButtons.tooltipToggleButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.tooltipToggleButton.setToggleState(true, juce::dontSendNotification); // ON por defecto
    utilityButtons.tooltipToggleButton.addListener(this);
    addAndMakeVisible(utilityButtons.tooltipToggleButton);
    // Tooltip actualizado via getTooltipText("tooltiptoggle") en updateAllTooltips()

    // Botón de idioma - estilo transparente
    utilityButtons.tooltipLangButton.setClickingTogglesState(false);  // No toggle, solo botón normal
    utilityButtons.tooltipLangButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.tooltipLangButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.tooltipLangButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    utilityButtons.tooltipLangButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.tooltipLangButton.setButtonText("esp");  // Texto inicial para español
    utilityButtons.tooltipLangButton.addListener(this);
    addAndMakeVisible(utilityButtons.tooltipLangButton);
    // Tooltip actualizado via getTooltipText("tooltiplang") en updateAllTooltips()

    // Botón HQ - oversampling
    utilityButtons.hqButton.setClickingTogglesState(true);
    utilityButtons.hqButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.hqButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.hqButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    utilityButtons.hqButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.hqButton.addListener(this);
    addAndMakeVisible(utilityButtons.hqButton);
    utilityButtons.hqButton.setEnabled(false);  // TODO: Implementar

    // Dual Mono button
    utilityButtons.dualMonoButton.setClickingTogglesState(true);
    utilityButtons.dualMonoButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.dualMonoButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.dualMonoButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    utilityButtons.dualMonoButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.dualMonoButton.addListener(this);
    addAndMakeVisible(utilityButtons.dualMonoButton);
    utilityButtons.dualMonoButton.setEnabled(false);  // TODO: Implementar

    // Stereo Linked button (ALWAYS ON - plugin only works in stereo linked mode)
    utilityButtons.stereoLinkedButton.setClickingTogglesState(false);  // No toggle
    utilityButtons.stereoLinkedButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.stereoLinkedButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.stereoLinkedButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);  // Siempre texto blanco
    utilityButtons.stereoLinkedButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.stereoLinkedButton.setToggleState(true, juce::dontSendNotification); // Siempre ON
    // No listener necesario ya que siempre está activo
    addAndMakeVisible(utilityButtons.stereoLinkedButton);
    // Tooltip actualizado via getTooltipText("link") en updateAllTooltips()
    utilityButtons.stereoLinkedButton.setEnabled(false);  // Disabled - can't be changed

    // Botón M/S
    utilityButtons.msButton.setClickingTogglesState(true);
    utilityButtons.msButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.msButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    utilityButtons.msButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    utilityButtons.msButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.msButton.addListener(this);
    addAndMakeVisible(utilityButtons.msButton);
    utilityButtons.msButton.setEnabled(false);  // TODO: Implementar

    // A/B State button
    topButtons.abStateButton.setClickingTogglesState(false);  // No es toggle, es un indicador
    topButtons.abStateButton.setColour(juce::TextButton::buttonColourId, 
        processor.getIsStateA() ? juce::Colour(0xff9E35B0) : juce::Colour(0xff2196f3));  // Color según estado actual
    topButtons.abStateButton.setColour(juce::TextButton::buttonOnColourId, 
        processor.getIsStateA() ? juce::Colour(0xff9E35B0) : juce::Colour(0xff2196f3));  // Mismo color para evitar brillo
    topButtons.abStateButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    topButtons.abStateButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    topButtons.abStateButton.addListener(this);
    topButtons.abStateButton.setButtonText(processor.getIsStateA() ? "A" : "B");  // Texto según estado actual
    addAndMakeVisible(topButtons.abStateButton);
    topButtons.abStateButton.setEnabled(true);  // Now implemented!

    // Botón copiar A/B
    topButtons.abCopyButton.setClickingTogglesState(false);
    topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    topButtons.abCopyButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    topButtons.abCopyButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    topButtons.abCopyButton.addListener(this);
    topButtons.abCopyButton.setButtonText(processor.getIsStateA() ? "A-B" : "B-A");  // Texto según estado actual
    addAndMakeVisible(topButtons.abCopyButton);
    // Tooltip actualizado dinámicamente en updateAbButtonState()

    // MIDI Learn button
    utilityButtons.midiLearnButton.setClickingTogglesState(true);
    utilityButtons.midiLearnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.midiLearnButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::purple.withAlpha(0.3f));
    utilityButtons.midiLearnButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    utilityButtons.midiLearnButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.midiLearnButton.addListener(this);
    addAndMakeVisible(utilityButtons.midiLearnButton);
    utilityButtons.midiLearnButton.setEnabled(false);  // TODO: Implementar

    // Botón Zoom
    utilityButtons.zoomButton.setClickingTogglesState(true);
    utilityButtons.zoomButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    utilityButtons.zoomButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    utilityButtons.zoomButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);  // Cambiado para igualar otros botones
    utilityButtons.zoomButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    utilityButtons.zoomButton.addListener(this);
    addAndMakeVisible(utilityButtons.zoomButton);
    utilityButtons.zoomButton.setButtonText("zoom"); // Estado inicial: Normal
    utilityButtons.zoomButton.setToggleState(false, juce::dontSendNotification); // Toggle OFF para normal
    // Tooltip actualizado via getTooltipText("zoom") en updateAllTooltips()

    // Botón Diagram
    centerButtons.diagramButton.setClickingTogglesState(true);
    centerButtons.diagramButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    centerButtons.diagramButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    centerButtons.diagramButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    centerButtons.diagramButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    centerButtons.diagramButton.addListener(this);
    addAndMakeVisible(centerButtons.diagramButton);
    // Tooltip actualizado via getTooltipText("diagram") en updateAllTooltips()

}

void JCBReverbAudioProcessorEditor::setupParameterButtons()
{

    // Botón BYPASS - movido desde utilityButtons
    parameterButtons.bypassButton.setClickingTogglesState(true);
    parameterButtons.bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    parameterButtons.bypassButton.setColour(juce::TextButton::buttonOnColourId, DarkTheme::accent.withAlpha(0.3f));
    parameterButtons.bypassButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    parameterButtons.bypassButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    parameterButtons.bypassButton.addListener(this);
    addAndMakeVisible(parameterButtons.bypassButton);
    // Bypass interno (Gen) no está en APVTS → no crear attachment al host
    // El estado se sincroniza en updateButtonValues() y buttonClicked()
}

void JCBReverbAudioProcessorEditor::setupBackground()
{
    try {
        // Cargar imágenes de fondo con validación
        normalBackground = juce::ImageCache::getFromMemory(BinaryData::fondo_png, BinaryData::fondo_pngSize);
        bypassBackground = juce::ImageCache::getFromMemory(BinaryData::bypass_png, BinaryData::bypass_pngSize);
        diagramBackground = juce::ImageCache::getFromMemory(BinaryData::diagramaFondo_png, BinaryData::diagramaFondo_pngSize);

        // Establecer background inicial solo si es válido
        if (normalBackground.isValid())
        {
            backgroundImage.setImage(normalBackground, juce::RectanglePlacement::stretchToFit);
            addAndMakeVisible(backgroundImage);
            backgroundImage.toBack();
        }
    }
    catch (const std::exception& e) {
        // En caso de error, continuar sin imagen de fondo
        DBG("Error loading background images: " << e.what());
    }
}

//==============================================================================
// MÉTODOS DE UPDATE Y REFRESH
//==============================================================================

void JCBReverbAudioProcessorEditor::updateButtonStates()
{
    // Función maestra que actualiza todos los estados de UI
    updateBasicButtonStates();
    updateSidechainComponentStates();
    updateEqComponentStates();
    updateCompComponentStates();
    /*
    // Actualizar estados de componentes de distorsión
    updateDistortionComponentStates();
    // Actualizar estados de componentes de bit crusher
    updateBitCrusherComponentStates();
    // Actualizar estados de componentes de downsample
    updateDownsampleComponentStates();
    // Actualizar estados de componentes de tone LPF
    updateToneLpfComponentStates();
    // Actualizar estados de componentes de tilt
    updateTiltComponentStates();
    */
    updateBackgroundState();
    updateMeterStates();

    // MEJORADO: Estado inicial aplicado
}

void JCBReverbAudioProcessorEditor::updateBasicButtonStates()
{
    // Obtener estados actuales
    const bool bypassActive = parameterButtons.bypassButton.getToggleState();

    // Actualizar estados visuales básicos
    isBypassed = bypassActive;
    bypassTextVisible = bypassActive;  // Siempre mostrar texto cuando bypass está activo
}

void JCBReverbAudioProcessorEditor::updateSidechainComponentStates()
{
    // Obtener estado del botón FILTERS
    //const bool filtersActive = sidechainControls.scButton.getToggleState();
    const bool filtersActive = processor.apvts.getRawParameterValue("y_FILTERS")->load() > 0.5f;

    // Los filtros HPF/LPF siempre visibles y movibles
    sidechainControls.hpfSlider.setVisible(true);  // Siempre visibles
    sidechainControls.lpfSlider.setVisible(true);  // Siempre visibles
    // Solo cambiar alpha para indicación visual (pero siguen siendo movibles)
    sidechainControls.hpfSlider.setAlpha(filtersActive ? 1.0f : 0.5f);  // Alpha indica estado
    sidechainControls.lpfSlider.setAlpha(filtersActive ? 1.0f : 0.5f);   // Alpha indica estado
}

void JCBReverbAudioProcessorEditor::updateEqComponentStates()
{
    const bool eqOn = processor.apvts.getRawParameterValue("q_ONOFFEQ")->load() > 0.5f;
    auto set = [&](juce::Component& c){ c.setEnabled(eqOn); c.setAlpha(eqOn ? 1.0f : 0.35f); };
    set(eqControls.lsfSlider); set(eqControls.pfSlider); set(eqControls.hsfSlider);
    set(eqControls.lsgSlider); set(eqControls.pgSlider); set(eqControls.hsgSlider);
    eqControls.eqOnButton.setButtonText(eqOn ? "ON" : "OFF");
}

void JCBReverbAudioProcessorEditor::updateCompComponentStates()
{
    const bool compOn = processor.apvts.getRawParameterValue("r_ONOFFCOMP")->load() > 0.5f;
    auto set = [&](juce::Component& c){ c.setEnabled(compOn); c.setAlpha(compOn ? 1.0f : 0.35f); };
    set(compControls.thdSlider);
    set(compControls.ratioSlider);
    set(compControls.atkSlider);
    set(compControls.relSlider);
    set(compControls.gainSlider);
    set(compControls.pumpButton);
    compControls.compOnButton.setButtonText(compOn ? "ON" : "OFF");

    // Política: cuando COMP está OFF, PUMP queda deshabilitado visualmente
    // pero su estado (ON/OFF) se conserva para restaurarlo al reactivar COMP.
}

void JCBReverbAudioProcessorEditor::updateRightPanelVisibility()
{
    const bool showEQ = (currentRightTab == RightPanelTab::EQ);

    auto setEqVis = [&](bool v){
        eqControls.eqOnButton.setVisible(v);
        eqControls.lsfSlider.setVisible(v);
        eqControls.pfSlider.setVisible(v);
        eqControls.hsfSlider.setVisible(v);
        eqControls.lsgSlider.setVisible(v);
        eqControls.pgSlider.setVisible(v);
        eqControls.hsgSlider.setVisible(v);
    };
    auto setCompVis = [&](bool v){
        compControls.compOnButton.setVisible(v);
        compControls.thdSlider.setVisible(v);
        compControls.ratioSlider.setVisible(v);
        compControls.atkSlider.setVisible(v);
        compControls.relSlider.setVisible(v);
        compControls.gainSlider.setVisible(v);
        compControls.pumpButton.setVisible(v);
    };

    setEqVis(showEQ);
    setCompVis(!showEQ);

    rightTabs.eqTab.setToggleState(showEQ, juce::dontSendNotification);
    rightTabs.compTab.setToggleState(!showEQ, juce::dontSendNotification);

    // Bring tabs and active panel to front for clickability over FFT
    rightTabs.eqTab.toFront(true);
    rightTabs.compTab.toFront(true);
    if (showEQ)
    {
        eqControls.eqOnButton.toFront(true);
        eqControls.lsfSlider.toFront(true);
        eqControls.pfSlider.toFront(true);
        eqControls.hsfSlider.toFront(true);
        eqControls.lsgSlider.toFront(true);
        eqControls.pgSlider.toFront(true);
        eqControls.hsgSlider.toFront(true);
    }
    else
    {
        compControls.compOnButton.toFront(true);
        compControls.pumpButton.toFront(true);
        compControls.thdSlider.toFront(true);
        compControls.ratioSlider.toFront(true);
        compControls.atkSlider.toFront(true);
        compControls.relSlider.toFront(true);
        compControls.gainSlider.toFront(true);
    }
}


// void JCBReverbAudioProcessorEditor::updateDistortionComponentStates()
// {
//     // Obtener estado del botón distOnButton (p_DISTON)
//     const bool distortionActive = rightBottomKnobs.distOnButton.getToggleState();
//
//     // REFLECT slider always enabled for reverb
//     leftKnobs.reflectSlider.setEnabled(true);
//     leftKnobs.reflectSlider.setAlpha(1.0f);
//
//     // EVEN (DC) slider - activo solo cuando distorsión está ON
//     rightBottomKnobs.dcSlider.setEnabled(distortionActive);
//     rightBottomKnobs.dcSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
//
//     // DRIVE slider - activo solo cuando distorsión está ON
//     rightBottomKnobs.driveSlider.setEnabled(distortionActive);
//     rightBottomKnobs.driveSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
//
//     // CEIL slider - activo solo cuando distorsión está ON
//     leftKnobs.ceilingSlider.setEnabled(distortionActive);
//     leftKnobs.ceilingSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
//
//     // TILT POS button (PRE/POST) - activo solo cuando distorsión está ON
//     rightTopControls.tiltPosButton.setEnabled(distortionActive);
//     rightTopControls.tiltPosButton.setAlpha(distortionActive ? 1.0f : 0.5f);
//
//     // Actualizar alpha del texto del botón tiltPos según estado de distorsión
//     // PRE y POST deben verse igual (no hay diferencia entre los dos estados)
//     rightTopControls.tiltPosButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFFA6DAD5).withAlpha(distortionActive ? 1.0f : 0.5f)  // Verde agua pálido como tiltSlider
//     );
//     rightTopControls.tiltPosButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFFA6DAD5).withAlpha(distortionActive ? 1.0f : 0.5f)  // Verde agua pálido como tiltSlider
//     );
//
//     // Actualizar alpha del texto del botón distOn según estado
//     rightBottomKnobs.distOnButton.setColour(
//         juce::TextButton::textColourOffId,
//         DarkTheme::textSecondary.withAlpha(0.7f)
//     );
//     rightBottomKnobs.distOnButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFFFEB2B2)  // Rosa pálido como los sliders de distorsión
//     );
//
//     // Actualizar estado de la curva de distorsión
//     // distortionCurveDisplay.setDistortionEnabled(distortionActive);
// }

// void JCBReverbAudioProcessorEditor::updateBitCrusherComponentStates()
// {
//     // Obtener estado del botón BIT CRUSHER (h_BITSON)
//     const bool bitCrusherActive = rightBottomKnobs.bitButton.getToggleState();
//
//     // BIT slider - siempre interactivo pero con alpha reducido cuando BIT CRUSHER está OFF
//     rightTopControls.bitsSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
//     rightTopControls.bitsSlider.setAlpha(bitCrusherActive ? 1.0f : 0.5f);
//
//     // Actualizar alpha del texto del botón BIT CRUSHER según estado
//     rightBottomKnobs.bitButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFFB2FFB3).withAlpha(bitCrusherActive ? 0.7f : 0.4f)  // Verde pálido
//     );
//     rightBottomKnobs.bitButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFFB2FFB3).withAlpha(bitCrusherActive ? 1.0f : 0.5f)  // Verde pálido
//     );
// }

// void JCBReverbAudioProcessorEditor::updateDownsampleComponentStates()
// {
//     // Obtener estado del botón DOWNSAMPLE (n_DOWNSAMPLEON)
//     const bool downsampleActive = rightTopControls.downsampleButton.getToggleState();
//
//     // DECI slider - siempre interactivo pero con alpha reducido cuando DOWNSAMPLE está OFF
//     rightTopControls.downsampleSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
//     rightTopControls.downsampleSlider.setAlpha(downsampleActive ? 1.0f : 0.5f);
//
//     // Actualizar alpha del texto del botón DOWNSAMPLE según estado
//     rightTopControls.downsampleButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFFD9B2FF).withAlpha(downsampleActive ? 0.7f : 0.4f)  // Púrpura pálido
//     );
//     rightTopControls.downsampleButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFFD9B2FF).withAlpha(downsampleActive ? 1.0f : 0.5f)  // Púrpura pálido
//     );
// }

// void JCBReverbAudioProcessorEditor::updateTiltComponentStates()
// {
//     // Obtener estado del botón TILT (s_TILTON)
//     const bool tiltActive = rightTopControls.tiltOnButton.getToggleState();
//
//     // TILT slider - siempre interactivo pero con alpha reducido cuando TILT está OFF
//     rightTopControls.tiltSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
//     rightTopControls.tiltSlider.setAlpha(tiltActive ? 1.0f : 0.5f);
//
//     // TILT POS button - siempre interactivo pero con alpha reducido cuando TILT está OFF
//     rightTopControls.tiltPosButton.setEnabled(true);  // Siempre habilitado para pre-configuración
//     rightTopControls.tiltPosButton.setAlpha(tiltActive ? 1.0f : 0.5f);
//     rightTopControls.tiltPosButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 1.0f : 0.5f)  // Verde agua pálido
//     );
//     rightTopControls.tiltPosButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 1.0f : 0.5f)  // Verde agua pálido
//     );
//
//     // Actualizar alpha del texto del botón TILT según estado
//     rightTopControls.tiltOnButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 0.7f : 0.3f)  // Verde agua pálido
//     );
//     rightTopControls.tiltOnButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 1.0f : 0.4f)  // Verde agua pálido
//     );
// }

// void JCBReverbAudioProcessorEditor::updateToneLpfComponentStates()
// {
//     // Obtener estado del botón TONE LPF (q_TONEON)
//     const bool toneLpfActive = leftBottomKnobs.toneLpfButton.getToggleState();
//
//     // TONE FREQ slider - siempre interactivo pero con alpha reducido cuando TONE LPF está OFF
//     leftBottomKnobs.toneFreqSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
//     leftBottomKnobs.toneFreqSlider.setAlpha(toneLpfActive ? 1.0f : 0.5f);
//
//     // TONE Q slider - siempre interactivo pero con alpha reducido cuando TONE LPF está OFF
//     leftBottomKnobs.toneQSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
//     leftBottomKnobs.toneQSlider.setAlpha(toneLpfActive ? 1.0f : 0.5f);
//
//     // TONE POS button - siempre interactivo pero con alpha reducido cuando TONE LPF está OFF
//     leftBottomKnobs.tonePosButton.setEnabled(true);  // Siempre habilitado para pre-configuración
//     leftBottomKnobs.tonePosButton.setAlpha(toneLpfActive ? 1.0f : 0.5f);
//     leftBottomKnobs.tonePosButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 1.0f : 0.5f)  // Azul claro TONE
//     );
//     leftBottomKnobs.tonePosButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 1.0f : 0.5f)  // Azul claro TONE
//     );
//
//     // Actualizar alpha del texto del botón TONE LPF según estado
//     leftBottomKnobs.toneLpfButton.setColour(
//         juce::TextButton::textColourOffId,
//         juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 0.7f : 0.3f)  // Azul claro TONE
//     );
//     leftBottomKnobs.toneLpfButton.setColour(
//         juce::TextButton::textColourOnId,
//         juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 1.0f : 0.4f)  // Azul claro TONE
//     );
// }

void JCBReverbAudioProcessorEditor::updateBackgroundState()
{
    // Obtener estados actuales
    const bool bypassActive = parameterButtons.bypassButton.getToggleState();

    // Actualizar fondo según prioridad: bypass > normal
    if (bypassActive) {
        backgroundImage.setImage(bypassBackground, juce::RectanglePlacement::stretchToFit);
    }
    else {
        backgroundImage.setImage(normalBackground, juce::RectanglePlacement::stretchToFit);
    }
}

void JCBReverbAudioProcessorEditor::updateFilterButtonText()
{
    /*
    // Actualizar texto del botón HPF Order
    if (auto* hpfParam = processor.apvts.getParameter("j_HPFORDER"))
    {
        float normalized = hpfParam->getValue();
        float denormalized = hpfParam->convertFrom0to1(normalized);
        int value = static_cast<int>(denormalized + 0.5f);

        switch (value)
        {
            case 0: sidechainControls.hpfOrderButton.setButtonText("12"); break;
            case 1: sidechainControls.hpfOrderButton.setButtonText("24"); break;
            default: sidechainControls.hpfOrderButton.setButtonText("12"); break;
        }
    }
    */

    /*
    // Actualizar texto del botón LPF Order
    if (auto* lpfParam = processor.apvts.getParameter("k_LPFORDER"))
    {
        float normalized = lpfParam->getValue();
        float denormalized = lpfParam->convertFrom0to1(normalized);
        int value = static_cast<int>(denormalized + 0.5f);

        switch (value)
        {
            case 0: sidechainControls.lpfOrderButton.setButtonText("12"); break;
            case 1: sidechainControls.lpfOrderButton.setButtonText("24"); break;
            default: sidechainControls.lpfOrderButton.setButtonText("12"); break;
        }
    }
    */
}

void JCBReverbAudioProcessorEditor::updateMeterStates()
{
    // Obtener estados actuales
    const bool bypassActive = parameterButtons.bypassButton.getToggleState();
    // MAXIMIZER: No sidechain controls - commenting out
    // const bool soloScActive = sidechainControls.soloScButton.getToggleState();
    const bool soloScActive = false;  // No sidechain in this processor

    // Actualizar colores de medidores
    // Si bypass está activo, no cambiar colores (mantener normales)
    // Si solo SC está activo, usar colores rojos
    bool soloMode = soloScActive && !bypassActive;
    // scMeterL.setSoloScMode(soloMode);
    // scMeterR.setSoloScMode(soloMode);

    inputMeterL.setSoloScMode(soloMode);
    inputMeterR.setSoloScMode(soloMode);
    outputMeterL.setSoloScMode(soloMode);
    outputMeterR.setSoloScMode(soloMode);
    // scMeterL.setSoloScMode(soloMode);
    // scMeterR.setSoloScMode(soloMode);

    // Ocultar gain reduction meter cuando SOLO SC está activo (no hay compresión activa)
    // NUEVO: También ocultar cuando BYPASS está activo

    // Actualizar gradiente de salida para modo bypass
    outputMeterL.setBypassMode(bypassActive);
    outputMeterR.setBypassMode(bypassActive);

    // CORRECCIÓN: Asegurar sincronización estado BYPASS al reabrir plugin
    // Esto resuelve el problema de la función de transferencia que reaparece incorrectamente
    // distortionCurveDisplay.setBypassMode(bypassActive);
}

void JCBReverbAudioProcessorEditor::updateMeters()
{
    // CORRECCIÓN CRÍTICA: Cachear estados de visibilidad para evitar llamadas repetidas a setVisible
    static bool lastSoloScActive = false;
    static bool lastExtKeyActive = false;

    // Verificar si SOLO SC está activo
    // MAXIMIZER: No sidechain controls - commenting out
    // const bool soloScActive = sidechainControls.soloScButton.getToggleState();
    // const bool extKeyActive = sidechainControls.keyButton.getToggleState();
    const bool soloScActive = false;  // No sidechain
    const bool extKeyActive = false;  // No external key

    // Solo actualizar visibilidad cuando el estado realmente cambia
    if (soloScActive != lastSoloScActive || extKeyActive != lastExtKeyActive) {
        if (soloScActive) {
            // SOLO SC activo - mostrar meters apropiados basados en EXT KEY
            if (extKeyActive) {
                // Ocultar medidores principales de entrada
                inputMeterL.setVisible(false);
                inputMeterR.setVisible(false);
                            // Hacer visibles los medidores de sidechain
                // scMeterL.setVisible(true);
                // scMeterR.setVisible(true);
            } else {
                // Mostrar medidores principales de entrada en modo SOLO SC (sidechain interno)
                inputMeterL.setVisible(true);
                inputMeterR.setVisible(true);
                            // scMeterL.setVisible(true);
                // scMeterR.setVisible(true);
            }
        } else {
            // Modo normal - mostrar todos los medidores normalmente
            inputMeterL.setVisible(true);
            inputMeterR.setVisible(true);
                    // scMeterL.setVisible(true);
            // scMeterR.setVisible(true);
        }

        lastSoloScActive = soloScActive;
        lastExtKeyActive = extKeyActive;
    }

    // Actualizar medidores con control centralizado a 60 Hz
    // Llamar a updateLevel() de cada medidor para procesar valores y animaciones
    if (inputMeterL.isVisible()) {
        inputMeterL.updateLevel();
        inputMeterR.updateLevel();
        inputMeterL.repaint();
        inputMeterR.repaint();
    }

    /*
    if (scMeterL.isVisible()) {
        scMeterL.updateLevel();
        scMeterR.updateLevel();
        scMeterL.repaint();
        scMeterR.repaint();
    }
    */

    /*
    // Siempre actualizar detección de clip de sidechain
    scMeterL.setClipDetected(processor.getSidechainClipDetected(0));
    scMeterR.setClipDetected(processor.getSidechainClipDetected(1));
    */

    // Siempre actualizar medidores de salida y reducción de ganancia

    outputMeterL.updateLevel();
    outputMeterR.updateLevel();
    outputMeterL.repaint();
    outputMeterR.repaint();
}

void JCBReverbAudioProcessorEditor::updateSliderValues()
{
    // Actualizar todos los sliders con los valores actuales del APVTS
    // Esto soluciona el problema de que los valores no se actualizan al cargar sesión
    // FIXED: Los comentarios anteriores eran incorrectos - todos los sliders usan CustomSliderAttachment

    // COMENTADO: Actualización de sliders de distorsión que no existen
    /*
    // Left top knobs - Todos usan CustomSliderAttachment
    if (auto* param = processor.apvts.getRawParameterValue("a_DRYWET"))
        leftBottomKnobs.drywetSlider.setValue(param->load(), juce::dontSendNotification);

    if (auto* param = processor.apvts.getRawParameterValue("e_CEILING"))
        leftKnobs.ceilingSlider.setValue(param->load(), juce::dontSendNotification);
    */

    // if (auto* param = processor.apvts.getRawParameterValue("c_RATIO"))
    //     leftKnobs.ratioSlider.setValue(param->load(), juce::dontSendNotification);


    // if (auto* param = processor.apvts.getRawParameterValue("q_KNEE"))
    //     leftKnobs.kneeSlider.setValue(param->load(), juce::dontSendNotification);


    // n_LOOKAHEAD no existe en este procesador



    // Right top controls

    // MAXIMIZER: g_REACT no existe - parámetro eliminado según CONTEXTO.txt
    // if (auto* param = processor.apvts.getRawParameterValue("g_REACT"))
    //     rightTopControls.reactSlider.setValue(param->load(), juce::dontSendNotification);

    // COMENTADO: Más sliders de distorsión
    /*
    // Right bottom knobs - Todos usan CustomSliderAttachment
    if (auto* param = processor.apvts.getRawParameterValue("b_DRIVE"))
        rightBottomKnobs.driveSlider.setValue(param->load(), juce::dontSendNotification);

    if (auto* param = processor.apvts.getRawParameterValue("c_REFLECT"))
        leftKnobs.reflectSlider.setValue(param->load(), juce::dontSendNotification);
    */

    // COMENTADO: Más controles de distorsión inexistentes
    /*
    if (auto* param = processor.apvts.getRawParameterValue("i_TILT"))
        rightTopControls.tiltSlider.setValue(param->load(), juce::dontSendNotification);


    if (auto* param = processor.apvts.getRawParameterValue("c_DC"))
        rightBottomKnobs.dcSlider.setValue(param->load(), juce::dontSendNotification);

    // MAXIMIZER: z_SMOOTH no existe - parámetro eliminado según CONTEXTO.txt
    // if (auto* param = processor.apvts.getRawParameterValue("z_SMOOTH"))
    //     rightTopControls.smoothSlider.setValue(param->load(), juce::dontSendNotification);

    // Controles de sidechain - Todos usan CustomSliderAttachment
    if (auto* param = processor.apvts.getRawParameterValue("j_HPF"))
        sidechainControls.hpfSlider.setValue(param->load(), juce::dontSendNotification);

    if (auto* param = processor.apvts.getRawParameterValue("k_LPF"))
        sidechainControls.lpfSlider.setValue(param->load(), juce::dontSendNotification);

    if (auto* param = processor.apvts.getRawParameterValue("o_BAND"))
        sidechainControls.bandSlider.setValue(param->load(), juce::dontSendNotification);
    */


    // COMENTADO: Sliders de trim y makeup que no existen
    /*
    // Slider de trims (both linked to the same parameter)
    if (auto* param = processor.apvts.getRawParameterValue("k_INPUT")) {
        float trimValue = param->load();
        trimSlider.setValue(trimValue, juce::dontSendNotification);
    }

    if (auto* param = processor.apvts.getRawParameterValue("l_OUTPUT")) {
        float makeupValue = param->load();
        makeupSlider.setValue(makeupValue, juce::dontSendNotification);
    }
    */

    /*
    // Slider de trim de sidechain
    if (auto* param = processor.apvts.getRawParameterValue("y_SCTRIM")) {
        float scTrimValue = param->load();
        scTrimSlider.setValue(scTrimValue, juce::dontSendNotification);
    }
    */

    // NUEVO: Actualizar alpha del REL slider basado en estado inicial de AUTOREL
}

void JCBReverbAudioProcessorEditor::updateButtonValues()
{
    // Actualizar todos los botones con los valores actuales del APVTS
    // Esta función es crucial para que los presets Factory/User actualicen correctamente los botones

    // Bypass button (interno Gen: z_BYPASS)
    {
        bool toggleState = false;
        if (auto* st = processor.getPluginState())
        {
            for (int i = 0; i < JCBReverb::num_params(); ++i)
            {
                if (juce::String(JCBReverb::getparametername(st, i)) == "z_BYPASS")
                {
                    t_param v = 0;
                    JCBReverb::getparameter(st, i, &v);
                    toggleState = (v >= 0.5f);
                    break;
                }
            }
        }
        parameterButtons.bypassButton.setToggleState(toggleState, juce::dontSendNotification);
    }
    // El resto de controles pertenece al plugin de origen (Distortion) y no existen aquí.
    // Evitar referencias a controles no declarados hasta que la UI de reverb esté completa.
    return;
}

void JCBReverbAudioProcessorEditor::resetGuiSize()
{
    // Ciclar al siguiente estado: Current -> Maximum -> Minimum -> Current
    switch (currentSizeState) {
        case GuiSizeState::Current:
            // Current -> Maximum
            processor.setSavedSize({MAX_WIDTH, MAX_HEIGHT});
            setSize(MAX_WIDTH, MAX_HEIGHT);
            currentSizeState = GuiSizeState::Maximum;
            break;

        case GuiSizeState::Maximum:
            // Maximum -> Minimum
            processor.setSavedSize({MIN_WIDTH, MIN_HEIGHT});
            setSize(MIN_WIDTH, MIN_HEIGHT);
            currentSizeState = GuiSizeState::Minimum;
            break;

        case GuiSizeState::Minimum:
            // Minimum -> Current (back to default)
            processor.setSavedSize({DEFAULT_WIDTH, DEFAULT_HEIGHT});
            setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
            currentSizeState = GuiSizeState::Current;
            break;
    }

    // Forzar repaint para asegurar que se actualice correctamente
    repaint();
}

//==============================================================================
// GESTIÓN DE PRESETS
//==============================================================================
juce::File JCBReverbAudioProcessorEditor::getPresetsFolder()
{
    juce::File folder = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory)
        .getChildFile("Audio")
        .getChildFile("Presets")
        .getChildFile("Coeval")
        .getChildFile("JCBReverb");

    if (!folder.isDirectory() && !folder.existsAsFile()) {
        folder.createDirectory();
    }

    return folder;
}

juce::Array<juce::File> JCBReverbAudioProcessorEditor::populatePresetFolder()
{
    return getPresetsFolder().findChildFiles(2, false, "*.preset");
}

void JCBReverbAudioProcessorEditor::refreshPresetMenu()
{
    presetArea.presetMenu.clear();
    presetIdToNameMap.clear();  // Limpiar mapeo anterior

    // Añadir DEFAULT como primer preset siempre
    presetArea.presetMenu.addItem("DEFAULT", 1);
    presetIdToNameMap[1] = "DEFAULT";

    // Añadir separador
    presetArea.presetMenu.addItem("---", 2);

    // Organizar factory presets por categoría
    std::map<juce::String, juce::StringArray> categorizedPresets;
    std::map<juce::String, juce::StringArray> categorizedFullNames;  // Nombres completos con prefijos
    int nextId = 100;

    // Procesar factory presets desde BinaryData
    for (int i = 0; i < BinaryData::namedResourceListSize; ++i)
    {
        juce::String resourceName(BinaryData::namedResourceList[i]);

        // Buscar archivos que terminen en "_preset"
        if (resourceName.endsWith("_preset"))
        {
            juce::String cleanName = resourceName.replace("_preset", "");

            // Detectar categoría del prefijo
            juce::String category = "General";
            juce::String presetName = cleanName;

            if (cleanName.startsWith("Bass_"))
            {
                category = "Bass";
                presetName = cleanName.substring(5).replace("_", " ");
            }
            else if (cleanName.startsWith("Drums_"))
            {
                category = "Drums";
                presetName = cleanName.substring(6).replace("_", " ");
            }
            else if (cleanName.startsWith("Rooms_"))
            {
                category = "Rooms";
                presetName = cleanName.substring(6).replace("_", " ");
            }
            else if (cleanName.startsWith("Guitars_"))
            {
                category = "Guitars";
                presetName = cleanName.substring(8).replace("_", " ");
            }
            else if (cleanName.startsWith("Voces_"))
            {
                category = "Voces";
                presetName = cleanName.substring(6).replace("_", " ");
            }
            else if (cleanName.startsWith("Fx_"))
            {
                category = "Fx";
                presetName = cleanName.substring(3).replace("_", " ");
            }
            else if (cleanName.startsWith("Synth_"))
            {
                category = "Synth";
                presetName = cleanName.substring(6).replace("_", " ");
            }
            else if (cleanName.startsWith("General_"))
            {
                category = "General";
                presetName = cleanName.substring(8).replace("_", " ");
            }

            categorizedPresets[category].add("[F] " + presetName);
            categorizedFullNames[category].add(cleanName);  // Guardar nombre completo con prefijo
        }
    }

    // Añadir categorías al menú
    juce::StringArray categoryOrder = {"Rooms", "Bass", "Drums", "Fx", "Guitars"};

    for (const auto& category : categoryOrder)
    {
        if (categorizedPresets.find(category) != categorizedPresets.end())
        {
            auto& presets = categorizedPresets[category];
            auto& fullNames = categorizedFullNames[category];
            presets.sort(true);
            fullNames.sort(true);

            // Añadir categoría con sus subitems
            presetArea.presetMenu.addCategoryItem(category, presets, nextId);

            // Mapear IDs a nombres de presets
            for (int j = 0; j < presets.size(); ++j)
            {
                int presetId = nextId + j + 1;  // +1 porque el ID de la categoría es nextId
                presetIdToNameMap[presetId] = fullNames[j];  // Usar nombre completo con prefijo de categoría para BinaryData
            }

            nextId += static_cast<int>(presets.size()) + 1;
        }
    }

    // Añadir separador
    presetArea.presetMenu.addItem("---", nextId++);

    // Añadir user presets
    juce::StringArray userPresets;
    for (int i = 0; i < getUpdatedNumPresets(); i++) {
        userPresets.add(populatePresetFolder()[i].getFileNameWithoutExtension());
    }

    userPresets.sort(true);
    for (const auto& preset : userPresets)
    {
        presetArea.presetMenu.addItem(preset, nextId);
        presetIdToNameMap[nextId] = preset;  // Mapear user presets también
        nextId++;
    }

    // Restaurar selección previa si existe
    if (processor.getLastPreset() > 0) {
        presetArea.presetMenu.setSelectedId(processor.getLastPreset());
    }
}

void JCBReverbAudioProcessorEditor::savePresetFile()
{
    // Obtener estado del menú de presets y del processor
    juce::String currentText = presetArea.presetMenu.getText();
    juce::String processorText = processor.getPresetDisplayText();

    // Si no hay texto en el menú, usar el texto del processor
    if (currentText.isEmpty() && !processorText.isEmpty()) {
        currentText = processorText;
    }

    // Extraer el nombre del preset sin asterisco
    juce::String currentPresetName = currentText.endsWith("*") ?
        currentText.dropLastCharacters(1).trimEnd() : currentText;

    // Si no hay preset o es DEFAULT, ir a Save As
    if (currentPresetName.isEmpty() || currentPresetName == "DEFAULT") {
        saveAsPresetFile();
        return;
    }

    // Verificar si es un factory preset
    bool isFactoryPreset = currentPresetName.startsWith("[F] ");
    if (isFactoryPreset) {
        // Quitar el prefijo [F] para mostrar el nombre limpio
        juce::String cleanName = currentPresetName.substring(4);
        showCustomAlertDialog(JUCE_UTF8("Cannot overwrite"),
                            JUCE_UTF8("Factory Presets are read-only.\nUse 'Save As' to create a copy."));
        return;
    }

    // Si hay un preset cargado (modificado o no), ofrecer opciones
    // Mostrar diálogo si hay un preset cargado (modificado O no modificado)
    if (!currentPresetName.isEmpty()) {
        overwritePresetDialog = std::make_unique<CustomThreeButtonDialog>(
            "Overwrite \"" + currentPresetName + "\"",
            "",  // No mensaje adicional, el título es suficiente
            "Overwrite",
            "Save As",
            "Cancel"
        );

        overwritePresetDialog->onDialogClosed = [this, currentPresetName](bool wasAccepted) {
            if (wasAccepted) {
                int result = overwritePresetDialog->getSelectedButton();
                if (result == 1) { // Overwrite
                // Guardar directamente en el archivo existente
                auto presetFile = getPresetsFolder().getChildFile(currentPresetName + ".preset");
                auto state = processor.apvts.copyState();

                // Añadir estado del modo de visualización FFT/WAVE
                auto uiSettings = state.getOrCreateChildWithName("UISettings", nullptr);
                uiSettings.setProperty("displayModeIsFFT", processor.displayModeIsFFT, nullptr);

                std::unique_ptr<juce::XmlElement> xml(state.createXml());

                if (xml != nullptr) {
                    xml->writeTo(presetFile);

                    // Actualizar menú primero
                    refreshPresetMenu();

                    // No seleccionar el preset, solo mostrar su nombre
                    // Esto evita problemas con handleParameterChange
                    presetArea.presetMenu.setSelectedId(0);
                    presetArea.presetMenu.setTextWhenNothingSelected(currentPresetName);
                    presetArea.presetMenu.setTextItalic(false);

                    // Actualizar estado en el processor
                    processor.setPresetDisplayText(currentPresetName);
                    processor.setPresetTextItalic(false);
                    processor.setLastPreset(0);
                }
                } else if (result == 2) { // Guardar como...
                    saveAsPresetFile();
                }
                // result == 3 is Cancel, do nothing
            }

            // Limpiar el diálogo después de usarlo
            overwritePresetDialog.reset();
        };

        addChildComponent(overwritePresetDialog.get());
        overwritePresetDialog->showDialog();
    } else {
        // No hay preset cargado, ir directamente a "Save As..."
        saveAsPresetFile();
    }
}

void JCBReverbAudioProcessorEditor::saveAsPresetFile()
{
    // Crear y mostrar el diálogo personalizado
    savePresetDialog = std::make_unique<SavePresetDialog>("");
    savePresetDialog->onDialogClosed = [this](bool shouldSave) {
        if (shouldSave) {
            juce::String presetName = savePresetDialog->getPresetName();

            // No permitir usar el nombre DEFAULT
            if (presetName.toUpperCase() == "DEFAULT") {
                showCustomAlertDialog("Error",
                                    "Cannot use the name DEFAULT for a preset.");
                return;
            }

            // Verificar si el nombre coincide con algún factory preset
            for (const auto& factoryName : factoryPresetNames) {
                if (presetName.compareIgnoreCase(factoryName) == 0) {
                    showCustomAlertDialog(JUCE_UTF8("Reserved name"),
                                        JUCE_UTF8("Name reserved for Factory Preset.\nPlease choose another name."));
                    return;
                }
            }

            // Crear archivo con el nombre del preset
            juce::File presetFile = getPresetsFolder().getChildFile(presetName + ".preset");

            // Si el archivo ya existe, preguntar si sobrescribir
            if (presetFile.existsAsFile()) {
                showCustomConfirmDialog(JUCE_UTF8("Preset already exists"),
                                      JUCE_UTF8("Do you want to overwrite the existing preset?"),
                                      [this, presetFile, presetName](bool shouldOverwrite) {
                    if (shouldOverwrite) {
                        // Guardar el preset
                        auto state = processor.apvts.copyState();

                        // Añadir estado del modo de visualización FFT/WAVE
                        auto uiSettings = state.getOrCreateChildWithName("UISettings", nullptr);
                        uiSettings.setProperty("displayModeIsFFT", processor.displayModeIsFFT, nullptr);

                        std::unique_ptr<juce::XmlElement> xml(state.createXml());

                        if (xml != nullptr) {
                            xml->writeTo(presetFile);

                            // Actualizar el menú
                            refreshPresetMenu();

                            // No seleccionar el preset, solo mostrar su nombre
                            // Esto evita problemas con handleParameterChange
                            presetArea.presetMenu.setSelectedId(0);
                            presetArea.presetMenu.setTextWhenNothingSelected(presetName);
                            presetArea.presetMenu.setTextItalic(false);

                            // Actualizar estado en el processor
                            processor.setPresetDisplayText(presetName);
                            processor.setPresetTextItalic(false);
                            processor.setLastPreset(0);
                        }
                    }
                });
            } else {
                // Guardar directamente si no existe
                auto state = processor.apvts.copyState();

                // Añadir estado del modo de visualización FFT/WAVE
                auto uiSettings = state.getOrCreateChildWithName("UISettings", nullptr);
                uiSettings.setProperty("displayModeIsFFT", processor.displayModeIsFFT, nullptr);

                std::unique_ptr<juce::XmlElement> xml(state.createXml());

                if (xml != nullptr) {
                    xml->writeTo(presetFile);

                    // Actualizar el menú
                    refreshPresetMenu();

                    // No seleccionar el preset, solo mostrar su nombre
                    // Esto evita problemas con handleParameterChange
                    presetArea.presetMenu.setSelectedId(0);
                    presetArea.presetMenu.setTextWhenNothingSelected(presetName);
                    presetArea.presetMenu.setTextItalic(false);

                    // Actualizar estado en el processor
                    processor.setPresetDisplayText(presetName);
                    processor.setPresetTextItalic(false);
                    processor.setLastPreset(0);
                }
            }
        }

        // Limpiar el diálogo
        savePresetDialog.reset();
    };

    addChildComponent(savePresetDialog.get());
    savePresetDialog->showDialog();
}

void JCBReverbAudioProcessorEditor::deletePresetFile()
{
    int selectedId = presetArea.presetMenu.getSelectedId();
    juce::String presetName;

    if (selectedId > 0) {
        // Hay un preset seleccionado en el menú
        // Usar el mapeo que ya tiene el nombre correcto con "[F] " para factory presets
        if (presetIdToNameMap.find(selectedId) != presetIdToNameMap.end()) {
            presetName = presetIdToNameMap[selectedId];
        } else {
            presetName = presetArea.presetMenu.getItemText(selectedId - 1);
        }
    } else {
        // No hay selección, verificar si hay un preset modificado
        juce::String displayText = presetArea.presetMenu.getTextWhenNothingSelected();
        if (displayText.isEmpty()) {
            displayText = processor.getPresetDisplayText();
        }

        if (displayText.isEmpty()) {
            showCustomAlertDialog(JUCE_UTF8("Error"),
                                JUCE_UTF8("Ningún preset seleccionado."));
            return;
        }

        // Quitar asterisco si lo tiene
        presetName = displayText.endsWith("*") ?
            displayText.dropLastCharacters(1).trimEnd() : displayText;
    }

    // No permitir borrar DEFAULT ni factory presets
    if (presetName == "DEFAULT" || presetName.startsWith("[F] ")) {
        juce::String errorMsg = presetName == "DEFAULT" ?
            JUCE_UTF8("The DEFAULT preset cannot be deleted.") :
            JUCE_UTF8("Factory presets cannot be deleted.");
        showCustomAlertDialog(JUCE_UTF8("Error"), errorMsg);
        return;
    }

    showCustomConfirmDialog(JUCE_UTF8("Delete Preset"),
                            JUCE_UTF8("The preset \"") + presetName + JUCE_UTF8("\" will be moved to trash."),
                            [this, presetName](bool confirmed) {
        if (confirmed) {
            juce::File presetFile = getPresetsFolder().getChildFile(presetName + ".preset");

            if (presetFile.existsAsFile()) {
                presetFile.moveToTrash();

                // Actualizar el menú
                refreshPresetMenu();

                // Dejar el menú sin selección y sin texto
                presetArea.presetMenu.setSelectedId(0);
                presetArea.presetMenu.setTextWhenNothingSelected("");
                presetArea.presetMenu.setTextItalic(false);
                processor.setPresetDisplayText("");
                processor.setPresetTextItalic(false);
                processor.setLastPreset(0);

                // NO cargar DEFAULT - dejar los parámetros como están
            }
        }
    });
}

void JCBReverbAudioProcessorEditor::selectNextPreset()
{
    // Obtener todos los IDs seleccionables (excluyendo separadores y categorías)
    auto selectableIds = presetArea.presetMenu.getAllSelectableIds();

    if (selectableIds.empty()) return;

    int currentId = presetArea.presetMenu.getSelectedId();

    // Encontrar el índice actual en la lista de IDs seleccionables
    auto currentIt = std::find(selectableIds.begin(), selectableIds.end(), currentId);

    int nextId;
    if (currentIt == selectableIds.end() || currentIt == selectableIds.end() - 1) {
        // Si no se encuentra o es el último, ir al primero
        nextId = selectableIds.front();
    } else {
        // Ir al siguiente
        nextId = *(++currentIt);
    }

    presetArea.presetMenu.setSelectedId(nextId);

    // Trigger onChange para cargar el preset
    if (presetArea.presetMenu.onChange) {
        presetArea.presetMenu.onChange();
    }
}

void JCBReverbAudioProcessorEditor::selectPreviousPreset()
{
    // Obtener todos los IDs seleccionables (excluyendo separadores y categorías)
    auto selectableIds = presetArea.presetMenu.getAllSelectableIds();

    if (selectableIds.empty()) return;

    int currentId = presetArea.presetMenu.getSelectedId();

    // Encontrar el índice actual en la lista de IDs seleccionables
    auto currentIt = std::find(selectableIds.begin(), selectableIds.end(), currentId);

    int prevId;
    if (currentIt == selectableIds.end() || currentIt == selectableIds.begin()) {
        // Si no se encuentra o es el primero, ir al último
        prevId = selectableIds.back();
    } else {
        // Ir al anterior
        prevId = *(--currentIt);
    }

    presetArea.presetMenu.setSelectedId(prevId);

    // Trigger onChange para cargar el preset
    if (presetArea.presetMenu.onChange) {
        presetArea.presetMenu.onChange();
    }
}

//==============================================================================
// DIÁLOGOS Y OVERLAYS
//==============================================================================
void JCBReverbAudioProcessorEditor::showCustomConfirmDialog(const juce::String& message,
                                                          const juce::String& subMessage,
                                                          std::function<void(bool)> callback,
                                                          const juce::String& confirmText,
                                                          const juce::String& cancelText)
{
    // Combinar mensaje principal y submensaje si existe
    juce::String fullMessage = message;
    if (subMessage.isNotEmpty()) {
        fullMessage += "\n\n" + subMessage;
    }

    // Usar el nuevo diálogo personalizado
    deleteConfirmDialog = std::make_unique<CustomConfirmDialog>("Confirmation", fullMessage, confirmText, cancelText);
    deleteConfirmDialog->onDialogClosed = callback;
    addChildComponent(deleteConfirmDialog.get());
    deleteConfirmDialog->showDialog();
}

void JCBReverbAudioProcessorEditor::showCustomAlertDialog(const juce::String& title, const juce::String& message)
{
    // Crear un diálogo de alerta simple con solo OK
    alertDialog = std::make_unique<CustomAlertDialog>(title, message);
    alertDialog->onDialogClosed = [](bool) {}; // Callback vacío
    addChildComponent(alertDialog.get());
    alertDialog->showDialog();
}

void JCBReverbAudioProcessorEditor::showCredits()
{
    // Desactivar estados operacionales antes de mostrar créditos (consistencia con DIAGRAM)
    parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
    // sidechainControls.soloScButton.setToggleState(false, juce::sendNotification);

    if (creditsOverlay == nullptr)
    {
        // Obtener el formato del plugin desde el processor
        juce::String format = processor.getPluginFormat();

        creditsOverlay = std::make_unique<CreditsOverlay>(format);
        creditsOverlay->setBounds(getLocalBounds());
        creditsOverlay->onClose = [this]() {
            hideCredits();
        };

        addAndMakeVisible(creditsOverlay.get());
        creditsOverlay->grabKeyboardFocus();
    }
}

void JCBReverbAudioProcessorEditor::hideCredits()
{
    if (creditsOverlay != nullptr)
    {
        removeChildComponent(creditsOverlay.get());
        creditsOverlay.reset();
    }
}

//==============================================================================
// SISTEMA DE TOOLTIPS
//==============================================================================
void JCBReverbAudioProcessorEditor::updateTodoButtonTexts()
{
    // Actualizar tooltips de botones por hacer para consistencia
    utilityButtons.hqButton.setTooltip(getTooltipText("hq"));
    utilityButtons.dualMonoButton.setTooltip(getTooltipText("dualmono"));
    utilityButtons.msButton.setTooltip(getTooltipText("ms"));
    topButtons.abStateButton.setTooltip(getTooltipText("abstate"));
    utilityButtons.midiLearnButton.setTooltip(getTooltipText("midilearn"));
    // Stereo Linked button - se maneja en updateAllTooltips()
}

void JCBReverbAudioProcessorEditor::updateAllTooltips()
{
    // Título
    titleLink.setTooltip(getTooltipText("title"));

    trimSlider.setTooltip(getTooltipText("trim"));
    makeupSlider.setTooltip(getTooltipText("makeup"));

    sidechainControls.hpfSlider.setTooltip(getTooltipText("hpf"));
    sidechainControls.lpfSlider.setTooltip(getTooltipText("lpf"));
    sidechainControls.scButton.setTooltip(getTooltipText("sc"));

    leftKnobs.reflectSlider.setTooltip(getTooltipText("reflect"));
    leftKnobs.sizeSlider.setTooltip(getTooltipText("size"));
    leftKnobs.dampSlider.setTooltip(getTooltipText("damp"));
    leftKnobs.drywetSlider.setTooltip(getTooltipText("drywet"));
    leftKnobs.stSlider.setTooltip(getTooltipText("stereo"));
    leftKnobs.freezeButton.setTooltip(getTooltipText("freeze"));


    // Área de presets
    presetArea.saveButton.setTooltip(getTooltipText("save"));
    presetArea.saveAsButton.setTooltip(getTooltipText("saveas"));
    presetArea.deleteButton.setTooltip(getTooltipText("delete"));
    presetArea.backButton.setTooltip(getTooltipText("back"));
    presetArea.nextButton.setTooltip(getTooltipText("next"));

    // Utility buttons
    utilityButtons.undoButton.setTooltip(getTooltipText("undo"));
    utilityButtons.redoButton.setTooltip(getTooltipText("redo"));
    utilityButtons.resetGuiButton.setTooltip(getTooltipText("resetgui"));
    utilityButtons.runGraphicsButton.setTooltip(getTooltipText("graphics"));
    utilityButtons.zoomButton.setTooltip(getTooltipText("zoom"));
    centerButtons.diagramButton.setTooltip(getTooltipText("diagram"));
    utilityButtons.tooltipToggleButton.setTooltip(getTooltipText("tooltiptoggle"));
    utilityButtons.tooltipLangButton.setTooltip(getTooltipText("tooltiplang"));

    // Botones de parámetros
    parameterButtons.bypassButton.setTooltip(getTooltipText("bypass"));

    // Tabs y controles de la derecha (EQ / COMP)
    rightTabs.eqTab.setTooltip(getTooltipText("eqtab"));
    rightTabs.compTab.setTooltip(getTooltipText("comptab"));

    eqControls.eqOnButton.setTooltip(getTooltipText("eqon"));
    eqControls.lsgSlider.setTooltip(getTooltipText("lsg"));
    eqControls.pgSlider.setTooltip(getTooltipText("pg"));
    eqControls.hsgSlider.setTooltip(getTooltipText("hsg"));
    eqControls.lsfSlider.setTooltip(getTooltipText("lsf"));
    eqControls.pfSlider.setTooltip(getTooltipText("pf"));
    eqControls.hsfSlider.setTooltip(getTooltipText("hsf"));

    compControls.compOnButton.setTooltip(getTooltipText("compon"));
    compControls.pumpButton.setTooltip(getTooltipText("pump"));
    compControls.thdSlider.setTooltip(getTooltipText("thd"));
    compControls.ratioSlider.setTooltip(getTooltipText("ratio"));
    compControls.atkSlider.setTooltip(getTooltipText("atk"));
    compControls.relSlider.setTooltip(getTooltipText("rel"));
    compControls.gainSlider.setTooltip(getTooltipText("compgain"));

    // Actualizar tooltips de botones "por hacer"
    updateTodoButtonTexts();

    // Botones de utilidad - fila inferior
    utilityButtons.stereoLinkedButton.setTooltip(getTooltipText("link"));
}

juce::String JCBReverbAudioProcessorEditor::getTooltipText(const juce::String& key)
{
    if (currentLanguage == TooltipLanguage::Spanish)
    {
        // Spanish tooltips
        if (key == "trim") return JUCE_UTF8("TRIM: ganancia de entrada a la reverb\nAjusta el nivel antes del procesamiento\nRango: -12 a +12 dB | Por defecto: 0 dB");
        if (key == "makeup") return JUCE_UTF8("OUTPUT: ganancia de salida (sólo WET)\nNo afecta la rama DRY/Dry-Wet\nRango: -24 a +12 dB | Por defecto: 0 dB");

        if (key == "hpf") return JUCE_UTF8("HPF: filtro paso alto 12 dB/oct\nAtenúa frecuencias por debajo del corte\nRango: 20 a 5000 Hz | Por defecto: 100 Hz");
        if (key == "lpf") return JUCE_UTF8("LPF: filtro paso bajo 12 dB/oct\nAtenúa frecuencias por encima del corte\nRango: 100 Hz a 20 kHz | Por defecto: 20 kHz");
        if (key == "sc") return JUCE_UTF8("FILTERS: activa/desactiva los filtros HPF/LPF (12 dB/oct).\nHPF y LPF se aplican según sus controles dedicados.\nValor por defecto: OFF");

        if (key == "reflect") return JUCE_UTF8("REFLECT: cantidad de reflexiones\nControla la retroalimentación/densidad de la reverb\nRango: 0% a 100% | Por defecto: 74 %");
        if (key == "size") return JUCE_UTF8("SIZE: tamaño del tanque de filtros peine\nSimula el tamaño del espacio\nRango: 0.1 a 4 | Por defecto: 1.5");

        if (key == "drywet") return JUCE_UTF8("DRY/WET: mezcla entre señal original y procesada\nControla el balance final de salida\nRango: 0 a 100% | Por defecto: 100%");
        //if (key == "lookahead") return JUCE_UTF8("LOOKAHEAD: anticipación para evitar distorsión\nEvita overshooting en transitorios rápidos\nRango: 0 a 5 ms | Por defecto: 0 ms");

        if (key == "damp") return JUCE_UTF8("DAMP: filtro en los feedback de los tanques de comb\nLPF 1er orden dentro del feedback\nRango: 0 a 100% | Por defecto: 0 %");
        if (key == "stereo") return JUCE_UTF8("STEREO: stereo image width\nMS matrix with delay on right channel\nRange: 0% to 100% | Default: 50%");
        if (key == "freeze") return JUCE_UTF8("FREEZE: congela el tanque de combs\nActivado silencia la entrada y la cadena DRY\nRango: OFF/ON | Por defecto: OFF");

        // Tabs y EQ (derecha)
        if (key == "eqtab") return JUCE_UTF8("Pestaña EQ: muestra controles de ecualización\nAjusta frecuencias y ganancias");
        if (key == "comptab") return JUCE_UTF8("Pestaña COMP: muestra controles del compresor\nConfigura dinámica y PUMP");
        if (key == "eqon") return JUCE_UTF8("EQ ON/OFF: activa o desactiva la EQ\nAl OFF, los controles quedan atenuados");
        if (key == "lsf") return JUCE_UTF8("LSF: frecuencia del Low Shelf\nPunto de giro de graves\nRango: 20 a 500 Hz");
        if (key == "pf")  return JUCE_UTF8("PF: frecuencia del filtro Peak (campana)\nCentro de realce/atenuación en medios\nRango: 500 a 2500 Hz");
        if (key == "hsf") return JUCE_UTF8("HSF: frecuencia del High Shelf\nPunto de giro de agudos\nRango: 2.5 a 15 kHz");
        if (key == "lsg") return JUCE_UTF8("LSG: ganancia del Low Shelf\nAjuste de graves en dB\nRango: -24 a +24 dB");
        if (key == "pg")  return JUCE_UTF8("PG: ganancia del filtro Peak\nRealce/atenuación en medios\nRango: -24 a +24 dB");
        if (key == "hsg") return JUCE_UTF8("HSG: ganancia del High Shelf\nAjuste de agudos en dB\nRango: -24 a +24 dB");

        // Compresor (derecha)
        if (key == "compon") return JUCE_UTF8("COMP ON/OFF: activa o desactiva el compresor\nAl OFF se bloquea PUMP y los controles quedan atenuados");
        if (key == "thd")   return JUCE_UTF8("THD: umbral del compresor\nNivel a partir del cual comprime\nRango: -60 a 0 dB");
        if (key == "ratio") return JUCE_UTF8("RATIO: relación de compresión\nCuánto reduce por encima del umbral\nRango: 1:1 a 20:1");
        if (key == "atk")   return JUCE_UTF8("ATK: tiempo de ataque\nVelocidad de reacción al superar el umbral\nRango: 1 a 750 ms");
        if (key == "rel")   return JUCE_UTF8("REL: tiempo de relajación\nVelocidad de retorno tras compresión\nRango: 15 a 2000 ms");
        if (key == "compgain") return JUCE_UTF8("GAIN: ganancia de compensación del compresor\nAjusta el nivel tras comprimir\nRango: -6 a +6 dB");
        if (key == "pump")  return JUCE_UTF8("PUMP: modo de bombeo/ducking\nRealza el efecto de bombeo impulsado por el compresor\nSolo disponible cuando COMP está ON");


        if (key == "title") return JUCE_UTF8("JCBReverb: reverb tipo Schoroeder v1.0.0-alpha.2\nPlugin de audio open source\nClick para créditos");
        if (key == "save") return JUCE_UTF8("SAVE: guarda el preset actual\nSobrescribe el preset seleccionado con valores actuales\nNo funciona con DEFAULT");
        if (key == "saveas") return JUCE_UTF8("SAVE AS: guarda como nuevo preset\nCrea un nuevo archivo de preset con los valores actuales\nPermite crear presets personalizados");
        if (key == "delete") return JUCE_UTF8("BORRAR: elimina el preset seleccionado\nRequiere confirmación antes de borrar");
        if (key == "back") return JUCE_UTF8("ANTERIOR: selecciona el preset previo\nNavega hacia atrás en la lista de presets");
        if (key == "next") return JUCE_UTF8("SIGUIENTE: selecciona el próximo preset\nNavega hacia adelante en la lista de presets");
        if (key == "undo") return JUCE_UTF8("DESHACER: revierte el último cambio\nDeshace modificación realizada manualmente por el usuario\nHistorial: hasta 20 pasos");
        if (key == "redo") return JUCE_UTF8("REHACER: aplica el cambio deshecho\nRehace modificación manual previamente revertida\nHistorial: hasta 20 pasos");
        if (key == "resetgui") return JUCE_UTF8("SIZE: cicla entre tamaños de ventana\nActual → Máximo → Mínimo → Actual\nAjuste rápido del tamaño del plugin");
        if (key == "bypass") return JUCE_UTF8("BYPASS: desactiva el procesamiento del plugin\nParámetro global, no automatizable. Transición suave\nRango: OFF/ON | Por defecto: OFF");
        if (key == "graphics") return JUCE_UTF8("GRAPHICS: alterna entre FFT y Wave\nFFT: analizador de espectro | Wave: forma de onda\nClick para cambiar de modo");
        if (key == "zoom") return JUCE_UTF8("ZOOM: cicla entre vista normal y ampliada del FFT\nNormal: -80 a 0dB | x2: -48 a 0dB\nSolo activo en modo FFT");
        if (key == "diagram") return JUCE_UTF8("DIAGRAM: muestra diagrama de bloques del procesador\nSolo visual; bloquea clics al fondo");
        if (key == "tooltiptoggle") return JUCE_UTF8("TOOLTIP: muestra/oculta los tooltips de ayuda\nActiva o desactiva las ventanas de ayuda emergentes");
        if (key == "tooltiplang") return JUCE_UTF8("IDIOMA: cambia entre español e inglés.\nAlterna el idioma de los tooltips.");
        if (key == "link") return JUCE_UTF8("STEREO LINKED: siempre activo.\nEl plugin solo funciona en modo stereo linked.\nAmbos canales siempre están vinculados");
        if (key == "hq") return JUCE_UTF8("POR HACER: Habilita oversampling para mayor calidad.");
        if (key == "dualmono") return JUCE_UTF8("POR HACER: Procesa canales L/R independientemente.");
        if (key == "ms") return JUCE_UTF8("POR HACER: Procesa en formato Mid/Side.");
        if (key == "abstate") return JUCE_UTF8("Alterna entre dos configuraciones A/B para comparar ajustes.");
        if (key == "midilearn") return JUCE_UTF8("POR HACER: Asigna control MIDI.");
        if (key == "abcopyatob") return JUCE_UTF8("Copiar A a B");
        if (key == "abcopybtoa") return JUCE_UTF8("Copiar B a A");
    }
    else
    {
        // English tooltips
        if (key == "trim") return JUCE_UTF8("TRIM: input gain to the reverb\nAdjusts the level before processing\nRange: -12 to +12 dB | Default: 0 dB");
        if (key == "makeup") return JUCE_UTF8("OUTPUT: output gain (WET only)\nDoes not affect the DRY/Dry-Wet path\nRange: -24 to +12 dB | Default: 0 dB");

        if (key == "hpf") return JUCE_UTF8("HPF: high-pass filter 12 dB/oct\nAttenuates frequencies below the cutoff\nRange: 20 to 5000 Hz | Default: 100 Hz");
        if (key == "lpf") return JUCE_UTF8("LPF: low-pass filter 12 dB/oct\nAttenuates frequencies above the cutoff\nRange: 100 Hz to 20 kHz | Default: 20 kHz");
        if (key == "sc") return JUCE_UTF8("FILTERS: enable/disable HPF/LPF (12 dB/oct)\nHPF and LPF are applied according to their dedicated controls\nDefault: OFF");

        if (key == "reflect") return JUCE_UTF8("REFLECT: amount of reflections\nControls reverb feedback/density\nRange: 0% to 100% | Default: 74 %");
        if (key == "size") return JUCE_UTF8("SIZE: comb filter tank size\nSimulates the size of the space\nRange: 0.1 to 4 | Default: 1.5");

        if (key == "drywet") return JUCE_UTF8("DRY/WET: mix between original and processed signal\nControls the final output balance\nRange: 0 to 100% | Default: 100%");
        if (key == "damp") return JUCE_UTF8("DAMP: damping filter in the comb tank feedback\n1st-order LPF inside the feedback loop\nRange: 0 to 100% | Default: 0 %");
        if (key == "stereo") return JUCE_UTF8("STEREO: stereo image width\nMS matrix with delay on right channel\nRange: 0% to 100% | Default: 50%");
        if (key == "freeze") return JUCE_UTF8("FREEZE: freezes the comb tank\nWhen enabled, input and DRY chain are muted\nRange: OFF/ON | Default: OFF");

        // Tabs & EQ (right)
        if (key == "eqtab") return JUCE_UTF8("EQ tab: shows equalizer controls\nAdjust frequencies and gains");
        if (key == "comptab") return JUCE_UTF8("COMP tab: shows compressor controls\nSet dynamics and PUMP");
        if (key == "eqon") return JUCE_UTF8("EQ ON/OFF: enable or disable the EQ\nWhen OFF, controls are dimmed");
        if (key == "lsf") return JUCE_UTF8("LSF: Low Shelf frequency\nShelf pivot for lows\nRange: 20 to 500 Hz");
        if (key == "pf")  return JUCE_UTF8("PF: Peak filter frequency\nCenter frequency for mid boost/cut\nRange: 500 to 2500 Hz");
        if (key == "hsf") return JUCE_UTF8("HSF: High Shelf frequency\nShelf pivot for highs\nRange: 2.5 to 15 kHz");
        if (key == "lsg") return JUCE_UTF8("LSG: Low Shelf gain\nBass adjustment in dB\nRange: -24 to +24 dB");
        if (key == "pg")  return JUCE_UTF8("PG: Peak gain\nMidrange boost/cut in dB\nRange: -24 to +24 dB");
        if (key == "hsg") return JUCE_UTF8("HSG: High Shelf gain\nHighs adjustment in dB\nRange: -24 to +24 dB");

        // Compressor (right)
        if (key == "compon") return JUCE_UTF8("COMP ON/OFF: enable or disable the compressor\nWhen OFF, PUMP is blocked and controls are dimmed");
        if (key == "thd")   return JUCE_UTF8("THD: compressor threshold\nLevel above which compression occurs\nRange: -60 to 0 dB");
        if (key == "ratio") return JUCE_UTF8("RATIO: compression ratio\nHow much reduction above threshold\nRange: 1:1 to 20:1");
        if (key == "atk")   return JUCE_UTF8("ATK: attack time\nHow fast it reacts above threshold\nRange: 1 to 750 ms");
        if (key == "rel")   return JUCE_UTF8("REL: release time\nHow fast it recovers after compression\nRange: 15 to 2000 ms");
        if (key == "compgain") return JUCE_UTF8("GAIN: compressor makeup gain\nAdjusts level after compression\nRange: -6 to +6 dB");
        if (key == "pump")  return JUCE_UTF8("PUMP: pumping/ducking mode\nEnhances compressor-driven pumping effect\nOnly available when COMP is ON");



        if (key == "title") return JUCE_UTF8("JCBReverb: Schroeder-type reverb v1.0.0-alpha.2\nOpen source audio plugin\nClick for credits");
        if (key == "save") return JUCE_UTF8("SAVE: overwrite current preset\nReplaces the selected preset with current values\nNot available for DEFAULT");
        if (key == "saveas") return JUCE_UTF8("SAVE AS: save as new preset\nCreates a new preset file with current values\nAllows creating custom presets");
        if (key == "delete") return JUCE_UTF8("DELETE: remove selected preset\nRequires confirmation before deletion");
        if (key == "back") return JUCE_UTF8("PREVIOUS: select previous preset\nNavigate backwards in preset list");
        if (key == "next") return JUCE_UTF8("NEXT: select next preset\nNavigate forwards in preset list");
        if (key == "undo") return JUCE_UTF8("UNDO: revert last change\nUndoes manual user modification\nHistory: up to 20 steps");
        if (key == "redo") return JUCE_UTF8("REDO: apply reverted change\nReapplies previously undone modification\nHistory: up to 20 steps");
        if (key == "resetgui") return JUCE_UTF8("SIZE: cycle window size\nCurrent → Maximum → Minimum → Current\nQuick adjustment of plugin window size");
        if (key == "bypass") return JUCE_UTF8("BYPASS: disables plugin processing\nGlobal parameter, not automatable. Smooth transition\nRange: OFF/ON | Default: OFF");
        if (key == "graphics") return JUCE_UTF8("GRAPHICS: toggle between FFT and Wave\nFFT: spectrum analyzer | Wave: waveform display\nClick to switch modes");
        if (key == "zoom") return JUCE_UTF8("ZOOM: cycle FFT zoom view\nNormal: -80 to 0 dB | x2: -48 to 0 dB\nOnly active in FFT mode");
        if (key == "diagram") return JUCE_UTF8("DIAGRAM: show processor block diagram\nVisual only; blocks clicks to the background");
        if (key == "tooltiptoggle") return JUCE_UTF8("TOOLTIP: show/hide help tooltips\nEnable or disable popup help windows");
        if (key == "tooltiplang") return JUCE_UTF8("LANGUAGE: switch between Spanish and English\nToggles tooltip language");
        if (key == "link") return JUCE_UTF8("STEREO LINKED: always active\nThe plugin only works in stereo linked mode\nBoth channels are always coupled");
        if (key == "hq") return JUCE_UTF8("TODO: Enable oversampling for higher quality");
        if (key == "dualmono") return JUCE_UTF8("TODO: Process L/R channels independently");
        if (key == "ms") return JUCE_UTF8("TODO: Process in Mid/Side format");
        if (key == "abstate") return JUCE_UTF8("Toggle between two A/B states to compare settings");
        if (key == "midilearn") return JUCE_UTF8("TODO: Assign MIDI control");
        if (key == "abcopyatob") return JUCE_UTF8("Copy A to B");
        if (key == "abcopybtoa") return JUCE_UTF8("Copy B to A");
    }

    return "";
}


//==============================================================================
// HELPERS DE UI
//==============================================================================
void JCBReverbAudioProcessorEditor::applyAlphaToMainControls(float alpha)
{
    juce::ignoreUnused(alpha);
}


// Nota: La funcionalidad de visualización de código ahora se maneja por CodeWindow desde DIAGRAM



//==============================================================================
// THREAD SAFETY Y AUTOMATIZACIÓN
//==============================================================================
void JCBReverbAudioProcessorEditor::queueParameterUpdate(const juce::String& paramID, float normalizedValue)
{
    {
        std::lock_guard<std::mutex> lock(parameterUpdateMutex);

        // Check if this parameter is already queued
        auto it = std::ranges::find_if(pendingParameterUpdates,
                               [&paramID](const DeferredParameterUpdate& update) {
                                   return update.paramID == paramID;
                               });

        if (it != pendingParameterUpdates.end()) {
            // Actualizar entrada existente
            it->normalizedValue = normalizedValue;
        } else {
            // Add new entry
            pendingParameterUpdates.push_back({paramID, normalizedValue});
        }
    }

    hasPendingParameterUpdates.store(true);
}

void JCBReverbAudioProcessorEditor::processPendingParameterUpdates()
{
    if (!hasPendingParameterUpdates.exchange(false)) {
        return;
    }

    std::vector<DeferredParameterUpdate> updates;
    {
        std::lock_guard<std::mutex> lock(parameterUpdateMutex);
        updates = std::move(pendingParameterUpdates);
        pendingParameterUpdates.clear();
    }

    // Establecer flag para prevenir transacciones de undo durante procesamiento de queue
    isProcessingQueue = true;

    // Process all updates on the message thread
    for (const auto& update : updates) {
        if (auto* param = processor.apvts.getParameter(update.paramID)) {
            // Usar beginChangeGesture/endChangeGesture para prevenir transacciones de undo
            param->beginChangeGesture();
            param->setValueNotifyingHost(update.normalizedValue);
            param->endChangeGesture();

            // CRÍTICO: Sincronización directa con Gen~ DSP
            // Esto asegura que los valores del DEFAULT button lleguen al DSP
            // Convertir valor normalizado a valor real usando el rango del parámetro
            if (auto* floatParam = dynamic_cast<juce::AudioParameterFloat*>(param)) {
                float realValue = floatParam->getNormalisableRange().convertFrom0to1(update.normalizedValue);

                if (update.paramID == "d_ATK" || update.paramID == "e_REL") {
                    // Debug info for DEFAULT preset parameter updates
                }

                // Llamar al método parameterChanged del processor para sincronizar con Gen~
                processor.parameterChanged(update.paramID, realValue);
            }

            // Manejo de AudioParameterBool para sincronización con Gen~
            if (dynamic_cast<juce::AudioParameterBool*>(param)) {
                float realValue = update.normalizedValue >= 0.5f ? 1.0f : 0.0f;


                // Llamar al método parameterChanged del processor para sincronizar con Gen~
                processor.parameterChanged(update.paramID, realValue);
            }
        }
    }

    // Visual feedback (cambios de alpha) se maneja en timerCallback() para updates consistentes

    // Limpiar flag después del procesamiento
    isProcessingQueue = false;
}

//==============================================================================
// DIAGRAM Y CODE WINDOW
//==============================================================================

void JCBReverbAudioProcessorEditor::showDiagram()
{
    // Thread-safe: usar MessageManager::callAsync para UI pesadas
    juce::Component::SafePointer<JCBReverbAudioProcessorEditor> safeThis(this);

    juce::MessageManager::callAsync([safeThis]() {
        if (!safeThis) return;

        // Crear overlay si no existe
        if (!safeThis->diagramOverlay)
        {
            safeThis->diagramOverlay = std::make_unique<DiagramOverlay>(*safeThis);
        }

        // Configurar y mostrar
        safeThis->addChildComponent(safeThis->diagramOverlay.get());
        safeThis->diagramOverlay->setBounds(safeThis->getLocalBounds());
        safeThis->diagramOverlay->setVisible(true);
        safeThis->diagramOverlay->toFront(true);
        safeThis->centerButtons.diagramButton.setToggleState(true, juce::dontSendNotification);
    });
}

void JCBReverbAudioProcessorEditor::hideDiagram()
{
    if (diagramOverlay && diagramOverlay->isVisible())
    {
        diagramOverlay->setVisible(false);
        removeChildComponent(diagramOverlay.get());
    }
    centerButtons.diagramButton.setToggleState(false, juce::dontSendNotification);
}

void JCBReverbAudioProcessorEditor::hideCodeWindow()
{
    if (codeWindow && codeWindow->isVisible())
    {
        codeWindow->setVisible(false);
        removeChildComponent(codeWindow.get());
    }
}

juce::String JCBReverbAudioProcessorEditor::loadCodeFromFile(const juce::String& blockName)
{
    // Thread-safe: usar cache pre-cargado en lugar de leer BinaryData cada vez
    if (codeContentCacheInitialized && codeContentCache.contains(blockName)) {
        return codeContentCache[blockName];
    }

    // Fallback si el cache no está inicializado o no se encuentra el bloque
    return "// Code for " + blockName + "\n\n// Content not found in cache.\n// Please report this issue.\n\n// Basic functionality:\n" + getBasicBlockDescription(blockName);
}

void JCBReverbAudioProcessorEditor::initializeCodeContentCache()
{
    // Code windows for DIAGRAM have been removed; keep an empty cache to satisfy calls.
    codeContentCache.clear();
    codeContentCacheInitialized = true;
}

juce::String JCBReverbAudioProcessorEditor::getBasicBlockDescription(const juce::String& blockName)
{
    if (blockName == "TRIM IN") {
        return "// Input trim gain applied to main signal\ninput_trimmed = input * dbtoa(trim_db);";
    } else if (blockName == "OUTPUT") {
        return "// Final output with any additional processing\nfinal_output = output_stage(processed_signal);";
    } else {
        return "// Generic Gen~ block processing\n// See Max patch for detailed implementation";
    }
}

// Función helper para obtener índice de parámetro por ID (robusta, compatible con el futuro)
int JCBReverbAudioProcessorEditor::getParameterIndexByID(const juce::String& parameterID)
{
    auto& params = processor.getParameters();
    for (int i = 0; i < params.size(); ++i) {
        if (auto* param = dynamic_cast<juce::AudioProcessorParameterWithID*>(params[i])) {
            if (param->paramID == parameterID) {
                return i;
            }
        }
    }
    return -1; // Parámetro no encontrado
}

int JCBReverbAudioProcessorEditor::getControlParameterIndex(juce::Component& control)
{
    auto resolve = [this](const char* parameterID) -> int
    {
        return getParameterIndexByID(parameterID);
    };

    // Trim sliders over the meters
    if (&control == &trimSlider)       return resolve("a_INPUT");
    if (&control == &makeupSlider)     return resolve("m_OUTPUT");

    // Main reverb knobs
    if (&control == &leftKnobs.reflectSlider) return resolve("c_REFLECT");
    if (&control == &leftKnobs.sizeSlider)    return resolve("e_SIZE");
    if (&control == &leftKnobs.drywetSlider)  return resolve("b_DRYWET");
    if (&control == &leftKnobs.dampSlider)    return resolve("d_DAMP");
    if (&control == &leftKnobs.stSlider)      return resolve("f_ST");
    if (&control == &leftKnobs.freezeButton)  return resolve("g_FREEZE");

    // Input filtering section
    if (&control == &sidechainControls.hpfSlider) return resolve("l_HPF");
    if (&control == &sidechainControls.lpfSlider) return resolve("k_LPF");
    if (&control == &sidechainControls.scButton)  return resolve("y_FILTERS");

    // EQ tab controls
    if (&control == &eqControls.eqOnButton)   return resolve("q_ONOFFEQ");
    if (&control == &eqControls.lsfSlider)    return resolve("n_LOWFREQ");
    if (&control == &eqControls.pfSlider)     return resolve("o_PEAKFREQ");
    if (&control == &eqControls.hsfSlider)    return resolve("p_HIFREQ");
    if (&control == &eqControls.lsgSlider)    return resolve("h_LOWGAIN");
    if (&control == &eqControls.pgSlider)     return resolve("i_PEAKGAIN");
    if (&control == &eqControls.hsgSlider)    return resolve("j_HIGAIN");

    // Compressor tab controls
    if (&control == &compControls.compOnButton) return resolve("r_ONOFFCOMP");
    if (&control == &compControls.thdSlider)    return resolve("s_THD");
    if (&control == &compControls.ratioSlider)  return resolve("t_RATIO");
    if (&control == &compControls.atkSlider)    return resolve("u_ATK");
    if (&control == &compControls.relSlider)    return resolve("v_REL");
    if (&control == &compControls.gainSlider)   return resolve("w_MAKEUP");
    if (&control == &compControls.pumpButton)   return resolve("x_PUMP");

    // All other components are visual-only or not exposed as automatable parameters
    return -1;
}

void JCBReverbAudioProcessorEditor::applyMeterDecayIfNeeded()
{
    // Sistema universal de decay para todos los DAWs
    // Basado en la solución recomendada en los foros de JUCE
    // Implementación profesional: decay siempre activo
    
    // Los medidores decaen naturalmente por inactividad
    // Los repaints se manejan automáticamente por el timer normal del editor
}

void JCBReverbAudioProcessorEditor::updateARButtonText()
{
    // En el original ExpansorGate manejaba el texto dinámico AR OFF/AR ON
    // En este procesador no hay AUTOREL independiente
}


//==============================================================================
// SPECTRUM ANALYZER SUPPORT
//==============================================================================

void JCBReverbAudioProcessorEditor::toggleDisplayMode()
{
    // Alternar entre modos FFT y Waveform
    if (currentDisplayMode == DisplayMode::FFT)
    {
        applyDisplayMode(false);
    }
    else
    {
        applyDisplayMode(true);
    }
}

void JCBReverbAudioProcessorEditor::applyDisplayMode(bool isFFT)
{
    processor.displayModeIsFFT = isFFT;
    currentDisplayMode = isFFT ? DisplayMode::FFT : DisplayMode::Waveform;

    // Visibilidad de componentes
    spectrumAnalyzer.setVisible(isFFT);
    waveformDisplay.setVisible(!isFFT);

    // Botón
    utilityButtons.runGraphicsButton.setButtonText(isFFT ? "FFT" : "wave");
    utilityButtons.runGraphicsButton.setColour(
        juce::TextButton::buttonColourId,
        isFFT ? juce::Colours::transparentBlack : DarkTheme::accent.withAlpha(0.3f));

    // Zoom button estado
    utilityButtons.zoomButton.setAlpha(1.0f);
    utilityButtons.zoomButton.setEnabled(true);
    utilityButtons.zoomButton.setButtonText(
        isFFT ? (spectrumAnalyzer.getZoomEnabled() ? "zoom x2" : "zoom")
              : (waveformDisplay.getZoomEnabled() ? "zoom x2" : "zoom"));

    handleParameterChange();
    repaint();
}
