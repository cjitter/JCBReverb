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

// Listener para cambios en el parámetro o_BAND (selección de banda)

// Placeholder para otros listeners (se implementarán cuando sea necesario)
// TransferFunctionParameterListener eliminado - no aplica a reverb

// Listeners obsoletos eliminados - no son necesarios para reverb




// TiltParameterListener eliminado - no existe s_TILTON en reverb

// ToneLpfParameterListener eliminado - q_TONEON es de distorsión, no reverb

//==============================================================================
// CONSTRUCTOR Y DESTRUCTOR
//==============================================================================
JCBReverbAudioProcessorEditor::JCBReverbAudioProcessorEditor (JCBReverbAudioProcessor& p, juce::UndoManager& um)
    : AudioProcessorEditor (&p), 
      processor (p), 
      undoManager (um),
      // CRASH FIX: Initialize with safe dummy functions, configure real ones later
      // Orden corregido siguiendo declaraciones en .h (línea 235, 242-244)
    // distortionCurveDisplay(processor.apvts),    // Declarado primero en .h (línea 235)
      // TEMPORAL: Comentado para evitar crash - necesita reimplementación
      // spectrumAnalyzer(processor.apvts),          // Declarado segundo en .h
      inputMeterL([]() { return -100.0f; }),      // Safe dummy value for input meters  
      inputMeterR([]() { return -100.0f; }),      // Safe dummy value for input meters
      outputMeterL([]() { return -100.0f; }),     // Safe dummy value for output meters
      outputMeterR([]() { return -100.0f; })      // Safe dummy value for output meters
      // scMeterL([&p](){ return p.getSCValue(0); }), // SC meter L
      // scMeterR([&p](){ return p.getSCValue(1); }) // SC meter R
{
    // Inicializar LookAndFeel personalizado para el botón FILTERS
    filtersButtonLAF = std::make_unique<FiltersButtonLookAndFeel>();
    soloButtonLAF = std::make_unique<SoloButtonLookAndFeel>();
    reversedGradientButtonLAF = std::make_unique<ReversedGradientButtonLookAndFeel>();
    tealGradientButtonLAF = std::make_unique<TealGradientButtonLookAndFeel>();
    coralGradientButtonLAF = std::make_unique<CoralGradientButtonLookAndFeel>();
    transparentButtonLAF = std::make_unique<TransparentButtonLookAndFeel>();
    
    // Configurar todos los componentes
    setupBackground();
    setupKnobs();
    setupMeters();
    // setupSidechainControls();
    setupPresetArea();
    setupUtilityButtons();
    setupParameterButtons();
    
    // Agregar display principal
    
    // Agregar visualizador de curvas de distorsión
    // addAndMakeVisible(distortionCurveDisplay) - No necesario para reverb;
    
    // Agregar analizador de espectro (inicialmente invisible)
    // addAndMakeVisible(spectrumAnalyzer) - Temporalmente deshabilitado;
    // spectrumAnalyzer.setVisible(false);
    
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
        titleText = "v0.9.1";  // Solo versión para Logic Pro
    } else {
        titleText = "JCBReverb v0.9.1";  // Nombre completo para otros DAWs
    }

#if defined(JCB_DEBUG_MUTE_OUTPUT)
    titleText += " [MUTE]";
#elif defined(JCB_DEBUG_PASSTHROUGH)
    titleText += " [PT]";
#endif
    
    titleLink.setButtonText(titleText);
    
    // NO agregar tooltip individual - solo usar la ventana general de tooltips
    // El tooltip se actualiza dinámicamente en updateTooltips() usando getTooltipText("title")
    titleLink.setTooltip("");
    
    // Configurar el click para mostrar créditos
    titleLink.onClick = [this]() {
        showCredits();
    };
    
    addAndMakeVisible(titleLink);
    
    
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
    
    // DISTORTION: Transfer display no necesita inicialización con parámetros
    // Se usará solo para visualización de salida, no función de transferencia

    // Solo se usará para visualización de salida, sin controles interactivos
    
    
    // Solo se mantiene para visualización básica si es necesario en el futuro
    // transferFunctionListener eliminado - no necesario para reverb
    
    
    // Listeners para parámetros de reverb se añadirán según sea necesario
    
    // Listeners de reverb se implementarán cuando se añadan los controles correctos
    
    // Crear y registrar parameter listener para cambios en la banda seleccionada
    
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
    
    // Configurar AUTO RELEASE button
    
    // Configurar estados iniciales
    
    updateButtonStates();
    updateFilterButtonText();  // Establecer texto inicial de botones de filtro
    
    // COMENTADO: Llamadas a métodos update de controles de distorsión
    /*
    updateSidechainComponentStates();
    updateDistortionComponentStates();
    updateBitCrusherComponentStates();
    updateDownsampleComponentStates();
    updateToneLpfComponentStates();
    updateTiltComponentStates();
    */
    
    // Establecer estado inicial de SOLO SIDECHAIN en transfer display
    
    // COMENTADO: Display mode de distorsión no aplica a reverb
    /*
    if (processor.displayModeIsFFT)
    {
        // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado
        utilityButtons.runGraphicsButton.setButtonText("FFT");
        utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId, 
                                                  juce::Colours::transparentBlack);
        utilityButtons.zoomButton.setAlpha(1.0f);
        utilityButtons.zoomButton.setEnabled(true);
    }
    else
    {
        // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado
        utilityButtons.runGraphicsButton.setButtonText("curves");
        utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId, 
                                                  DarkTheme::accent.withAlpha(0.3f));
        utilityButtons.zoomButton.setAlpha(0.4f);
        utilityButtons.zoomButton.setEnabled(false);
    }
    */
    
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
    updateButtonStates();
    
    
    // Inicializar texto del botón AR basado en el estado actual del parámetro
    
    // CRASH FIX: Configurar las funciones reales de los medidores DESPUÉS de toda la inicialización
    // Esto evita accesos prematuros a valores atómicos del processor durante la construcción
    inputMeterL.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsInputValue(0) : -100.0f; });
    inputMeterR.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsInputValue(1) : -100.0f; });
    outputMeterL.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsOutputValue(0) : -100.0f; });
    outputMeterR.setValueFunction([this](){ return processor.isInitialized() ? processor.getRmsOutputValue(1) : -100.0f; });
    
    // Callbacks para visualización se añadirán cuando se implemente el display de reverb

    // Inicializar texto debug overlay
    debugLabel.setText("FS:0  RS:0", juce::dontSendNotification);
    
    
    // CRASH FIX: Iniciar timer AL FINAL para evitar acceso prematuro a valores atómicos
    // El timer debe iniciarse después de que todo esté completamente inicializado
    startTimerHz(TIMER_HZ);
}

//==============================================================================
// IMPLEMENTACIÓN DE BANDSLIDER LOOKANDFEEL
//==============================================================================

void JCBReverbAudioProcessorEditor::BandSliderLookAndFeel::drawLinearSlider(
    juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const juce::Slider::SliderStyle style,
    juce::Slider& slider)
{
    if (style == juce::Slider::LinearHorizontal)
    {
        // Dibujar el track de fondo (línea horizontal)
        const float trackHeight = 2.0f;
        const float trackY = y + height * 0.5f - trackHeight * 0.5f;
        
        g.setColour(juce::Colours::white.withAlpha(0.12f));
        g.fillRoundedRectangle(x, trackY, width, trackHeight, trackHeight * 0.5f);
        
        // Dibujar el thumb con gradiente basado en el valor actual
        const float thumbDiameter = juce::jmin(width, height) * 0.7f;
        const float thumbX = sliderPos - thumbDiameter * 0.5f;
        const float thumbY = y + height * 0.5f - thumbDiameter * 0.5f;
        
        // Obtener el valor actual del slider (0=Low, 1=Mid, 2=High)
        float bandValue = static_cast<float>(slider.getValue());
        
        // Calcular colores para el gradiente del thumb
        juce::Colour thumbColour = getInterpolatedBandColour(bandValue);
        
        // Dibujar sombra del thumb
        g.setColour(juce::Colours::black.withAlpha(0.3f));
        g.fillEllipse(thumbX + 1.0f, thumbY + 1.0f, thumbDiameter, thumbDiameter);
        
        // Dibujar el thumb con gradiente
        if (bandValue <= 1.0f)
        {
            // Gradiente entre Low (púrpura) y Mid (mezcla)
            float t = bandValue;  // 0 a 1
            juce::ColourGradient gradient(
                lowBandColour,
                thumbX, thumbY + thumbDiameter * 0.5f,
                lowBandColour.interpolatedWith(highBandColour, 0.5f),
                thumbX + thumbDiameter, thumbY + thumbDiameter * 0.5f,
                false
            );
            gradient.addColour(0.5, lowBandColour.interpolatedWith(highBandColour, t * 0.5f));
            g.setGradientFill(gradient);
        }
        else
        {
            // Gradiente entre Mid (mezcla) y High (azul)
            float t = bandValue - 1.0f;  // 0 a 1
            juce::ColourGradient gradient(
                lowBandColour.interpolatedWith(highBandColour, 0.5f),
                thumbX, thumbY + thumbDiameter * 0.5f,
                highBandColour,
                thumbX + thumbDiameter, thumbY + thumbDiameter * 0.5f,
                false
            );
            gradient.addColour(0.5, lowBandColour.interpolatedWith(highBandColour, 0.5f + t * 0.5f));
            g.setGradientFill(gradient);
        }
        
        g.fillEllipse(thumbX, thumbY, thumbDiameter, thumbDiameter);
        
        // Añadir un borde sutil al thumb
        g.setColour(thumbColour.brighter(0.3f).withAlpha(0.8f));
        g.drawEllipse(thumbX, thumbY, thumbDiameter, thumbDiameter, 1.0f);
        
        // Añadir punto central brillante
        const float centerDotSize = thumbDiameter * 0.2f;
        g.setColour(juce::Colours::white.withAlpha(0.9f));
        g.fillEllipse(
            thumbX + thumbDiameter * 0.5f - centerDotSize * 0.5f,
            thumbY + thumbDiameter * 0.5f - centerDotSize * 0.5f,
            centerDotSize,
            centerDotSize
        );
    }
    else
    {
        // Delegar a la implementación por defecto para otros estilos
        juce::LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, 
                                              sliderPos, minSliderPos, maxSliderPos, 
                                              style, slider);
    }
}

juce::Colour JCBReverbAudioProcessorEditor::BandSliderLookAndFeel::getInterpolatedBandColour(float bandValue) const
{
    // bandValue: 0=Low, 1=Mid, 2=High
    if (bandValue <= 1.0f)
    {
        // Interpolar entre Low (púrpura) y Mid (mezcla púrpura-azul)
        return lowBandColour.interpolatedWith(
            lowBandColour.interpolatedWith(highBandColour, 0.5f),
            bandValue
        );
    }
    else
    {
        // Interpolar entre Mid (mezcla) y High (azul)
        float t = bandValue - 1.0f;
        return lowBandColour.interpolatedWith(highBandColour, 0.5f)
            .interpolatedWith(highBandColour, t);
    }
}

//==============================================================================
// IMPLEMENTACIÓN DE FILTERSBUTTONLOOKANDFEEL
//==============================================================================

void JCBReverbAudioProcessorEditor::FiltersButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    
    // Si el botón está activado (toggle ON), dibujar gradiente basado en banda seleccionada
    if (auto* toggleButton = dynamic_cast<juce::TextButton*>(&button))
    {
        if (toggleButton->getToggleState())
        {
            // Usar siempre el color de banda Mid (valor fijo 1.0f)
            float bandValue = 1.0f;  // Siempre Mid - color fijo independiente de la selección actual
            
            // Crear gradiente basado en la banda Mid
            juce::ColourGradient gradient;
            
            if (bandValue <= 1.0f)
            {
                // Gradiente entre Low (púrpura) y Mid (mezcla)
                float t = bandValue;  // 0 a 1
                gradient = juce::ColourGradient(
                    lowBandColour.withAlpha(0.20f),  // Restaurar transparencia original
                    bounds.getX(), bounds.getCentreY(),
                    lowBandColour.interpolatedWith(highBandColour, 0.5f).withAlpha(0.15f),  // Restaurar transparencia original
                    bounds.getRight(), bounds.getCentreY(),
                    false
                );
                // Añadir punto intermedio para transición más suave
                gradient.addColour(0.5, lowBandColour.interpolatedWith(highBandColour, t * 0.5f).withAlpha(0.18f));
            }
            else
            {
                // Gradiente entre Mid (mezcla) y High (azul)
                float t = bandValue - 1.0f;  // 0 a 1
                gradient = juce::ColourGradient(
                    lowBandColour.interpolatedWith(highBandColour, 0.5f).withAlpha(0.15f),  // Restaurar transparencia original
                    bounds.getX(), bounds.getCentreY(),
                    highBandColour.withAlpha(0.20f),  // Restaurar transparencia original
                    bounds.getRight(), bounds.getCentreY(),
                    false
                );
                // Añadir punto intermedio para transición más suave
                gradient.addColour(0.5, lowBandColour.interpolatedWith(highBandColour, 0.5f + t * 0.5f).withAlpha(0.18f));
            }
            
            // Dibujar fondo con gradiente
            g.setGradientFill(gradient);
            g.fillRoundedRectangle(bounds, 3.0f);
            
            // Añadir un borde sutil con el color interpolado
            juce::Colour borderColour = getInterpolatedBandColour(bandValue);
            g.setColour(borderColour.withAlpha(0.3f));
            g.drawRoundedRectangle(bounds.reduced(0.5f), 3.0f, 1.0f);
        }
        else
        {
            // Botón desactivado: fondo transparente (comportamiento por defecto)
            g.setColour(backgroundColour);
            g.fillRoundedRectangle(bounds, 3.0f);
        }
    }
    else
    {
        // Fallback para otros tipos de botones
        g.setColour(backgroundColour);
        g.fillRoundedRectangle(bounds, 3.0f);
    }
}

juce::Colour JCBReverbAudioProcessorEditor::FiltersButtonLookAndFeel::getInterpolatedBandColour(float bandValue) const
{
    // bandValue: 0=Low, 1=Mid, 2=High
    // Misma lógica que BandSliderLookAndFeel para consistencia
    if (bandValue <= 1.0f)
    {
        // Interpolar entre Low (púrpura) y Mid (mezcla púrpura-azul)
        return lowBandColour.interpolatedWith(
            lowBandColour.interpolatedWith(highBandColour, 0.5f),
            bandValue
        );
    }
    else
    {
        // Interpolar entre Mid (mezcla) y High (azul)
        float t = bandValue - 1.0f;
        return lowBandColour.interpolatedWith(highBandColour, 0.5f)
            .interpolatedWith(highBandColour, t);
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

//==============================================================================
// IMPLEMENTACIÓN DE TRANSPARENTBUTTONLOOKANDFEEL
//==============================================================================

void JCBReverbAudioProcessorEditor::TransparentButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat();
    
    // Si el botón está activado (toggle ON), solo dibujar borde sutil sin fondo
    if (auto* toggleButton = dynamic_cast<juce::TextButton*>(&button))
    {
        // Para tiltPosButton, siempre dibujar el borde (tanto PRE como POST son estados válidos)
        bool shouldDrawBorder = toggleButton->getToggleState() || 
                               button.getComponentID() == "tiltpos";
        
        if (shouldDrawBorder)
        {
            // NO dibujar fondo - completamente transparente
            
            // Solo añadir un borde muy sutil
            juce::Colour borderColour = lowBandColour.interpolatedWith(highBandColour, 0.5f);
            g.setColour(borderColour.withAlpha(0.15f));  // Borde muy sutil
            g.drawRoundedRectangle(bounds.reduced(0.5f), 3.0f, 1.0f);
        }
        else
        {
            // Botón desactivado: fondo transparente (comportamiento por defecto)
            g.setColour(backgroundColour);
            g.fillRoundedRectangle(bounds, 3.0f);
        }
    }
}

void JCBReverbAudioProcessorEditor::TransparentButtonLookAndFeel::drawButtonText(
    juce::Graphics& g, 
    juce::TextButton& button,
    bool /*shouldDrawButtonAsHighlighted*/,
    bool /*shouldDrawButtonAsDown*/)
{
    auto font = getTextButtonFont(button, button.getHeight());
    g.setFont(font);
    
    // Todos los botones usan findColour normal
    if (button.getToggleState())
        g.setColour(button.findColour(juce::TextButton::textColourOnId));
    else
        g.setColour(button.findColour(juce::TextButton::textColourOffId));
    
    const int yIndent = juce::jmin(4, button.proportionOfHeight(0.3f));
    const int cornerSize = juce::jmin(button.getHeight(), button.getWidth()) / 2;
    const int leftIndent = cornerSize / 2 + 1;
    const int rightIndent = leftIndent;
    const int textWidth = button.getWidth() - leftIndent - rightIndent;
    
    g.drawFittedText(button.getButtonText(),
                    leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                    juce::Justification::centred, 2);
}

juce::Colour JCBReverbAudioProcessorEditor::TransparentButtonLookAndFeel::getInterpolatedBandColour(float bandValue) const
{
    // Mismo código que FiltersButtonLookAndFeel para consistencia
    if (bandValue <= 1.0f)
    {
        return lowBandColour.interpolatedWith(
            lowBandColour.interpolatedWith(highBandColour, 0.5f),
            bandValue
        );
    }
    else
    {
        float t = bandValue - 1.0f;
        return lowBandColour.interpolatedWith(highBandColour, 0.5f)
            .interpolatedWith(highBandColour, t);
    }
}

JCBReverbAudioProcessorEditor::~JCBReverbAudioProcessorEditor()
{
    // CRÍTICO: Detener timer PRIMERO para prevenir crashes durante destrucción
    stopTimer();
    
    // Eliminar parameter listeners
    processor.apvts.removeParameterListener("g_BITS", this);
    
    
    // DISTORTION: Transfer function listener sin parameter listeners activos
    // if (transferFunctionListener) - sin listeners que remover
    
    
    // Remover listeners de reverb cuando se implementen
    
    // Remoción de listeners de reverb cuando se implementen
    
    // IMPORTANTE: Limpiar todos los LookAndFeels de componentes hijos antes de destrucción
    // Esto resuelve la aserción juce_LookAndFeel.cpp:82 detectada por pluginval
    
    // COMENTADO: Limpiar look and feel de controles de distorsión
    /* 
    leftTopKnobs.ceilingSlider.setLookAndFeel(nullptr);
    leftBottomKnobs.drywetSlider.setLookAndFeel(nullptr);
    leftBottomKnobs.toneFreqSlider.setLookAndFeel(nullptr);
    leftBottomKnobs.toneQSlider.setLookAndFeel(nullptr);
    rightTopControls.bitsSlider.setLookAndFeel(nullptr);
    rightBottomKnobs.driveSlider.setLookAndFeel(nullptr);
    rightBottomKnobs.modeSlider.setLookAndFeel(nullptr);
    rightTopControls.tiltSlider.setLookAndFeel(nullptr);
    rightTopControls.downsampleSlider.setLookAndFeel(nullptr);
    rightBottomKnobs.dcSlider.setLookAndFeel(nullptr);
    sidechainControls.xLowSlider.setLookAndFeel(nullptr);
    sidechainControls.xHighSlider.setLookAndFeel(nullptr);
    sidechainControls.bandSlider.setLookAndFeel(nullptr);
    leftBottomKnobs.toneLpfButton.setLookAndFeel(nullptr);
    leftBottomKnobs.tonePosButton.setLookAndFeel(nullptr);
    rightBottomKnobs.distOnButton.setLookAndFeel(nullptr);
    rightTopControls.tiltOnButton.setLookAndFeel(nullptr);
    rightTopControls.tiltPosButton.setLookAndFeel(nullptr);
    rightTopControls.downsampleButton.setLookAndFeel(nullptr);
    sidechainControls.bandSoloButton.setLookAndFeel(nullptr);
    sidechainControls.scButton.setLookAndFeel(nullptr);
    rightTopControls.safeLimitButton.setLookAndFeel(nullptr);
    rightBottomKnobs.bitButton.setLookAndFeel(nullptr);
    */
    
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
    
    // Si el usuario redimensiona manualmente (no es uno de los tamaños predefinidos),
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
    
    // Meters de sidechain - ahora directamente adyacentes a los meters de entrada (sin gap)
    // scMeterL.setBounds(getScaledBounds(24, 42, 12, 117));
    // scMeterR.setBounds(getScaledBounds(34, 42, 12, 117));
    
    // COMENTADO: Slider de trim incorrecto
    // trimSlider.setBounds(getScaledBounds(2, 40, 22, 130));
    
    // Sliders de trim de sidechain superpuestos a los medidores de sidechain
    // scTrimSlider.setBounds(getScaledBounds(24, 40, 22, 130));  // Altura expandida para TextBox integrado
    
    // Medidor GR (centro-derecha) - más delgado y alto, posición final ajustada
    
    // Medidores de salida (lado derecho)
    outputMeterL.setBounds(getScaledBounds(677, 42, 12, 117));
    outputMeterR.setBounds(getScaledBounds(687, 42, 12, 117));

    // Posicionar debug label en esquina inferior derecha
    const int dbgW = 220;
    const int dbgH = 16;
    debugLabel.setBounds(getWidth() - dbgW - 10, getHeight() - dbgH - 6, dbgW, dbgH);
    
    // COMENTADO: Slider de makeup incorrecto
    // makeupSlider.setBounds(getScaledBounds(677, 40, 22, 130));
    
    
    // === TRANSFER FUNCTION DISPLAY (CENTER) ===
    float x = 460.0f * 700.0f / 1247.0f;
    float y = 73.0f * 200.0f / 353.0f + 4.0f;
    float w = 335.0f * 700.0f / 1247.0f;
    float h = 205.0f * 200.0f / 353.0f - 5.0f;
    
    // Posicionar el visualizador de curvas de distorsión en el mismo lugar
    // distortionCurveDisplay.setBounds(getScaledBounds(x, y, w, h));
    
    // Posicionar el analizador de espectro en el mismo lugar
    // spectrumAnalyzer.setBounds(getScaledBounds(x, y, w, h));

    // COMENTADO: Posicionamiento de controles de distorsión
    /*
    leftBottomKnobs.toneLpfButton.setBounds(getScaledBounds(126, 118, 25, 15));
    leftBottomKnobs.tonePosButton.setBounds(getScaledBounds(136, 138, 20, 10));
    leftBottomKnobs.toneFreqSlider.setBounds(getScaledBounds(146, 102, 53, 53));
    leftBottomKnobs.toneQSlider.setBounds(getScaledBounds(193, 102, 53, 53));
    rightTopControls.tiltSlider.setBounds(getScaledBounds(73, 102, 53, 53));
    rightTopControls.tiltOnButton.setBounds(getScaledBounds(53, 118, 25, 15));
    rightTopControls.tiltPosButton.setBounds(getScaledBounds(63, 138, 20, 10));
    rightBottomKnobs.distOnButton.setBounds(getScaledBounds(33, 68, 25, 20));
    rightBottomKnobs.modeSlider.setBounds(getScaledBounds(52, 49, 53, 53));
    rightBottomKnobs.driveSlider.setBounds(getScaledBounds(100, 49, 53, 53));
    rightBottomKnobs.dcSlider.setBounds(getScaledBounds(146, 49, 53, 53));
    leftTopKnobs.ceilingSlider.setBounds(getScaledBounds(193, 49, 53, 53));
    rightTopControls.bitsSlider.setBounds(getScaledBounds(475, 51, 53, 53));
    rightBottomKnobs.bitButton.setBounds(getScaledBounds(525, 73, 57, 15));
    rightTopControls.downsampleSlider.setBounds(getScaledBounds(530, 102, 53, 53));
    rightTopControls.downsampleButton.setBounds(getScaledBounds(580, 118, 57, 15));
    leftBottomKnobs.drywetSlider.setBounds(getScaledBounds(585, 51, 53, 53));
    rightTopControls.safeLimitButton.setBounds(getScaledBounds(678, 30, 20, 10));
    */
    // Movido junto con FILTERS button abajo


    // COMENTADO: Controles de filtro/sidechain de distorsión
    /*
    sidechainControls.xLowSlider.setBounds(getScaledBounds(285, 5, 36, 36));
    sidechainControls.xHighSlider.setBounds(getScaledBounds(388, 5, 36, 36));
    const int bandCenterX = 353;
    auto bandBounds = getScaledBounds(bandCenterX - 35, 24, 70, 10);
    sidechainControls.bandSlider.setBounds(bandBounds);
    */
    
    // COMENTADO: Más posicionamiento de controles de sidechain
    /*
    const int labelY = bandBounds.getBottom() + 1;
    const int labelHeight = 14;
    sidechainControls.bandLowLabel.setBounds(
        bandBounds.getX(), labelY, 30, labelHeight);
    sidechainControls.bandMidLabel.setBounds(
        bandBounds.getX() + bandBounds.getWidth()/2 - 15, labelY, 30, labelHeight);
    sidechainControls.bandHighLabel.setBounds(
        bandBounds.getRight() - 25, labelY, 25, labelHeight);
    const int buttonWidth = 25;
    const int centerX = 353;
    const int spacing = 2;
    sidechainControls.scButton.setBounds(getScaledBounds(centerX - buttonWidth - spacing/2, 8, buttonWidth, 12));
    sidechainControls.bandSoloButton.setBounds(getScaledBounds(centerX + spacing/2, 8, buttonWidth, 12));
    */

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
    
    // Botones TODO movidos abajo a la derecha, centrados en el rectángulo
    // Calcular posición central para el grupo de botones TODO
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
        
        // Forzar repaint del transfer display cuando Logic está parado
        // para que las envolventes y el histograma desaparezcan
        if (isProcessingInactive)
        {
        }
    }
    
    // FFT processing removed - disabled for stability

    // Debug overlay: update counters each frame (lightweight atomics)
    {
        const int fs = processor.getDiagFailsafeCount();
        const int rs = processor.getDiagGenResets();
        debugLabel.setText(juce::String::formatted("FS:%d  RS:%d", fs, rs), juce::dontSendNotification);
    }
}

void JCBReverbAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    // Simplificado - sin manejo automático de cambios de parámetros para undo/redo
    
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
            // BYPASS desactiva SOLO SC y DIAGRAM
            if (centerButtons.diagramButton.getToggleState()) {
                centerButtons.diagramButton.setToggleState(false, juce::dontSendNotification);
                hideDiagram();
            }
        }
        updateButtonStates();

        // Reactivar control de bypass interno de Gen: z_BYPASSS (sin smoothing en Gen)
        if (auto* st = processor.getPluginState())
        {
            for (int i = 0; i < JCBReverb::num_params(); ++i)
            {
                if (juce::String(JCBReverb::getparametername(st, i)) == "z_BYPASSS")
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
    // COMENTADO: Control de filtros y módulos de distorsión - no aplican a reverb
    /*
    else if (button == &sidechainControls.scButton)
    {
        // Actualizar estado visual de sliders HPF/LPF
        updateSidechainComponentStates();
    }
    // DISTORTION: Control de activación del módulo de distorsión
    else if (button == &rightBottomKnobs.distOnButton)
    {
        // Actualizar estado visual de sliders de distorsión (MODE, EVEN, DRIVE, CEIL)
        updateDistortionComponentStates();
    }
    // Control de activación de BIT CRUSHER
    else if (button == &rightBottomKnobs.bitButton)
    {
        // Actualizar estado visual del slider BIT
        updateBitCrusherComponentStates();
    }
    // Control de activación de DOWNSAMPLE
    else if (button == &rightTopControls.downsampleButton)
    {
        // Actualizar estado visual del slider DECI
        updateDownsampleComponentStates();
    }
    // Control de activación de TONE LPF
    else if (button == &leftBottomKnobs.toneLpfButton)
    {
        // Actualizar estado visual del slider TONE
        updateToneLpfComponentStates();
    }
    // Control de activación de TILT
    else if (button == &rightTopControls.tiltOnButton)
    {
        // Actualizar estado visual del slider TILT
        updateTiltComponentStates();
    }
    */
    /* MAXIMIZER: Otros controles sidechain comentados (no existen en DISTORTION)
    else if (button == &sidechainControls.keyButton)
    {
        // Actualizar visibilidad del medidor de sidechain cuando KEY es activado
        updateButtonStates();
        
        // Actualizar estado EXT KEY en transfer display
    }
    else if (button == &sidechainControls.soloScButton)
    {
        if (sidechainControls.soloScButton.getToggleState()) {
            // SOLO SC desactiva BYPASS y DIAGRAM
            parameterButtons.bypassButton.setToggleState(false, juce::sendNotification);
            if (centerButtons.diagramButton.getToggleState()) {
                centerButtons.diagramButton.setToggleState(false, juce::dontSendNotification);
                hideDiagram(); // Cerrar DIAGRAM si está abierto
            }
        }
        
        updateButtonStates();
        
        // Actualizar transfer function display para estado SOLO SC
        bool soloActive = sidechainControls.soloScButton.getToggleState();
    }
    */
    else if (button == &utilityButtons.runGraphicsButton)
    {
        // COMENTADO: toggleDisplayMode no existe para reverb
        // toggleDisplayMode();
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
        
        // Actualizar textos de botones TODO con el nuevo idioma
        updateTodoButtonTexts();
    }
    else if (button == &utilityButtons.hqButton)
    {
        
        // TODO: Implementar oversampling HQ
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
            topButtons.abStateButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff9c27b0));  // Purple
            topButtons.abStateButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
        } else {
            // B = Azul
            topButtons.abStateButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2196f3));  // Blue
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
            topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff9c27b0));  // Destello púrpura
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
        
        // TODO: Implementar modo MIDI learn
    }
    else if (button == &utilityButtons.zoomButton)
    {
        // COMENTADO: DisplayMode eliminado
        // if (currentDisplayMode == DisplayMode::FFT)
        if (false) // Temporal: siempre false hasta implementar modo correcto
        {
            // FFT zoom functionality - toggle zoom range
            // TEMPORAL: Deshabilitado mientras spectrumAnalyzer está comentado
            // bool currentZoom = spectrumAnalyzer.getZoomEnabled();
            bool currentZoom = false;
            bool newZoom = !currentZoom;
            
    // spectrumAnalyzer.setZoomEnabled(newZoom);
            
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
        else
        {
            // Zoom no está disponible en modo CURVES
            // El botón ya está deshabilitado en este modo
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
    // Manejador del botón CODE removido - funcionalidad manejada por botón DIAGRAM
}

//==============================================================================
// PARAMETER LISTENER - Sincronización con automatización del HOST
//==============================================================================

void JCBReverbAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{
    // BITS ahora usa CustomSliderAttachment, no necesita listener manual
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
    
    // Actualizar texto del botón EXT KEY dinámicamente basándose en el estado del parámetro "r_KEY"
    /*
    // if (auto* keyParam = processor.apvts.getRawParameterValue("r_KEY")) {
        bool isExtKeyActive = keyParam->load() > 0.5f;
        if (isExtKeyActive) {
            sidechainControls.keyButton.setButtonText("SC EXT");
        } else {
            sidechainControls.keyButton.setButtonText("SC INT");
        }
        // Nota: El tooltip se actualiza automáticamente via getTooltipText("extkey") en updateAllTooltips()
    }
    */
    
    // NUEVO: Actualizar alpha del REL slider basado en estado de AUTOREL
}


//==============================================================================
// MÉTODOS DE SETUP Y CONFIGURACIÓN
//==============================================================================
void JCBReverbAudioProcessorEditor::setupKnobs()
{
    // TODO: Implementar controles correctos para reverb
    // COMENTADO: Todo el código antiguo de controles de distorsión
    /*
    // Parámetros necesarios:
    // - a_input, b_drywet, c_reflect, d_damp, e_size, f_st, g_freeze (reverb)
    // - h_lowGain, i_peakGain, j_hiGain, n_lowFreq, o_peakFreq, p_hiFreq, q_onoffEQ (EQ)
    // - k_lpf, l_hpf (filtros)
    // - r_onoffCOMP, s_thd, t_ratio, u_atk, v_rel, w_makeup (compresor)
    // - m_output (salida)
    
    // COMENTADO: Todo el código antiguo de controles de distorsión
    /*
    // Establecer undo manager y editor para todos los sliders primero
    
    // === LEFT TOP KNOBS ===
    // CEILING (e_CEILING) - Output ceiling -20dB to 6dB
    leftTopKnobs.ceilingSlider.setComponentID("ceiling");
    leftTopKnobs.ceilingSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftTopKnobs.ceilingSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    leftTopKnobs.ceilingSlider.setLookAndFeel(&sliderLAFBig);
    leftTopKnobs.ceilingSlider.setTextBoxIsEditable(true);
    leftTopKnobs.ceilingSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftTopKnobs.ceilingSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFEB2B2));  // Rosa pálido como distorsión
    leftTopKnobs.ceilingSlider.setDoubleClickReturnValue(true, 0.0);  // Default: 0 dB
    leftTopKnobs.ceilingSlider.setPopupDisplayEnabled(false, false, this);
    leftTopKnobs.ceilingSlider.setNumDecimalPlacesToDisplay(1);
    leftTopKnobs.ceilingSlider.setTextValueSuffix(" dB");
    // Rango: -20 dB a 6 dB (según CLAUDE.md)
    leftTopKnobs.ceilingSlider.setRange(-20.0, 6.0, 0.1);
    // Centrar control visual en 0 dB para mejor resolución
    leftTopKnobs.ceilingSlider.setSkewFactorFromMidPoint(0.0);
    addAndMakeVisible(leftTopKnobs.ceilingSlider);
    if (auto* param = processor.apvts.getParameter("e_CEILING"))
    {
        leftTopKnobs.ceilingAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftTopKnobs.ceilingSlider, &undoManager);
        leftTopKnobs.ceilingAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    // Tooltip actualizado via getTooltipText("ceiling") en updateAllTooltips()
    
    // === LEFT BOTTOM KNOBS ===
    // DRYWET (o_DRYWET) - Mezcla dry/wet 0-100%
    leftBottomKnobs.drywetSlider.setComponentID("drywet");
    leftBottomKnobs.drywetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftBottomKnobs.drywetSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    leftBottomKnobs.drywetSlider.setLookAndFeel(&sliderLAFBig);
    leftBottomKnobs.drywetSlider.setTextBoxIsEditable(true);
    leftBottomKnobs.drywetSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.drywetSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFB1CAF6));  // Azul pálido como output
    leftBottomKnobs.drywetSlider.setDoubleClickReturnValue(true, 1.0);  // Default: 100% (o_DRYWET = 1.0)
    leftBottomKnobs.drywetSlider.setPopupDisplayEnabled(false, false, this);
    leftBottomKnobs.drywetSlider.setRange(0.0, 1.0, 0.01);  // Rango interno 0.0-1.0
    leftBottomKnobs.drywetSlider.textFromValueFunction = [](double value) {
        return juce::String(static_cast<int>(value * 101)) + " %";
    };
    leftBottomKnobs.drywetSlider.valueFromTextFunction = [](const juce::String& text) {
        auto trimmed = text.trim();
        // Eliminar símbolo de porcentaje si existe
        if (trimmed.endsWith("%"))
            trimmed = trimmed.dropLastCharacters(1).trim();
        
        // Convertir a número y normalizar de 0-100 a 0-1
        auto percentage = trimmed.getDoubleValue();
        return juce::jlimit(0.0, 1.0, percentage / 100.0);
    };
    addAndMakeVisible(leftBottomKnobs.drywetSlider);
    if (auto* param = processor.apvts.getParameter("a_DRYWET"))
    {
        leftBottomKnobs.drywetAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftBottomKnobs.drywetSlider, &undoManager);
        leftBottomKnobs.drywetAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    leftBottomKnobs.drywetSlider.setTooltip(JUCE_UTF8("D/W: mezcla entre señal seca y procesada.\n0% = solo señal original, 100% = solo señal comprimida.\nValor por defecto: 100% (wet)"));
    
    // TONE FREQ slider - movido desde RightTopControls
    leftBottomKnobs.toneFreqSlider.setComponentID("r_TONEFREQ");
    leftBottomKnobs.toneFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftBottomKnobs.toneFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
    leftBottomKnobs.toneFreqSlider.setLookAndFeel(&sliderLAFBig);
    leftBottomKnobs.toneFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF6EB8F6));  // Azul claro TONE
    leftBottomKnobs.toneFreqSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF6EB8F6));
    leftBottomKnobs.toneFreqSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.toneFreqSlider.setTextBoxIsEditable(true);
    leftBottomKnobs.toneFreqSlider.setEnabled(true);
    leftBottomKnobs.toneFreqSlider.setDoubleClickReturnValue(true, 20000.0f);
    leftBottomKnobs.toneFreqSlider.setPopupDisplayEnabled(false, false, this);
    leftBottomKnobs.toneFreqSlider.setNumDecimalPlacesToDisplay(0);
    leftBottomKnobs.toneFreqSlider.textFromValueFunction = [](double value) {
        if (value < 1000.0)
            return juce::String(static_cast<int>(value));
        else
            return juce::String(value / 1000.0, 1) + "k";
    };
    leftBottomKnobs.toneFreqSlider.setTextValueSuffix(" Hz");
    leftBottomKnobs.toneFreqSlider.setRange(20.0, 20000.0, 1.0);
    leftBottomKnobs.toneFreqSlider.setSkewFactorFromMidPoint(3000.0);
    addAndMakeVisible(leftBottomKnobs.toneFreqSlider);
    if (auto* param = processor.apvts.getParameter("r_TONEFREQ"))
    {
        leftBottomKnobs.toneFreqAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftBottomKnobs.toneFreqSlider, &undoManager);
        leftBottomKnobs.toneFreqAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // TONE Q slider - nuevo parámetro t_TONEQ
    leftBottomKnobs.toneQSlider.setComponentID("t_TONEQ");
    leftBottomKnobs.toneQSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    leftBottomKnobs.toneQSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 16);
    leftBottomKnobs.toneQSlider.setLookAndFeel(&sliderLAFBig);
    leftBottomKnobs.toneQSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF6EB8F6));  // Azul claro TONE
    leftBottomKnobs.toneQSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFF6EB8F6));
    leftBottomKnobs.toneQSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.toneQSlider.setTextBoxIsEditable(true);
    leftBottomKnobs.toneQSlider.setEnabled(true);
    leftBottomKnobs.toneQSlider.setDoubleClickReturnValue(true, 0.7071067811865476f);
    leftBottomKnobs.toneQSlider.setPopupDisplayEnabled(false, false, this);
    leftBottomKnobs.toneQSlider.setNumDecimalPlacesToDisplay(0);
    leftBottomKnobs.toneQSlider.textFromValueFunction = [](double value) {
        // Mapear Q a porcentaje 0-100%
        float percent = (value - 0.7071067811865476f) / (16.0f - 0.7071067811865476f) * 100.0f;
        return juce::String(static_cast<int>(percent)) + "%";
    };
    leftBottomKnobs.toneQSlider.setRange(0.7071067811865476, 16.0, 0.01);
    addAndMakeVisible(leftBottomKnobs.toneQSlider);
    if (auto* param = processor.apvts.getParameter("t_TONEQ"))
    {
        leftBottomKnobs.toneQAttachment = std::make_unique<CustomSliderAttachment>(
            *param, leftBottomKnobs.toneQSlider, &undoManager);
        leftBottomKnobs.toneQAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // Botón TONE - movido desde RightTopControls
    leftBottomKnobs.toneLpfButton.setComponentID("tonelpf");
    leftBottomKnobs.toneLpfButton.setLookAndFeel(transparentButtonLAF.get());
    leftBottomKnobs.toneLpfButton.setButtonText("TONE");
    leftBottomKnobs.toneLpfButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.toneLpfButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.toneLpfButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xFF6EB8F6).withAlpha(0.3f));
    leftBottomKnobs.toneLpfButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFF6EB8F6).withAlpha(0.4f));
    leftBottomKnobs.toneLpfButton.setClickingTogglesState(true);
    addAndMakeVisible(leftBottomKnobs.toneLpfButton);
    if (auto* param = processor.apvts.getParameter("q_TONEON"))
    {
        leftBottomKnobs.toneLpfAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, leftBottomKnobs.toneLpfButton, &undoManager);
        leftBottomKnobs.toneLpfAttachment->onStateChange = [](bool) {};
        leftBottomKnobs.toneLpfAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        leftBottomKnobs.toneLpfButton.setButtonText("TONE");
    }
    
    // Botón TONE POS - nuevo parámetro u_TONEPOS (PRE/POST)
    leftBottomKnobs.tonePosButton.setComponentID("tonepos");
    leftBottomKnobs.tonePosButton.setLookAndFeel(transparentButtonLAF.get());
    leftBottomKnobs.tonePosButton.setButtonText("POST");
    leftBottomKnobs.tonePosButton.setClickingTogglesState(true);
    leftBottomKnobs.tonePosButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.tonePosButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    leftBottomKnobs.tonePosButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xFF6EB8F6));  // Azul claro TONE
    leftBottomKnobs.tonePosButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFF6EB8F6));
    leftBottomKnobs.tonePosButton.addListener(this);
    addAndMakeVisible(leftBottomKnobs.tonePosButton);
    if (auto* param = processor.apvts.getParameter("u_TONEPOS"))
    {
        leftBottomKnobs.tonePosAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, leftBottomKnobs.tonePosButton, &undoManager);
        leftBottomKnobs.tonePosAttachment->onStateChange = [this](bool isPost) {
            leftBottomKnobs.tonePosButton.setButtonText(isPost ? "POST" : "PRE");
        };
        leftBottomKnobs.tonePosAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        // Sincronizar texto inicial con el estado actual del parámetro
        bool initialState = param->getValue() >= 0.5f;
        leftBottomKnobs.tonePosButton.setButtonText(initialState ? "POST" : "PRE");
    }
    
    // === RIGHT TOP CONTROLS ===
    // BITS - bit crusher resolution control
    rightTopControls.bitsSlider.setComponentID("bit");
    rightTopControls.bitsSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rightTopControls.bitsSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    rightTopControls.bitsSlider.setLookAndFeel(&sliderLAFBig);
    rightTopControls.bitsSlider.setTextBoxIsEditable(true);
    rightTopControls.bitsSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    rightTopControls.bitsSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFB2FFB3));  // Verde pálido para bits
    rightTopControls.bitsSlider.setRange(3.0, 16.0, 1.0);  // Rango igual al parámetro: 3-16 bits
    rightTopControls.bitsSlider.setDoubleClickReturnValue(true, 16.0);  // Valor por defecto 16 bits
    rightTopControls.bitsSlider.setPopupDisplayEnabled(false, false, this);
    rightTopControls.bitsSlider.setNumDecimalPlacesToDisplay(0);  // Solo enteros
    // IMPORTANTE: Configurar formatter ANTES de setValue para evitar bug de inicialización
    rightTopControls.bitsSlider.textFromValueFunction = [](double value) {
        return juce::String(static_cast<int>(value)) + " bit";
    };
    rightTopControls.bitsSlider.setValue(16.0);  // Default 16 bits
    addAndMakeVisible(rightTopControls.bitsSlider);
    
    // Crear CustomSliderAttachment para integrar en sistema UNDO/REDO
    if (auto* param = processor.apvts.getParameter("g_BITS"))
    {
        rightTopControls.bitsAttachment = std::make_unique<CustomSliderAttachment>(
            *param, rightTopControls.bitsSlider, &undoManager);
        rightTopControls.bitsAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // === PERILLAS INFERIORES DERECHAS ===
    // ATK - copiado exactamente de ExpansorGate
    rightBottomKnobs.driveSlider.setComponentID("drive");
    rightBottomKnobs.driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rightBottomKnobs.driveSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    rightBottomKnobs.driveSlider.setLookAndFeel(&sliderLAFBig);
    rightBottomKnobs.driveSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    rightBottomKnobs.driveSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFEB2B2));  // Rosa pálido como distorsión
    rightBottomKnobs.driveSlider.setDoubleClickReturnValue(true, 1.0);  // Valor por defecto 1.0 (sin drive)
    rightBottomKnobs.driveSlider.setPopupDisplayEnabled(false, false, this);
    rightBottomKnobs.driveSlider.setTextBoxIsEditable(true);
    // DISTORTION: Formato numérico simple para b_DRIVE (amplificación 1-50)
    rightBottomKnobs.driveSlider.setNumDecimalPlacesToDisplay(1);
    // Configurar rango para DRIVE: 1-50x
    rightBottomKnobs.driveSlider.setRange(1.0, 50.0, 0.1);
    rightBottomKnobs.driveSlider.setSkewFactorFromMidPoint(5.0);  // Concentrar rango útil en valores bajos
    addAndMakeVisible(rightBottomKnobs.driveSlider);
    if (auto* param = processor.apvts.getParameter("b_DRIVE"))
    {
        rightBottomKnobs.driveAttachment = std::make_unique<CustomSliderAttachment>(
            *param, rightBottomKnobs.driveSlider, &undoManager);
        rightBottomKnobs.driveAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    // Tooltip actualizado via getTooltipText("attack") en updateAllTooltips()
    
    // REL - modificado con rango mínimo de 1ms y formato de decimales progresivo
    rightBottomKnobs.modeSlider.setComponentID("mode");
    rightBottomKnobs.modeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rightBottomKnobs.modeSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 100, 16);  // Ancho aumentado para nombre
    rightBottomKnobs.modeSlider.setLookAndFeel(&sliderLAFBig);
    rightBottomKnobs.modeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    rightBottomKnobs.modeSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);  // Default para color dinámico
    rightBottomKnobs.modeSlider.setRange(0.0, 7.0, 0.1);  // MODE: 0-7
    rightBottomKnobs.modeSlider.setSkewFactorFromMidPoint(3.5);  // Linear para modos discretos
    rightBottomKnobs.modeSlider.setDoubleClickReturnValue(true, 0.0);  // Valor por defecto modo 0
    rightBottomKnobs.modeSlider.setPopupDisplayEnabled(false, false, this);
    rightBottomKnobs.modeSlider.setTextBoxIsEditable(true);
    // DISTORTION: Formato con número y nombre del algoritmo
    rightBottomKnobs.modeSlider.textFromValueFunction = [](double value) {
        int mode = static_cast<int>(value);
        juce::String modeName;
        
        switch (mode)
        {
            case 0: modeName = "SOFT CLIP"; break;
            case 1: modeName = "SIGMOID"; break;
            case 2: modeName = "RECT FW"; break;      // Full Wave abreviado
            case 3: modeName = "FUZZ EXPO"; break;
            case 4: modeName = "HYPER TANG"; break;
            case 5: modeName = "RECT HW"; break;      // Half Wave abreviado
            case 6: modeName = "ARC TANG"; break;
            case 7: modeName = "HARD CLIP"; break;
            default: modeName = ""; break;
        }
        
        return juce::String(mode + 1) + " - " + modeName;
    };
    rightBottomKnobs.modeSlider.valueFromTextFunction = [](const juce::String& text) {
        auto trimmed = text.trim();
        
        // Si contiene guión, extraer solo el número
        if (trimmed.contains("-"))
        {
            auto parts = juce::StringArray::fromTokens(trimmed, "-", "");
            if (parts.size() > 0)
            {
                int modeNumber = parts[0].trim().getIntValue();
                return juce::jlimit(0.0, 7.0, static_cast<double>(modeNumber - 1));
            }
        }
        
        // Si es solo un número
        int modeNumber = trimmed.getIntValue();
        return juce::jlimit(0.0, 7.0, static_cast<double>(modeNumber - 1));
    };
    rightBottomKnobs.modeSlider.setNumDecimalPlacesToDisplay(0);
    rightBottomKnobs.modeSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFEB2B2));  // Color rosa pálido fijo
    addAndMakeVisible(rightBottomKnobs.modeSlider);
    if (auto* param = processor.apvts.getParameter("d_MODE"))
    {
        rightBottomKnobs.modeAttachment = std::make_unique<CustomSliderAttachment>(
            *param, rightBottomKnobs.modeSlider, &undoManager);
        rightBottomKnobs.modeAttachment->onParameterChange = [this]() { 
            handleParameterChange();
        };
    }
    
    // DIST ON button - botón para activar/desactivar distorsión
    rightBottomKnobs.distOnButton.setComponentID("diston");
    rightBottomKnobs.distOnButton.setLookAndFeel(transparentButtonLAF.get());  // Usar fondo transparente con borde sutil
    rightBottomKnobs.distOnButton.setButtonText("ON");
    rightBottomKnobs.distOnButton.setClickingTogglesState(true);
    rightBottomKnobs.distOnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightBottomKnobs.distOnButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Transparente con borde sutil
    rightBottomKnobs.distOnButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    rightBottomKnobs.distOnButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFFFEB2B2));  // Rosa pálido como los sliders de distorsión
    rightBottomKnobs.distOnButton.addListener(this);
    addAndMakeVisible(rightBottomKnobs.distOnButton);
    if (auto* param = processor.apvts.getParameter("p_DISTON"))
    {
        rightBottomKnobs.distOnButtonAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, rightBottomKnobs.distOnButton, &undoManager);
        
        // Configurar callback para cambiar texto cuando el estado cambie (por cualquier razón)
        rightBottomKnobs.distOnButtonAttachment->onStateChange = [this](bool isOn) {
            rightBottomKnobs.distOnButton.setButtonText(isOn ? "ON" : "OFF");
        };
        
        // Callback para cuando el usuario hace click (para preset modification indicator)
        rightBottomKnobs.distOnButtonAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        
        // Sincronizar texto inicial con el estado actual del parámetro
        bool initialState = param->getValue() >= 0.5f;
        rightBottomKnobs.distOnButton.setButtonText(initialState ? "ON" : "OFF");
    }
    
    // DITHER button - área izquierda
    rightBottomKnobs.bitButton.setComponentID("bitcrusher");
    rightBottomKnobs.bitButton.setLookAndFeel(reversedGradientButtonLAF.get());  // Usar gradiente invertido
    rightBottomKnobs.bitButton.setButtonText("BIT CRUSHER");
    rightBottomKnobs.bitButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightBottomKnobs.bitButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Transparente para gradiente
    rightBottomKnobs.bitButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xFFB2FFB3));  // Verde pálido como el slider
    rightBottomKnobs.bitButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFFB2FFB3));  // Verde pálido como el slider
    rightBottomKnobs.bitButton.setClickingTogglesState(true);
    addAndMakeVisible(rightBottomKnobs.bitButton);
    if (auto* param = processor.apvts.getParameter("h_BITSON"))
    {
        rightBottomKnobs.bitAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, rightBottomKnobs.bitButton, &undoManager);
        rightBottomKnobs.bitAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
    }
    // Tooltip actualizado via getTooltipText("dither") en updateAllTooltips()
    
    // DET knob - área derecha superior  
rightTopControls.tiltSlider.setComponentID("tilt");
    rightTopControls.tiltSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rightTopControls.tiltSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    rightTopControls.tiltSlider.setLookAndFeel(&sliderLAFBig);
    rightTopControls.tiltSlider.setTextBoxIsEditable(true);
    rightTopControls.tiltSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    rightTopControls.tiltSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFA6DAD5));  // Verde agua pálido como tilt
    rightTopControls.tiltSlider.setRange(-6.0, 6.0, 0.1);
    rightTopControls.tiltSlider.setValue(0.0);
    rightTopControls.tiltSlider.setDoubleClickReturnValue(true, 0.0);  // TILT neutro en 0 dB
    rightTopControls.tiltSlider.setPopupDisplayEnabled(false, false, this);
    rightTopControls.tiltSlider.setNumDecimalPlacesToDisplay(1);
    // Custom text formatting para mostrar dB
    rightTopControls.tiltSlider.textFromValueFunction = [](double value) {
        return juce::String(value, 1) + " dB";
    };
    addAndMakeVisible(rightTopControls.tiltSlider);
    if (auto* param = processor.apvts.getParameter("i_TILT"))
    {
        rightTopControls.tiltAttachment = std::make_unique<CustomSliderAttachment>(
            *param, rightTopControls.tiltSlider, &undoManager);
        rightTopControls.tiltAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // TILT ON button - botón activador de TILT
    rightTopControls.tiltOnButton.setComponentID("tilton");
    rightTopControls.tiltOnButton.setLookAndFeel(transparentButtonLAF.get());
    rightTopControls.tiltOnButton.setButtonText("TILT");
    rightTopControls.tiltOnButton.setClickingTogglesState(true);
    rightTopControls.tiltOnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightTopControls.tiltOnButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    rightTopControls.tiltOnButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xFFA6DAD5).withAlpha(0.3f));  // Verde agua pálido con alpha
    rightTopControls.tiltOnButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFFA6DAD5).withAlpha(0.4f));  // Verde agua pálido con alpha
    rightTopControls.tiltOnButton.addListener(this);
    addAndMakeVisible(rightTopControls.tiltOnButton);
    if (auto* param = processor.apvts.getParameter("s_TILTON"))
    {
        rightTopControls.tiltOnAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, rightTopControls.tiltOnButton, &undoManager);
        rightTopControls.tiltOnAttachment->onStateChange = [](bool) {};
        rightTopControls.tiltOnAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        rightTopControls.tiltOnButton.setButtonText("TILT");
    }
    
    // TILT POS button - botón para posición PRE/POST
    rightTopControls.tiltPosButton.setComponentID("tiltpos");
    rightTopControls.tiltPosButton.setLookAndFeel(transparentButtonLAF.get());  // Usar fondo transparente con borde sutil
    rightTopControls.tiltPosButton.setButtonText("PRE");
    rightTopControls.tiltPosButton.setClickingTogglesState(true);
    rightTopControls.tiltPosButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightTopControls.tiltPosButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Transparente con borde sutil
    rightTopControls.tiltPosButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xFFA6DAD5));  // Verde agua pálido como tiltSlider
    rightTopControls.tiltPosButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFFA6DAD5));  // Verde agua pálido como tiltSlider
    rightTopControls.tiltPosButton.addListener(this);
    addAndMakeVisible(rightTopControls.tiltPosButton);
    if (auto* param = processor.apvts.getParameter("p_TILTPOS"))
    {
        rightTopControls.tiltPosButtonAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, rightTopControls.tiltPosButton, &undoManager);
        
        // Configurar callback para cambiar texto cuando el estado cambie (por cualquier razón)
        rightTopControls.tiltPosButtonAttachment->onStateChange = [this](bool isPost) {
            rightTopControls.tiltPosButton.setButtonText(isPost ? "POST" : "PRE");
        };
        
        // Callback para cuando el usuario hace click (para preset modification indicator)
        rightTopControls.tiltPosButtonAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        
        // Sincronizar texto inicial con el estado actual del parámetro
        bool initialState = param->getValue() >= 0.5f;
        rightTopControls.tiltPosButton.setButtonText(initialState ? "POST" : "PRE");
    }
    
    // DOWNSAMPLE slider - área derecha superior
    rightTopControls.downsampleSlider.setComponentID("m_DOWNSAMPLE");
    rightTopControls.downsampleSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rightTopControls.downsampleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    rightTopControls.downsampleSlider.setLookAndFeel(&sliderLAFBig);
    rightTopControls.downsampleSlider.setTextBoxIsEditable(true);
    rightTopControls.downsampleSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    rightTopControls.downsampleSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFD9B2FF));  // Púrpura pálido para DECI
    rightTopControls.downsampleSlider.setRange(0.0, 100.0, 1.0);  // m_DOWNSAMPLE: factor 0-100
    rightTopControls.downsampleSlider.setDoubleClickReturnValue(true, 0.0);  // Default value
    rightTopControls.downsampleSlider.setPopupDisplayEnabled(false, false, this);
    // IMPORTANTE: Configurar formatter ANTES de setValue para evitar bug de inicialización
    rightTopControls.downsampleSlider.textFromValueFunction = [](double value) {
        // Mostrar directo 0-100 como 0-100%
        return juce::String(static_cast<int>(value)) + " %";
    };
    rightTopControls.downsampleSlider.valueFromTextFunction = [](const juce::String& text) {
        auto trimmed = text.trim();
        // Eliminar símbolo de porcentaje si existe
        if (trimmed.endsWith("%"))
            trimmed = trimmed.dropLastCharacters(1).trim();
        
        // Mapear directo 0-100 ingresado a 0-100 interno
        auto percentage = trimmed.getDoubleValue();
        return juce::jlimit(0.0, 100.0, percentage);
    };
    rightTopControls.downsampleSlider.setValue(0.0);  // Default 0 (sin downsampling) - ahora con formatter activo
    addAndMakeVisible(rightTopControls.downsampleSlider);
    if (auto* param = processor.apvts.getParameter("m_DOWNSAMPLE"))
    {
        rightTopControls.downsampleAttachment = std::make_unique<CustomSliderAttachment>(
            *param, rightTopControls.downsampleSlider, &undoManager);
        rightTopControls.downsampleAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // DOWNSAMPLE button - control de activación
    rightTopControls.downsampleButton.setComponentID("downsampleon");
    rightTopControls.downsampleButton.setLookAndFeel(transparentButtonLAF.get());  // Usar fondo transparente
    rightTopControls.downsampleButton.setButtonText("DECIMATOR");
    rightTopControls.downsampleButton.setClickingTogglesState(true);
    rightTopControls.downsampleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightTopControls.downsampleButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Transparente para gradiente
    rightTopControls.downsampleButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xFFD9B2FF));  // Púrpura pálido como el slider
    rightTopControls.downsampleButton.setColour(juce::TextButton::textColourOnId, juce::Colour(0xFFD9B2FF));  // Púrpura pálido como el slider
    rightTopControls.downsampleButton.addListener(this);
    addAndMakeVisible(rightTopControls.downsampleButton);
    if (auto* param = processor.apvts.getParameter("n_DOWNSAMPLEON"))
    {
        rightTopControls.downsampleButtonAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, rightTopControls.downsampleButton, &undoManager);
        rightTopControls.downsampleButtonAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
    }
    
    // DC slider - área derecha inferior, junto a REL
    rightBottomKnobs.dcSlider.setComponentID("dc");
    rightBottomKnobs.dcSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    rightBottomKnobs.dcSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);
    rightBottomKnobs.dcSlider.setLookAndFeel(&sliderLAFBig);
    rightBottomKnobs.dcSlider.setTextBoxIsEditable(true);
    rightBottomKnobs.dcSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    rightBottomKnobs.dcSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xFFFEB2B2));  // Rosa pálido como distorsión
    rightBottomKnobs.dcSlider.setRange(0.0, 1.0, 0.01);  // c_DC: continuo 0-1 para armónicos pares
    rightBottomKnobs.dcSlider.setValue(0.0);  // Default 0 (sin asimetría)
    rightBottomKnobs.dcSlider.setDoubleClickReturnValue(true, 0.0);  // Default value
    rightBottomKnobs.dcSlider.setPopupDisplayEnabled(false, false, this);
    rightBottomKnobs.dcSlider.setNumDecimalPlacesToDisplay(0);
    // Mostrar como porcentaje
    rightBottomKnobs.dcSlider.textFromValueFunction = [](double value) {
        return juce::String(static_cast<int>(value * 101)) + " %";
    };
    rightBottomKnobs.dcSlider.valueFromTextFunction = [](const juce::String& text) {
        auto trimmed = text.trim();
        // Eliminar símbolo de porcentaje si existe
        if (trimmed.endsWith("%"))
            trimmed = trimmed.dropLastCharacters(1).trim();
        
        // Convertir a número y normalizar de 0-100 a 0-1
        auto percentage = trimmed.getDoubleValue();
        return juce::jlimit(0.0, 1.0, percentage / 100.0);
    };
    addAndMakeVisible(rightBottomKnobs.dcSlider);
    if (auto* param = processor.apvts.getParameter("c_DC"))
    {
        rightBottomKnobs.dcAttachment = std::make_unique<CustomSliderAttachment>(
            *param, rightBottomKnobs.dcSlider, &undoManager);
        rightBottomKnobs.dcAttachment->onParameterChange = [this]() { handleParameterChange(); };
    } 
    // Tooltip actualizado via getTooltipText("dc") en updateAllTooltips()


    
    
    
    
    
    
    // Conectar perillas al transfer display
    
    // === FILTROS DE ENTRADA ===
    // Slider HPF - copia EXACTA de ExpansorGate
    sidechainControls.xLowSlider.setName("hpf");
    sidechainControls.xLowSlider.setComponentID("hpf");
    sidechainControls.xLowSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sidechainControls.xLowSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, 16);
    sidechainControls.xLowSlider.setLookAndFeel(&sliderLAFBig);  // Usar LAF grande como ExpansorGate
    sidechainControls.xLowSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.xLowSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.xLowSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    sidechainControls.xLowSlider.setTextBoxIsEditable(true);
    sidechainControls.xLowSlider.setEnabled(true);  // Inicialmente habilitado
    sidechainControls.xLowSlider.setAlpha(1.0f);  // Inicialmente visible
    sidechainControls.xLowSlider.setDoubleClickReturnValue(true, 250.0f);  // Nuevo default 250Hz
    sidechainControls.xLowSlider.setPopupDisplayEnabled(false, false, this);
    sidechainControls.xLowSlider.setNumDecimalPlacesToDisplay(0);
    // Formato de texto personalizado para frecuencia
    sidechainControls.xLowSlider.textFromValueFunction = [](double value) {
        if (value < 1000.0)
            return juce::String(static_cast<int>(value));
        else
            return juce::String(value / 1000.0, 1) + "k";
    };
    sidechainControls.xLowSlider.setTextValueSuffix(" Hz");
    // Configurar rango para XOver Low (20-1000 Hz)
    sidechainControls.xLowSlider.setRange(20.0, 1000.0, 1.0);
    sidechainControls.xLowSlider.setSkewFactorFromMidPoint(250.0);  // 250Hz en el centro
    addAndMakeVisible(sidechainControls.xLowSlider);
    if (auto* param = processor.apvts.getParameter("j_HPF"))
    {
        sidechainControls.xLowAttachment = std::make_unique<CustomSliderAttachment>(
            *param, sidechainControls.xLowSlider, &undoManager);
        sidechainControls.xLowAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // Slider BAND - selector de banda del crossover (0=low, 1=mid, 2=high) - HORIZONTAL
    sidechainControls.bandSlider.setName("band");
    sidechainControls.bandSlider.setComponentID("band");
    sidechainControls.bandSlider.setSliderStyle(juce::Slider::LinearHorizontal);  // Slider horizontal
    sidechainControls.bandSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);  // Sin text box
    sidechainControls.bandSlider.setLookAndFeel(&bandSliderLAF);  // Usar el LAF personalizado con gradiente
    sidechainControls.bandSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::white.withAlpha(0.12f));  // Fondo blanco muy sutil
    sidechainControls.bandSlider.setColour(juce::Slider::trackColourId, juce::Colours::transparentBlack);  // Sin track de progreso
    sidechainControls.bandSlider.setColour(juce::Slider::thumbColourId, juce::Colours::white);  // Color base (será sobrescrito por LAF)
    sidechainControls.bandSlider.setTextBoxIsEditable(true);
    sidechainControls.bandSlider.setEnabled(true);  // Inicialmente habilitado
    sidechainControls.bandSlider.setAlpha(1.0f);  // Inicialmente visible
    sidechainControls.bandSlider.setDoubleClickReturnValue(true, 1.0f);  // Default = mid
    sidechainControls.bandSlider.setPopupDisplayEnabled(false, false, this);
    sidechainControls.bandSlider.setNumDecimalPlacesToDisplay(2);
    // Sin formato de texto ya que no hay text box
    // Configurar rango 0-2 para interpolar entre las 3 bandas
    sidechainControls.bandSlider.setRange(0.0, 2.0, 0.01);
    addAndMakeVisible(sidechainControls.bandSlider);
    if (auto* param = processor.apvts.getParameter("o_BAND"))
    {
        sidechainControls.bandAttachment = std::make_unique<CustomSliderAttachment>(
            *param, sidechainControls.bandSlider, &undoManager);
        sidechainControls.bandAttachment->onParameterChange = [this]() { 
            handleParameterChange(); 
            // Repintar el botón FILTERS para actualizar gradiente con nuevo valor de banda
            sidechainControls.scButton.repaint();
        };
    }
    
    // Configurar las labels para BAND (Low, Mid, High) con colores que coinciden con el analizador
    // Colores tomados de SpectrumAnalyzerComponent para consistencia visual
    const juce::Colour lowBandColour = juce::Colour(0xFF9C27B0);  // Púrpura (graves)
    const juce::Colour highBandColour = juce::Colour(0xFF2196F3);  // Azul (agudos)
    const juce::Colour midBandColour = lowBandColour.interpolatedWith(highBandColour, 0.5f);  // Mezcla púrpura-azul
    
    sidechainControls.bandLowLabel.setText("Low", juce::dontSendNotification);
    sidechainControls.bandLowLabel.setFont(juce::Font(juce::FontOptions(11.0f)));
    sidechainControls.bandLowLabel.setColour(juce::Label::textColourId, lowBandColour);
    sidechainControls.bandLowLabel.setJustificationType(juce::Justification::centredLeft);
    sidechainControls.bandLowLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(sidechainControls.bandLowLabel);
    
    sidechainControls.bandMidLabel.setText("Mid", juce::dontSendNotification);
    sidechainControls.bandMidLabel.setFont(juce::Font(juce::FontOptions(11.0f)));
    sidechainControls.bandMidLabel.setColour(juce::Label::textColourId, midBandColour);
    sidechainControls.bandMidLabel.setJustificationType(juce::Justification::centred);
    sidechainControls.bandMidLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(sidechainControls.bandMidLabel);
    
    sidechainControls.bandHighLabel.setText("High", juce::dontSendNotification);
    sidechainControls.bandHighLabel.setFont(juce::Font(juce::FontOptions(11.0f)));
    sidechainControls.bandHighLabel.setColour(juce::Label::textColourId, highBandColour);
    sidechainControls.bandHighLabel.setJustificationType(juce::Justification::centredRight);
    sidechainControls.bandHighLabel.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(sidechainControls.bandHighLabel);
    
    // Slider LPF - copia EXACTA de ExpansorGate
    sidechainControls.xHighSlider.setName("lpf");
    sidechainControls.xHighSlider.setComponentID("lpf");
    sidechainControls.xHighSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sidechainControls.xHighSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 60, 16);
    sidechainControls.xHighSlider.setLookAndFeel(&sliderLAFBig);  // Usar LAF grande como ExpansorGate
    sidechainControls.xHighSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.xHighSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);  // Blanco fijo
    sidechainControls.xHighSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    sidechainControls.xHighSlider.setTextBoxIsEditable(true);
    sidechainControls.xHighSlider.setEnabled(true);  // Inicialmente habilitado
    sidechainControls.xHighSlider.setAlpha(1.0f);  // Inicialmente visible
    sidechainControls.xHighSlider.setDoubleClickReturnValue(true, 5000.0f);  // Nuevo default 5kHz
    sidechainControls.xHighSlider.setPopupDisplayEnabled(false, false, this);
    sidechainControls.xHighSlider.setNumDecimalPlacesToDisplay(0);
    // Formato de texto personalizado para frecuencia
    sidechainControls.xHighSlider.textFromValueFunction = [](double value) {
        if (value < 1000.0)
            return juce::String(static_cast<int>(value));
        else
            return juce::String(value / 1000.0, 1) + "k";
    };
    sidechainControls.xHighSlider.setTextValueSuffix(" Hz");
    // Configurar rango para XOver High (1000-20000 Hz)
    sidechainControls.xHighSlider.setRange(1000.0, 20000.0, 1.0);
    sidechainControls.xHighSlider.setSkewFactorFromMidPoint(5000.0);  // 5kHz en el centro
    addAndMakeVisible(sidechainControls.xHighSlider);
    if (auto* param = processor.apvts.getParameter("k_LPF"))
    {
        sidechainControls.xHighAttachment = std::make_unique<CustomSliderAttachment>(
            *param, sidechainControls.xHighSlider, &undoManager);
        sidechainControls.xHighAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }

    // Botón FILTERS (antes SC) - VISIBLE para activar/desactivar filtros
    sidechainControls.scButton.setClickingTogglesState(true);
    sidechainControls.scButton.setLookAndFeel(filtersButtonLAF.get());  // Aplicar LAF con gradiente
    sidechainControls.scButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    sidechainControls.scButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Ahora manejado por LAF
    sidechainControls.scButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    sidechainControls.scButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    sidechainControls.scButton.addListener(this);
    addAndMakeVisible(sidechainControls.scButton);
    sidechainControls.scAttachment = std::make_unique<UndoableButtonAttachment>(
        *processor.apvts.getParameter("l_SC"), sidechainControls.scButton, &undoManager);
    sidechainControls.scAttachment->onParameterChange = [this]() { handleParameterChange(); };
    // Tooltip actualizado via getTooltipText("sc") en updateAllTooltips()
    
    // Botón SOLO - para solo de banda seleccionada (p_BANDSOLO)
    sidechainControls.bandSoloButton.setComponentID("bandsolo");
    sidechainControls.bandSoloButton.setLookAndFeel(soloButtonLAF.get());  // Usar LAF específico con gradiente invertido
    sidechainControls.bandSoloButton.setButtonText("SOLO");
    sidechainControls.bandSoloButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    sidechainControls.bandSoloButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Transparente para gradiente
    sidechainControls.bandSoloButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textSecondary.withAlpha(0.7f));
    sidechainControls.bandSoloButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    sidechainControls.bandSoloButton.setClickingTogglesState(true);
    addAndMakeVisible(sidechainControls.bandSoloButton);
    if (auto* param = processor.apvts.getParameter("p_BANDSOLO"))
    {
        sidechainControls.bandSoloAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, sidechainControls.bandSoloButton, &undoManager);
        
        // Callback para cambios de estado
        sidechainControls.bandSoloAttachment->onStateChange = [](bool) {
            // Ya no necesitamos cambiar el texto ni los colores
        };
        
        // Callback para clicks del usuario
        sidechainControls.bandSoloAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        
        // Sincronización inicial - ya no necesitamos cambiar el texto
    }
    
    // Botón LIMIT - limitador brickwall de protección (p_SAFELIMITON)
    rightTopControls.safeLimitButton.setComponentID("safelimit");
    rightTopControls.safeLimitButton.setLookAndFeel(filtersButtonLAF.get());  // Usar gradiente como FILTERS
    rightTopControls.safeLimitButton.setButtonText("LIM");
    rightTopControls.safeLimitButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    rightTopControls.safeLimitButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);  // Transparente para gradiente
    rightTopControls.safeLimitButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    rightTopControls.safeLimitButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    rightTopControls.safeLimitButton.setClickingTogglesState(true);
    addAndMakeVisible(rightTopControls.safeLimitButton);
    if (auto* param = processor.apvts.getParameter("p_SAFELIMITON"))
    {
        rightTopControls.safeLimitAttachment = std::make_unique<UndoableButtonAttachment>(
            *param, rightTopControls.safeLimitButton, &undoManager);
        
        // Callback para cambios de estado (texto fijo LIMIT)
        rightTopControls.safeLimitAttachment->onStateChange = [](bool) {
            // Texto siempre es "LIMIT", no cambia con el estado
        };
        
        // Callback para clicks del usuario
        rightTopControls.safeLimitAttachment->onParameterChange = [this]() {
            handleParameterChange();
        };
        
        // Sincronización inicial - texto siempre es "LIMIT"
        rightTopControls.safeLimitButton.setButtonText("LIM");
    }
    // NOTA: Botón LPF y Slider de frecuencia de tono movidos a leftBottomKnobs
    */
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
    
    /*
    // Medidores de sidechain (siempre visibles)
    scMeterL.setVisible(true);
    scMeterR.setVisible(true);
    addAndMakeVisible(scMeterL);
    addAndMakeVisible(scMeterR);
    */
    
    // COMENTADO: Sliders incorrectos - deberían ser input/output para reverb
    /*
    // Slider de trim
    trimSlider.setComponentID("trim");
    addAndMakeVisible(trimSlider);
    
    // Vincular slider de trim al parámetro k_INPUT - ahora usando attachment thread-safe
    if (auto* param = processor.apvts.getParameter("k_INPUT"))
    {
        trimAttachment = std::make_unique<CustomSliderAttachment>(
            *param, trimSlider, &undoManager);
        trimAttachment->onParameterChange = [this]() { handleParameterChange(); };
    }
    
    // Slider de makeup - RESTAURADO para i_MAKEUP
    makeupSlider.setComponentID("makeup");
    addAndMakeVisible(makeupSlider);
    
    // Vincular slider de makeup al parámetro l_OUTPUT - usando attachment thread-safe
    if (auto* param = processor.apvts.getParameter("l_OUTPUT"))
    {
        makeupAttachment = std::make_unique<CustomSliderAttachment>(
            *param, makeupSlider, &undoManager);
        makeupAttachment->onParameterChange = [this]() { handleParameterChange(); };
        
        // Configurar skew factor SOLO para el slider de salida
        // El attachment ya estableció el rango desde el parámetro (-24 a +12)
        makeupSlider.setSkewFactorFromMidPoint(0.0);  // Centrar 0 dB visualmente
    }
    */

    /*
    // Slider de trim de sidechain
    scTrimSlider.setComponentID("sctrim");
    addAndMakeVisible(scTrimSlider);
    
    // Establecer propiedades iniciales para el slider de trim de sidechain
    // scTrimSlider.setTooltip(JUCE_UTF8("SC TRIM: ganancia de entrada del sidechain entre -12 y +12 dB.\nAjusta el nivel del sidechain externo.\nValor por defecto: 0 dB, se activa con EXT KEY"));
    
    // Vincular slider de trim de sidechain al parámetro y_SCTRIM - ahora usando attachment thread-safe
    // if (auto* param = processor.apvts.getParameter("y_SCTRIM"))
    // {
    //     scTrimAttachment = std::make_unique<CustomSliderAttachment>(
    //         *param, scTrimSlider, &undoManager);
    //     scTrimAttachment->onParameterChange = [this]() { handleParameterChange(); };
    // }
    
    // Inicialmente visible pero con alpha reducido cuando EXT KEY está apagado
    scTrimSlider.setVisible(true);
    scTrimSlider.setEnabled(false);
    scTrimSlider.setAlpha(0.25f);
    */
    
    //==========================================================================
    // CONFIGURAR DISPLAYS INDEPENDIENTES
    //==========================================================================
    
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
                leftTopKnobs.ceilingSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("b_DRIVE")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightBottomKnobs.driveSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("d_MODE")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                rightBottomKnobs.modeSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("l_OUTPUT")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                makeupSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("j_HPF")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                sidechainControls.xLowSlider.setValue(realValue, juce::sendNotificationSync);
            }
            if (auto* param = processor.apvts.getParameter("k_LPF")) {
                float defaultValue = param->getDefaultValue();
                float realValue = param->getNormalisableRange().convertFrom0to1(defaultValue);
                sidechainControls.xHighSlider.setValue(realValue, juce::sendNotificationSync);
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

            // Restaurar FFT/CURVES a su estado por defecto (FFT)
            // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado
            utilityButtons.runGraphicsButton.setButtonText("FFT");
    // distortionCurveDisplay.setVisible(false);
    // spectrumAnalyzer.setVisible(true);
            // Actualizar color del botón para modo FFT
            utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId, 
                                                      juce::Colours::transparentBlack);  // FFT: transparente
            // Habilitar zoom button en modo FFT
            utilityButtons.zoomButton.setAlpha(1.0f);
            utilityButtons.zoomButton.setEnabled(true);
            
            // Establecer modo FFT para preset DEFAULT
            // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado
            processor.displayModeIsFFT = true;
            utilityButtons.runGraphicsButton.setButtonText("FFT");
    // distortionCurveDisplay.setVisible(false);
    // spectrumAnalyzer.setVisible(true);

            // Reactivar undo después carga de preset
            isLoadingPreset = false;
            
            // IMPORTANTE: Forzar la sincronización directa de Gen~ para asegurar valores correctos de los parámetros
            // Esto replica la misma sincronización realizada durante la instanciación del plugin
            for (int i = 0; i < JCBReverb::num_params(); i++) {
                auto paramName = juce::String(JCBReverb::getparametername(processor.getPluginState(), i));
                if (auto* param = processor.apvts.getRawParameterValue(paramName)) {
                    float value = param->load();
                    
                    // Aplicar la misma validación que en parameterChanged() (DISTORTION)
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
        else if (presetName.startsWith("Bass_") || presetName.startsWith("Drums_") || 
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
                            
                            // Restaurar estado del modo de visualización FFT/CURVES si está presente
                            auto uiSettings = stateTree.getChildWithName("UISettings");
                            if (uiSettings.isValid()) {
                                bool isFFT = uiSettings.getProperty("displayModeIsFFT", false);
                                // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado // Solo FFT para reverb
                                // Actualizar botón graphics
                                utilityButtons.runGraphicsButton.setButtonText(isFFT ? "FFT" : "curves");
                                // Actualizar color del botón
                                utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId,
                                                                          isFFT ? juce::Colours::transparentBlack : DarkTheme::accent.withAlpha(0.3f));
                                // Actualizar visibilidad de componentes
    // distortionCurveDisplay.setVisible(!isFFT);
    // spectrumAnalyzer.setVisible(isFFT);
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
                    
                    // Restaurar estado del modo de visualización FFT/CURVES si está presente
                    auto uiSettings = stateTree.getChildWithName("UISettings");
                    if (uiSettings.isValid()) {
                        bool isFFT = uiSettings.getProperty("displayModeIsFFT", false);
                        // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado // Solo FFT para reverb
                        // Actualizar botón graphics
                        utilityButtons.runGraphicsButton.setButtonText(isFFT ? "FFT" : "curves");
                        // Actualizar color del botón
                        utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId,
                                                                  isFFT ? juce::Colours::transparentBlack : DarkTheme::accent.withAlpha(0.3f));
                        // Actualizar visibilidad de componentes
    // distortionCurveDisplay.setVisible(!isFFT);
    // spectrumAnalyzer.setVisible(isFFT);
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
        if (presetName.startsWith("Bass_")) {
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
    topButtons.abStateButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff9c27b0));  // Comenzar con púrpura para A
    topButtons.abStateButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    topButtons.abStateButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    topButtons.abStateButton.addListener(this);
    topButtons.abStateButton.setButtonText("A");  // Comenzar con A
    addAndMakeVisible(topButtons.abStateButton);
    topButtons.abStateButton.setEnabled(true);  // Now implemented!
    
    // Botón copiar A/B
    topButtons.abCopyButton.setClickingTogglesState(false);
    topButtons.abCopyButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    topButtons.abCopyButton.setColour(juce::TextButton::textColourOffId, DarkTheme::textPrimary);
    topButtons.abCopyButton.setColour(juce::TextButton::textColourOnId, DarkTheme::textPrimary);
    topButtons.abCopyButton.addListener(this);
    topButtons.abCopyButton.setButtonText("A-B");  // Start showing A to B
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
    // COMENTADO: Llamadas a métodos de actualización para controles de distorsión que no existen
    /*
    // Actualizar estados de componentes de filtro
    updateSidechainComponentStates();
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

// COMENTADO: Métodos update para controles de distorsión que no existen en reverb
/*
void JCBReverbAudioProcessorEditor::updateSidechainComponentStates()
{
    // Obtener estado del botón FILTERS
    const bool filtersActive = sidechainControls.scButton.getToggleState();
    
    // Los filtros HPF/BAND/LPF activos solo cuando FILTERS está ON
    sidechainControls.xLowSlider.setVisible(true);  // Siempre visibles
    sidechainControls.bandSlider.setVisible(true);  // Siempre visible
    sidechainControls.xHighSlider.setVisible(true);  // Siempre visibles
    sidechainControls.xLowSlider.setEnabled(filtersActive);  // Activos solo si FILTERS ON
    sidechainControls.bandSlider.setEnabled(filtersActive);  // Activo solo si FILTERS ON
    sidechainControls.xHighSlider.setEnabled(filtersActive);   // Activos solo si FILTERS ON
    sidechainControls.xLowSlider.setAlpha(filtersActive ? 1.0f : 0.5f);  // Alpha indica estado
    sidechainControls.bandSlider.setAlpha(filtersActive ? 1.0f : 0.5f);  // Alpha indica estado
    sidechainControls.xHighSlider.setAlpha(filtersActive ? 1.0f : 0.5f);   // Alpha indica estado
    
    // Actualizar alpha de las labels de BAND
    float labelAlpha = filtersActive ? 0.85f : 0.425f;  // Mismo ratio que en paintOverChildren
    sidechainControls.bandLowLabel.setAlpha(labelAlpha);
    sidechainControls.bandMidLabel.setAlpha(labelAlpha);
    sidechainControls.bandHighLabel.setAlpha(labelAlpha);
    
    // SOLO BAND button - activo solo cuando FILTERS está ON
    sidechainControls.bandSoloButton.setEnabled(filtersActive);
    sidechainControls.bandSoloButton.setAlpha(filtersActive ? 1.0f : 0.5f);
}

void JCBReverbAudioProcessorEditor::updateDistortionComponentStates()
{
    // Obtener estado del botón distOnButton (p_DISTON)
    const bool distortionActive = rightBottomKnobs.distOnButton.getToggleState();
    
    // MODE slider - activo solo cuando distorsión está ON
    rightBottomKnobs.modeSlider.setEnabled(distortionActive);
    rightBottomKnobs.modeSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
    
    // EVEN (DC) slider - activo solo cuando distorsión está ON
    rightBottomKnobs.dcSlider.setEnabled(distortionActive);
    rightBottomKnobs.dcSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
    
    // DRIVE slider - activo solo cuando distorsión está ON
    rightBottomKnobs.driveSlider.setEnabled(distortionActive);
    rightBottomKnobs.driveSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
    
    // CEIL slider - activo solo cuando distorsión está ON
    leftTopKnobs.ceilingSlider.setEnabled(distortionActive);
    leftTopKnobs.ceilingSlider.setAlpha(distortionActive ? 1.0f : 0.5f);
    
    // TILT POS button (PRE/POST) - activo solo cuando distorsión está ON
    rightTopControls.tiltPosButton.setEnabled(distortionActive);
    rightTopControls.tiltPosButton.setAlpha(distortionActive ? 1.0f : 0.5f);
    
    // Actualizar alpha del texto del botón tiltPos según estado de distorsión
    // PRE y POST deben verse igual (no hay diferencia entre los dos estados)
    rightTopControls.tiltPosButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFFA6DAD5).withAlpha(distortionActive ? 1.0f : 0.5f)  // Verde agua pálido como tiltSlider
    );
    rightTopControls.tiltPosButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFFA6DAD5).withAlpha(distortionActive ? 1.0f : 0.5f)  // Verde agua pálido como tiltSlider
    );
    
    // Actualizar alpha del texto del botón distOn según estado
    rightBottomKnobs.distOnButton.setColour(
        juce::TextButton::textColourOffId, 
        DarkTheme::textSecondary.withAlpha(0.7f)
    );
    rightBottomKnobs.distOnButton.setColour(
        juce::TextButton::textColourOnId, 
        juce::Colour(0xFFFEB2B2)  // Rosa pálido como los sliders de distorsión
    );
    
    // Actualizar estado de la curva de distorsión
    // distortionCurveDisplay.setDistortionEnabled(distortionActive);
}

void JCBReverbAudioProcessorEditor::updateBitCrusherComponentStates()
{
    // Obtener estado del botón BIT CRUSHER (h_BITSON)
    const bool bitCrusherActive = rightBottomKnobs.bitButton.getToggleState();
    
    // BIT slider - siempre interactivo pero con alpha reducido cuando BIT CRUSHER está OFF
    rightTopControls.bitsSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
    rightTopControls.bitsSlider.setAlpha(bitCrusherActive ? 1.0f : 0.5f);
    
    // Actualizar alpha del texto del botón BIT CRUSHER según estado
    rightBottomKnobs.bitButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFFB2FFB3).withAlpha(bitCrusherActive ? 0.7f : 0.4f)  // Verde pálido
    );
    rightBottomKnobs.bitButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFFB2FFB3).withAlpha(bitCrusherActive ? 1.0f : 0.5f)  // Verde pálido
    );
}

void JCBReverbAudioProcessorEditor::updateDownsampleComponentStates()
{
    // Obtener estado del botón DOWNSAMPLE (n_DOWNSAMPLEON)
    const bool downsampleActive = rightTopControls.downsampleButton.getToggleState();
    
    // DECI slider - siempre interactivo pero con alpha reducido cuando DOWNSAMPLE está OFF
    rightTopControls.downsampleSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
    rightTopControls.downsampleSlider.setAlpha(downsampleActive ? 1.0f : 0.5f);
    
    // Actualizar alpha del texto del botón DOWNSAMPLE según estado
    rightTopControls.downsampleButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFFD9B2FF).withAlpha(downsampleActive ? 0.7f : 0.4f)  // Púrpura pálido
    );
    rightTopControls.downsampleButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFFD9B2FF).withAlpha(downsampleActive ? 1.0f : 0.5f)  // Púrpura pálido
    );
}

void JCBReverbAudioProcessorEditor::updateTiltComponentStates()
{
    // Obtener estado del botón TILT (s_TILTON)
    const bool tiltActive = rightTopControls.tiltOnButton.getToggleState();
    
    // TILT slider - siempre interactivo pero con alpha reducido cuando TILT está OFF
    rightTopControls.tiltSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
    rightTopControls.tiltSlider.setAlpha(tiltActive ? 1.0f : 0.5f);
    
    // TILT POS button - siempre interactivo pero con alpha reducido cuando TILT está OFF
    rightTopControls.tiltPosButton.setEnabled(true);  // Siempre habilitado para pre-configuración
    rightTopControls.tiltPosButton.setAlpha(tiltActive ? 1.0f : 0.5f);
    rightTopControls.tiltPosButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 1.0f : 0.5f)  // Verde agua pálido
    );
    rightTopControls.tiltPosButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 1.0f : 0.5f)  // Verde agua pálido
    );
    
    // Actualizar alpha del texto del botón TILT según estado
    rightTopControls.tiltOnButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 0.7f : 0.3f)  // Verde agua pálido
    );
    rightTopControls.tiltOnButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFFA6DAD5).withAlpha(tiltActive ? 1.0f : 0.4f)  // Verde agua pálido
    );
}

void JCBReverbAudioProcessorEditor::updateToneLpfComponentStates()
{
    // Obtener estado del botón TONE LPF (q_TONEON)
    const bool toneLpfActive = leftBottomKnobs.toneLpfButton.getToggleState();
    
    // TONE FREQ slider - siempre interactivo pero con alpha reducido cuando TONE LPF está OFF
    leftBottomKnobs.toneFreqSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
    leftBottomKnobs.toneFreqSlider.setAlpha(toneLpfActive ? 1.0f : 0.5f);
    
    // TONE Q slider - siempre interactivo pero con alpha reducido cuando TONE LPF está OFF
    leftBottomKnobs.toneQSlider.setEnabled(true);  // Siempre habilitado para pre-configuración
    leftBottomKnobs.toneQSlider.setAlpha(toneLpfActive ? 1.0f : 0.5f);
    
    // TONE POS button - siempre interactivo pero con alpha reducido cuando TONE LPF está OFF
    leftBottomKnobs.tonePosButton.setEnabled(true);  // Siempre habilitado para pre-configuración
    leftBottomKnobs.tonePosButton.setAlpha(toneLpfActive ? 1.0f : 0.5f);
    leftBottomKnobs.tonePosButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 1.0f : 0.5f)  // Azul claro TONE
    );
    leftBottomKnobs.tonePosButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 1.0f : 0.5f)  // Azul claro TONE
    );
    
    // Actualizar alpha del texto del botón TONE LPF según estado
    leftBottomKnobs.toneLpfButton.setColour(
        juce::TextButton::textColourOffId,
        juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 0.7f : 0.3f)  // Azul claro TONE
    );
    leftBottomKnobs.toneLpfButton.setColour(
        juce::TextButton::textColourOnId,
        juce::Colour(0xFF6EB8F6).withAlpha(toneLpfActive ? 1.0f : 0.4f)  // Azul claro TONE
    );
}
*/

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
    const bool soloScActive = false;  // Maximizer has no sidechain
    
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
    const bool soloScActive = false;  // Maximizer has no sidechain
    const bool extKeyActive = false;  // Maximizer has no external key
    
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
        leftTopKnobs.ceilingSlider.setValue(param->load(), juce::dontSendNotification);
    */
    
    // if (auto* param = processor.apvts.getRawParameterValue("c_RATIO"))
    //     leftTopKnobs.ratioSlider.setValue(param->load(), juce::dontSendNotification);
        
  
    // if (auto* param = processor.apvts.getRawParameterValue("q_KNEE"))
    //     leftTopKnobs.kneeSlider.setValue(param->load(), juce::dontSendNotification);
    
        
    // DISTORTION: n_LOOKAHEAD eliminado - no existe en distorsionador
        
        
    
    // Right top controls
        
    // MAXIMIZER: g_REACT no existe - parámetro eliminado según CONTEXTO.txt
    // if (auto* param = processor.apvts.getRawParameterValue("g_REACT"))
    //     rightTopControls.reactSlider.setValue(param->load(), juce::dontSendNotification);
    
    // COMENTADO: Más sliders de distorsión
    /*
    // Right bottom knobs - Todos usan CustomSliderAttachment
    if (auto* param = processor.apvts.getRawParameterValue("b_DRIVE"))
        rightBottomKnobs.driveSlider.setValue(param->load(), juce::dontSendNotification);
    
    if (auto* param = processor.apvts.getRawParameterValue("d_MODE"))
        rightBottomKnobs.modeSlider.setValue(param->load(), juce::dontSendNotification);
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
        sidechainControls.xLowSlider.setValue(param->load(), juce::dontSendNotification);
        
    if (auto* param = processor.apvts.getRawParameterValue("k_LPF"))
        sidechainControls.xHighSlider.setValue(param->load(), juce::dontSendNotification);
    
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
    
    // Bypass button (interno Gen: z_BYPASSS)
    {
        bool toggleState = false;
        if (auto* st = processor.getPluginState())
        {
            for (int i = 0; i < JCBReverb::num_params(); ++i)
            {
                if (juce::String(JCBReverb::getparametername(st, i)) == "z_BYPASSS")
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
        .getChildFile("JCBDistortion");

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
    juce::StringArray categoryOrder = {"Bass", "Drums", "Fx", "Guitars"};
    
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
                
                // Añadir estado del modo de visualización FFT/CURVES
                auto uiSettings = state.getOrCreateChildWithName("UISettings", nullptr);
                // uiSettings.setProperty("displayModeIsFFT", currentDisplayMode == DisplayMode::FFT, nullptr); // COMENTADO: DisplayMode eliminado
                
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
                        
                        // Añadir estado del modo de visualización FFT/CURVES
                        auto uiSettings = state.getOrCreateChildWithName("UISettings", nullptr);
                        // uiSettings.setProperty("displayModeIsFFT", currentDisplayMode == DisplayMode::FFT, nullptr); // COMENTADO: DisplayMode eliminado
                        
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
                
                // Añadir estado del modo de visualización FFT/CURVES
                auto uiSettings = state.getOrCreateChildWithName("UISettings", nullptr);
                // uiSettings.setProperty("displayModeIsFFT", currentDisplayMode == DisplayMode::FFT, nullptr); // COMENTADO: DisplayMode eliminado
                
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
    // Actualizar tooltips de botones TODO usando getTooltipText() para consistencia
    utilityButtons.hqButton.setTooltip(getTooltipText("hq"));
    utilityButtons.dualMonoButton.setTooltip(getTooltipText("dualmono"));
    utilityButtons.msButton.setTooltip(getTooltipText("ms"));
    topButtons.abStateButton.setTooltip(getTooltipText("abstate"));
    utilityButtons.midiLearnButton.setTooltip(getTooltipText("midilearn"));
    
    // Stereo Linked button - se maneja en updateAllTooltips()
    
    
    // Zoom y Diagram mantienen sus tooltips actuales ya que son funcionales
}

void JCBReverbAudioProcessorEditor::updateAllTooltips()
{
    // Actualizar todos los tooltips de componentes basado en el idioma actual
    
    // Título
    titleLink.setTooltip(getTooltipText("title"));
    
    // COMENTADO: Tooltips de controles de distorsión que no existen
    /*
    // Perillas - superiores izquierdas
    leftBottomKnobs.drywetSlider.setTooltip(getTooltipText("drywet"));
    leftTopKnobs.ceilingSlider.setTooltip(getTooltipText("ceiling"));  // NUEVO - tooltip para e_CEILING
    // MAXIMIZER: c_RATIO no existe - comentado según CONTEXTO.txt
    // leftTopKnobs.ratioSlider.setTooltip(getTooltipText("ratio"));
    // MAXIMIZER: q_KNEE no existe - comentado según CONTEXTO.txt
    // leftTopKnobs.kneeSlider.setTooltip(getTooltipText("knee"));
    
    // Perillas - lookahead movido a rightTopControls
    rightTopControls.bitsSlider.setTooltip(getTooltipText("bits"));
    rightTopControls.downsampleSlider.setTooltip(getTooltipText("downsample"));  // NUEVO - tooltip para DECI slider
    rightTopControls.downsampleButton.setTooltip(getTooltipText("downsampleon"));  // NUEVO - tooltip para DOWNSAMPLE button
    */
    
    // Perillas - superiores derechas
    // MAXIMIZER: h_RANGE no existe - comentado según CONTEXTO.txt
    // rightTopControls.rangeSlider.setTooltip(getTooltipText("range"));
    // MAXIMIZER: g_REACT no existe - comentado según CONTEXTO.txt
    // rightTopControls.reactSlider.setTooltip(getTooltipText("react"));
    // MAXIMIZER: z_SMOOTH no existe - comentado según CONTEXTO.txt
    // rightTopControls.smoothSlider.setTooltip(getTooltipText("smooth"));
    // COMENTADO: Más tooltips de controles inexistentes
    /*
    rightTopControls.tiltSlider.setTooltip(getTooltipText("tilt"));  // NUEVO - tooltip para TILT slider
    rightTopControls.tiltOnButton.setTooltip(getTooltipText("tilton"));  // NUEVO - tooltip para TILT ON button
    rightTopControls.tiltPosButton.setTooltip(getTooltipText("tiltpos"));  // NUEVO - tooltip para TILT POS button
    
    // Perillas - inferiores derechas
    rightBottomKnobs.driveSlider.setTooltip(getTooltipText("drive"));
    rightBottomKnobs.modeSlider.setTooltip(getTooltipText("mode"));
    rightBottomKnobs.distOnButton.setTooltip(getTooltipText("diston"));  // NUEVO - tooltip para DIST ON button
    rightBottomKnobs.bitButton.setTooltip(getTooltipText("bitcrusher"));    // NUEVO - tooltip para BIT CRUSHER button
    rightBottomKnobs.dcSlider.setTooltip(getTooltipText("even"));  // NUEVO - tooltip para EVEN slider
    // MAXIMIZER: f_HOLD no existe - comentado según CONTEXTO.txt
    // rightBottomKnobs.holdSlider.setTooltip(getTooltipText("hold"));
    // speedButton removed
    
    // Sliders de trim y makeup
    trimSlider.setTooltip(getTooltipText("trim"));
    // RESTAURADO: i_MAKEUP tooltip
    makeupSlider.setTooltip(getTooltipText("makeup"));
    */
    
    // Sliders de trim de sidechain
    // scTrimSlider.setTooltip(getTooltipText("sctrim"));
    
    // Controles de filtro de entrada (no aplican en esta UI de reverb)
    // Tooltips deshabilitados hasta que se integre la UI específica
    // sidechainControls.keyButton.setTooltip(getTooltipText("extkey"));
    // sidechainControls.soloScButton.setTooltip(getTooltipText("solosc"));
    
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

    
    // Actualizar tooltips de botones TODO
    updateTodoButtonTexts();
    
    
    // Botones de utilidad - fila inferior
    utilityButtons.stereoLinkedButton.setTooltip(getTooltipText("link"));
    
    // Tooltip para el analizador FFT (usa setHelpText porque hereda de TooltipClient)
    // spectrumAnalyzer.setHelpText(getTooltipText("spectrum"));
    
    // Tooltip para el visualizador de curvas de distorsión (usa setHelpText porque hereda de TooltipClient)
    // distortionCurveDisplay.setHelpText(getTooltipText("curves"));
    // CODE button removed
}

juce::String JCBReverbAudioProcessorEditor::getTooltipText(const juce::String& key)
{
    if (currentLanguage == TooltipLanguage::Spanish)
    {
        // Spanish tooltips
        if (key == "title") return JUCE_UTF8("JCBDistortion: distorsionador multimodal v1.0.0-alpha.1\nPlugin de audio open source\nClick para créditos");
        if (key == "drywet") return JUCE_UTF8("DRY/WET: mezcla entre señal original y procesada\nControla el balance final de salida\nRango: 0 a 100% | Por defecto: 100%");
        if (key == "lookahead") return JUCE_UTF8("LOOKAHEAD: anticipación para evitar distorsión\nEvita overshooting en transitorios rápidos\nRango: 0 a 5 ms | Por defecto: 0 ms");
        if (key == "drive") return JUCE_UTF8("DRIVE: intensidad de distorsión\nControla la ganancia antes de la saturación\nRango: 1 a 50 | Por defecto: 1");
        if (key == "tilt") return JUCE_UTF8("TILT: filtro de balance tonal\nControla el equilibrio entre graves y agudos\nRango: -6 a +6 dB | Por defecto: 0 dB");
        if (key == "ceiling") return JUCE_UTF8("CEILING: techo de salida con limitador suave\nProtege contra saturación excesiva\nRango: -20 a +6 dB | Por defecto: 0 dB");
        if (key == "bitcrusher") return JUCE_UTF8("BIT CRUSHER: activa la cuantización digital\nReduce la resolución de bits para distorsión digital\nRango: OFF/ON | Por defecto: OFF");
        if (key == "bits") return JUCE_UTF8("BITS: resolución del bit crusher\nControla la cuantización digital de bits\nRango: 3 a 16 bits | Por defecto: 16 bits");
        if (key == "even") return JUCE_UTF8("EVEN: asimetría DC para armónicos pares\nAñade componente continua para generar armónicos pares\nRango: 0 a 1 | Por defecto: 0");
        if (key == "downsample") return JUCE_UTF8("DECI: factor de decimación\nReduce el sample rate para distorsión aliasing\nRango: 0 a 100% | Por defecto: 0%");
        if (key == "downsampleon") return JUCE_UTF8("DOWNSAMPLE: activa la decimación\nActiva el efecto de reducción de sample rate\nRango: OFF/ON | Por defecto: OFF");
        if (key == "tiltpos") return JUCE_UTF8("TILT POSITION: posición del filtro tilt\nPRE: antes de la distorsión | POST: después de la distorsión\nRango: PRE/POST | Por defecto: PRE");
        if (key == "mode") return JUCE_UTF8("MODE: algoritmo de distorsión\n8 tipos diferentes: Soft Clip, Sigmoid, Rectifier, etc.\nRango: 1 a 8 (mostrado) | Por defecto: 1");
        if (key == "diston") return JUCE_UTF8("DIST: activa/desactiva el bloque de distorsión\nON: distorsión activa | OFF: bypass del bloque distorsión\nRango: ON/OFF | Por defecto: ON");
        if (key == "trim") return JUCE_UTF8("TRIM: ganancia de entrada al distorsionador\nAjusta el nivel antes del procesamiento\nRango: -12 a +12 dB | Por defecto: 0 dB");
        if (key == "makeup") return JUCE_UTF8("MAKEUP: ganancia de salida de la cadena WET\nAjusta el nivel solo del procesamiento (no afecta dry/wet)\nRango: -24 a +12 dB | Por defecto: 0 dB");
        if (key == "sc") return JUCE_UTF8("FILTERS: activa el crossover de 3 bandas.\nDivide la señal en Low/Mid/High para procesamiento selectivo.\nValor por defecto: OFF");
        //if (key == "solosc") return JUCE_UTF8("SOLO SC: escucha filtros sidechain int/ext\nParámetro global, no automatizable\nRango: OFF/ON | Por defecto: OFF");
        if (key == "hpf") return JUCE_UTF8("XLow: punto de cruce bajo del crossover\nDefine la frecuencia de separación entre bandas Low y Mid\nRango: 20 a 1000 Hz | Por defecto: 250 Hz");
        if (key == "band") return JUCE_UTF8("BAND: selector de banda del crossover\nElige qué banda de frecuencia procesar (Low/Mid/High)\nRango: Low-Mid-High (interpolable) | Por defecto: Mid");
        if (key == "lpf") return JUCE_UTF8("XHigh: punto de cruce alto del crossover\nDefine la frecuencia de separación entre bandas Mid y High\nRango: 1000 Hz a 20 kHz | Por defecto: 5 kHz");
        if (key == "bandsolo") return JUCE_UTF8("SOLO BAND: solea la banda de filtro activa\nPermite escuchar solo la banda seleccionada (Low/Mid/High) a través de la cadena de procesamiento\nRango: OFF/ON | Por defecto: OFF");
        if (key == "safelimit") return JUCE_UTF8("LIM: limitador brickwall de protección\nLimitador ajustado a -0.1 dBFS para evitar sobremodulación en la salida del plugin (post dry/wet)\nRango: OFF/ON | Por defecto: OFF");
        if (key == "tonelpf") return JUCE_UTF8("RLPF: filtro paso bajo resonante de tono\nSe puede usar PRE/POST distorsionador, compensado de fase\nRango: OFF/ON | Por defecto: OFF");
        if (key == "tonefreq") return JUCE_UTF8("RLPF: filtro paso bajo resonante (2nd order RBJ)\nFrecuencia de corte ajustable para control tonal\nRango: 20 Hz a 20 kHz | Por defecto: 15 kHz");
        if (key == "toneq") return JUCE_UTF8("Q: resonancia del filtro RLPF\n0% = Butterworth (Q=0.7071) | 100% = máxima resonancia (Q=16)\nRango: 0 a 100% | Por defecto: 0%");
        if (key == "tonepos") return JUCE_UTF8("RLPF POSITION: posición del filtro RLPF\nPRE: antes del distorsionador | POST: después del distorsionador\nRango: PRE/POST | Por defecto: POST");
        if (key == "tilton") return JUCE_UTF8("TILT: activación del filtro tilt compensado de fase\nBalance tonal de ±6dB entre graves y agudos\nRango: OFF/ON | Por defecto: ON");
        if (key == "save") return JUCE_UTF8("SAVE: guarda el preset actual\nSobrescribe el preset seleccionado con valores actuales\nNo funciona con DEFAULT");
        if (key == "saveas") return JUCE_UTF8("SAVE AS: guarda como nuevo preset\nCrea un nuevo archivo de preset con los valores actuales\nPermite crear presets personalizados");
        if (key == "delete") return JUCE_UTF8("BORRAR: elimina el preset seleccionado\nRequiere confirmación antes de borrar");
        if (key == "back") return JUCE_UTF8("ANTERIOR: selecciona el preset previo\nNavega hacia atrás en la lista de presets");
        if (key == "next") return JUCE_UTF8("SIGUIENTE: selecciona el próximo preset\nNavega hacia adelante en la lista de presets");
        if (key == "undo") return JUCE_UTF8("DESHACER: revierte el último cambio\nDeshace modificación realizada manualmente por el usuario\nHistorial: hasta 20 pasos");
        if (key == "redo") return JUCE_UTF8("REHACER: aplica el cambio deshecho\nRehace modificación manual previamente revertida\nHistorial: hasta 20 pasos");
        if (key == "resetgui") return JUCE_UTF8("SIZE: cicla entre tamaños de ventana\nActual → Máximo → Mínimo → Actual\nAjuste rápido del tamaño del plugin");
        if (key == "bypass") return JUCE_UTF8("BYPASS: desactiva el procesamiento del plugin\nParámetro global, no automatizable. Transición suave\nRango: OFF/ON | Por defecto: OFF");
        if (key == "graphics") return JUCE_UTF8("GRAPHICS: alterna entre FFT y curvas de distorsión\nFFT: analizador de espectro | curves: visualizador de curvas\nClick para cambiar entre modos");
        if (key == "zoom") return JUCE_UTF8("ZOOM: cicla entre vista normal y ampliada del FFT\nNormal: -80 a 0dB | x2: -48 a 0dB\nSolo activo en modo FFT");
        if (key == "diagram") return JUCE_UTF8("DIAGRAM: muestra diagrama de bloques del procesador\nDespliega menú con código GenExpr por bloque para copiar");
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
        if (key == "spectrum") return JUCE_UTF8("ANALIZADOR FFT: visualización del espectro de frecuencias\nMuestra análisis en tiempo real de 20Hz a 20kHz\nUsar botón ZOOM para cambiar escala");
        if (key == "curves") return JUCE_UTF8("CURVAS DE DISTORSIÓN: visualización de función de transferencia\nMuestra cómo el algoritmo seleccionado transforma la señal\nTILT colorea el fondo según balance tonal");
    }
    else
    {
        // English tooltips
        if (key == "title") return "JCBDistortion: multimodal distortion v1.0.0-alpha.1\nOpen source audio plugin\nClick for credits";
        if (key == "drywet") return "DRY/WET: mix between original and processed signal\nControls final output balance\nRange: 0 to 100% | Default: 100%";
        if (key == "lookahead") return "LOOKAHEAD: anticipation to prevent distortion\nPrevents overshooting on fast transients\nRange: 0 to 5 ms | Default: 0 ms";
        if (key == "drive") return "DRIVE: distortion intensity\nControls gain before saturation\nRange: 1 to 50 | Default: 1";
        if (key == "tilt") return "TILT: tonal balance filter\nControls bass/treble balance\nRange: -6 to +6 dB | Default: 0 dB";
        if (key == "ceiling") return "CEILING: maximum output level\nControls the maximizer's limiting ceiling\nRange: -60 to 0 dB | Default: -0.3 dB";
        if (key == "bitcrusher") return "BIT CRUSHER: enables digital quantization\nReduces bit resolution for digital distortion\nRange: OFF/ON | Default: OFF";
        if (key == "bits") return "BITS: bit crusher resolution\nControls digital bit quantization\nRange: 3 to 16 bits | Default: 16 bits";
        if (key == "even") return "EVEN: DC asymmetry for even harmonics\nAdds DC component to generate even harmonics\nRange: 0 to 1 | Default: 0";
        if (key == "downsample") return "DECI: decimation factor\nReduces sample rate for aliasing distortion\nRange: 0 to 100% | Default: 0%";
        if (key == "downsampleon") return "DOWNSAMPLE: enables decimation\nActivates sample rate reduction effect\nRange: OFF/ON | Default: OFF";
        if (key == "tiltpos") return "TILT POSITION: tilt filter position\nPRE: before distortion | POST: after distortion\nRange: PRE/POST | Default: PRE";
        if (key == "mode") return "MODE: distortion algorithm\n8 different types: Soft Clip, Sigmoid, Rectifier, etc.\nRange: 1 to 8 (displayed) | Default: 1";
        if (key == "diston") return "DIST: enables/disables distortion block\nON: distortion active | OFF: distortion bypassed\nRange: ON/OFF | Default: ON";
        if (key == "trim") return "TRIM: distortion input gain\nAdjusts level before processing\nRange: -12 to +12 dB | Default: 0 dB";
        if (key == "makeup") return "MAKEUP: WET chain output gain\nAdjusts only the processed signal level (doesn't affect dry/wet)\nRange: -24 to +12 dB | Default: 0 dB";
        if (key == "sc") return "FILTERS: activates the 3-band crossover.\nSplits signal into Low/Mid/High for selective processing.\nDefault: OFF";
        //if (key == "solosc") return "SOLO SC: listen to int/ext sidechain filters\nGlobal parameter, non-automatable\nRange: OFF/ON | Default: OFF";
        if (key == "hpf") return "XLow: crossover low frequency point\nDefines the separation frequency between Low and Mid bands\nRange: 20 to 1000 Hz | Default: 250 Hz";
        if (key == "band") return "BAND: crossover band selector\nChoose which frequency band to process (Low/Mid/High)\nRange: Low-Mid-High (interpolatable) | Default: Mid";
        if (key == "lpf") return "XHigh: crossover high frequency point\nDefines the separation frequency between Mid and High bands\nRange: 1000 Hz to 20 kHz | Default: 5 kHz";
        if (key == "save") return "SAVE: save or overwrite preset\nSave new or update current preset";
        if (key == "saveas") return "SAVE AS: save as new preset.\nCreates new preset file with current values.\nAllows creating custom presets";
        if (key == "delete") return "DELETE: remove selected preset\nRequires confirmation before deleting";
        if (key == "back") return "PREVIOUS: select previous preset\nNavigate backwards through preset list";
        if (key == "next") return "NEXT: select next preset\nNavigate forward through preset list";
        if (key == "undo") return "UNDO: revert last change\nUndo modification made manually by the user\nHistory: up to 20 steps";
        if (key == "redo") return "REDO: reapply undone change\nRedo manually made modification previously reverted\nHistory: up to 20 steps";
        if (key == "resetgui") return JUCE_UTF8("SIZE: cycles through window sizes\nCurrent → Maximum → Minimum → Current\nQuick plugin size adjustment");
        if (key == "bypass") return "BYPASS: disables plugin processing\nGlobal parameter, non-automatable. Smooth transition\nRange: OFF/ON | Default: OFF";
        if (key == "graphics") return "GRAPHICS: toggles between FFT and distortion curves\nFFT: spectrum analyzer | curves: curve visualizer\nClick to switch between modes";
        if (key == "zoom") return "ZOOM: cycles between normal and zoomed FFT view\nNormal: -80 to 0dB | x2: -48 to 0dB\nOnly active in FFT mode";
        if (key == "diagram") return "DIAGRAM: shows processor block diagram\nDisplays menu with GenExpr code per block for copying";
        if (key == "tooltiptoggle") return "TOOLTIP: show/hide help tooltips.\nEnables or disables popup help windows.";
        if (key == "tooltiplang") return "LANGUAGE: switch between Spanish and English.\nToggles tooltip language.";
        if (key == "link") return "STEREO LINKED: always active.\nPlugin only works in stereo linked mode.\nBoth channels are always linked";
        if (key == "hq") return "TODO: Enables oversampling for higher quality.";
        if (key == "dualmono") return "TODO: Processes L/R channels independently.";
        if (key == "ms") return "TODO: Processes in M/S format.";
        if (key == "abstate") return "Switches between two A/B configurations to compare settings.";
        if (key == "midilearn") return "TODO: Assigns MIDI control.";
        if (key == "abcopyatob") return "Copy A to B";
        if (key == "abcopybtoa") return "Copy B to A";
        if (key == "spectrum") return "FFT ANALYZER: frequency spectrum visualization\nShows real-time analysis from 20Hz to 20kHz\nUse ZOOM button to change scale";
        if (key == "curves") return "DISTORTION CURVES: transfer function visualization\nShows how the selected algorithm transforms the signal\nTILT colors background based on tonal balance";
        if (key == "bandsolo") return "SOLO BAND: solos the active filter band\nAllows listening only to the selected band (Low/Mid/High) through the processing chain\nRange: OFF/ON | Default: OFF";
        if (key == "safelimit") return "LIM: protection brickwall limiter\nLimiter set to -0.1 dBFS to prevent overmodulation at plugin output (post dry/wet)\nRange: OFF/ON | Default: OFF";
        if (key == "tonelpf") return "RLPF: resonant low-pass filter for tone\nCan be used PRE/POST distortion, phase compensated\nRange: OFF/ON | Default: OFF";
        if (key == "tonefreq") return "RLPF: resonant low-pass filter (2nd order RBJ)\nAdjustable cutoff frequency for tonal control\nRange: 20 Hz to 20 kHz | Default: 15 kHz";
        if (key == "toneq") return "Q: RLPF filter resonance\n0% = Butterworth (Q=0.7071) | 100% = maximum resonance (Q=16)\nRange: 0 to 100% | Default: 0%";
        if (key == "tonepos") return "RLPF POSITION: RLPF filter position\nPRE: before distortion | POST: after distortion\nRange: PRE/POST | Default: POST";
        if (key == "tilton") return "TILT: phase-compensated tilt filter activation\n±6dB tonal balance between bass and treble\nRange: OFF/ON | Default: ON";
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
    if (codeContentCacheInitialized) return;
    
    // Pre-cargar todo el contenido de código al inicializar para thread safety
    struct CodeMapping {
        juce::String blockName;
        const char* binaryData;
        int dataSize;
    };
    
    // Lista de todos los mappings - DISTORTION (archivos Gen~ disponibles)
    std::vector<CodeMapping> mappings = {
        {"INPUT STAGE", BinaryData::InputStage_txt, BinaryData::InputStage_txtSize},
        {"EFFECTS CHAIN", BinaryData::EffectsChain_txt, BinaryData::EffectsChain_txtSize},
        {"DISTORTION CORE", BinaryData::DistortionCore_txt, BinaryData::DistortionCore_txtSize},
        //{"GEN EXPR", BinaryData::GenExpr_txt, BinaryData::GenExpr_txtSize},
        //{"GEN EXPR (FILTERS)", BinaryData::GenExpr_with_filters_txt, BinaryData::GenExpr_with_filters_txtSize},
        {"OUTPUT STAGE", BinaryData::OutputStage_txt, BinaryData::OutputStage_txtSize},
        // Bloques de filtros LR4 (Linkwitz-Riley 4th order) - ambos apuntan al CrossoverStage completo
        {"LR4", BinaryData::CrossoverStage_txt, BinaryData::CrossoverStage_txtSize},
        {"LR4-DRY-AllpassCompensated", BinaryData::CrossoverStage_txt, BinaryData::CrossoverStage_txtSize},
    };
    
    // Cargar todo en cache
    for (const auto& mapping : mappings) {
        if (mapping.binaryData != nullptr && mapping.dataSize > 0) {
            juce::String content = juce::String::createStringFromData(mapping.binaryData, mapping.dataSize);
            if (content.isNotEmpty()) {
                codeContentCache[mapping.blockName] = content;
            } else {
                // Fallback si falla la carga
                codeContentCache[mapping.blockName] = "// Code for " + mapping.blockName + 
                    "\n\n// Error cargando contenido\n\n// Funcionalidad básica:\n" + 
                    getBasicBlockDescription(mapping.blockName);
            }
        }
    }
    
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
    // Mapear componentes UI a sus IDs de parámetro (robusta, compatible con el futuro)
    // Retornar -1 para componentes que no representan parámetros automatizables
    
    juce::String parameterID;
    
    // COMENTADO: Referencias a controles inexistentes en getParameterIndexFromControl
    /*
    // Perillas Superiores Izquierdas (threshold, ratio, knee)
    if (&control == &leftBottomKnobs.drywetSlider) parameterID = "a_DRYWET";
    else if (&control == &leftTopKnobs.ceilingSlider) parameterID = "e_CEILING";  // NUEVO - ceiling slider
    */
    // MAXIMIZER: c_RATIO no existe - comentado según CONTEXTO.txt
    // else if (&control == &leftTopKnobs.ratioSlider) parameterID = "c_RATIO";
    // MAXIMIZER: q_KNEE no existe - comentado según CONTEXTO.txt
    // else if (&control == &leftTopKnobs.kneeSlider) parameterID = "q_KNEE";
    
    // DISTORTION: n_LOOKAHEAD eliminado - no existe en distorsionador
    // else if (&control == &rightTopControls.lookaheadSlider) parameterID = "n_LOOKAHEAD";
    
    // Controles Superiores Derechos (range, react, smooth)
    // MAXIMIZER: h_RANGE no existe - comentado según CONTEXTO.txt
    // else if (&control == &rightTopControls.rangeSlider) parameterID = "h_RANGE";
    // MAXIMIZER: g_REACT no existe - comentado según CONTEXTO.txt
    // else if (&control == &rightTopControls.reactSlider) parameterID = "g_REACT";
    // MAXIMIZER: z_SMOOTH no existe - comentado según CONTEXTO.txt
    // else if (&control == &rightTopControls.smoothSlider) parameterID = "z_SMOOTH";
    // COMENTADO: Más referencias en getParameterIndexFromControl
    /*
    else if (&control == &rightTopControls.tiltSlider) parameterID = "i_TILT";  // NUEVO - tilt EQ slider
    else if (&control == &rightTopControls.bitsSlider) parameterID = "g_BITS";  // NUEVO - bit crusher resolution
    
    // Perillas Inferiores Derechas (attack, release, hold)
    else if (&control == &rightBottomKnobs.driveSlider) parameterID = "b_DRIVE";
    else if (&control == &rightBottomKnobs.modeSlider) parameterID = "d_MODE";
    // else if (&control == &rightBottomKnobs.holdSlider) parameterID = "f_HOLD";
    
    // Controles de filtro de entrada
    else if (&control == &sidechainControls.xLowSlider) parameterID = "j_HPF";
    else if (&control == &sidechainControls.bandSlider) parameterID = "o_BAND";
    else if (&control == &sidechainControls.xHighSlider) parameterID = "k_LPF";
    // else if (&control == &sidechainControls.keyButton) parameterID = "r_KEY";
    
    // Sliders de Trim
    else if (&control == &trimSlider) parameterID = "k_INPUT";
    else if (&control == &makeupSlider) parameterID = "l_OUTPUT";
    // else if (&control == &scTrimSlider) parameterID = "y_SCTRIM";
    
    // Botones Automatizables
    else if (&control == &sidechainControls.scButton) parameterID = "l_SC";
    
    // Parámetros no automatizables (retornar -1)
    // Estos son parámetros globales/utility que no deberían mostrar carriles de automatización
    // else if (&control == &sidechainControls.soloScButton) return -1;  // m_SOLOSC (no automatizable)
    else if (&control == &rightBottomKnobs.bitButton) return -1;      // g_DITHER (no automatizable)
    else if (&control == &rightBottomKnobs.dcSlider) parameterID = "c_DC";  // c_DC (continuo 0-1)
    */
    // else if (&control == &parameterButtons.bypassButton) return -1;     // h_BYPASS (no automatizable)
    
    // Obtener índice dinámico de parámetro
    if (parameterID.isNotEmpty()) {
        return getParameterIndexByID(parameterID);
    }
    
    // Cualquier otro componente que no representa un parámetro
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
    // El Maximizer tiene AUTOREL como botón toggle separado
}


//==============================================================================
// SPECTRUM ANALYZER SUPPORT
//==============================================================================

void JCBReverbAudioProcessorEditor::toggleDisplayMode()
{
    // Para JCBReverb, solo tenemos modo FFT disponible
    // TODO: Implementar visualización específica para reverb cuando sea necesario
    
    // Mantener siempre el modo FFT activo
    // currentDisplayMode = DisplayMode::FFT; // COMENTADO: DisplayMode eliminado
    processor.displayModeIsFFT = true;
    
    // Configurar visualización FFT
    // spectrumAnalyzer.setVisible(true);
    utilityButtons.runGraphicsButton.setButtonText("FFT");
    utilityButtons.runGraphicsButton.setColour(juce::TextButton::buttonColourId, 
                                              juce::Colours::transparentBlack);
    
    // Habilitar botón zoom para modo FFT
    utilityButtons.zoomButton.setAlpha(1.0f);
    utilityButtons.zoomButton.setEnabled(true);
    
    handleParameterChange();
    repaint();
}
