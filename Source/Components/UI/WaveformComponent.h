#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

//==============================================================================
/**
 * Componente de visualización de forma de onda para reverb
 * Muestra la señal seca (input) y la señal con reverb (output) superpuestas
 */
class WaveformComponent : public juce::Component,
                         private juce::Timer
{
public:
    WaveformComponent();
    ~WaveformComponent() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    //==============================================================================
    // Actualizar datos de forma de onda
    void updateWaveformData(const std::vector<float>& inputSamples, 
                           const std::vector<float>& processedSamples);
    
    // Control de zoom vertical
    void setZoomEnabled(bool shouldZoom);
    bool getZoomEnabled() const noexcept { return zoomEnabled; }
    
    // Establecer el nivel de dry/wet para ajustar visualización
    void setDryWetMix(float mix) { dryWetMix = juce::jlimit(0.0f, 1.0f, mix); }
    
    // Establecer el tamaño de reverb para controlar el fade
    void setReverbSize(float size) { reverbSize = juce::jlimit(0.0f, 1.0f, size); }
    
    // Establecer la cantidad de reflexiones para controlar intensidad del fade
    void setReflectAmount(float amount) { reflectAmount = juce::jlimit(0.0f, 1.0f, amount); }

private:
    void timerCallback() override;
    
    //==============================================================================
    // Buffers para historia de niveles RMS
    static constexpr int levelHistorySize = 120;  // Puntos de historia de niveles
    std::vector<float> inputLevels;              // Historia de niveles de entrada
    std::vector<float> outputLevels;             // Historia de niveles de salida  
    int writePos = 0;                             // Posición de escritura
    
    // Niveles actuales suavizados
    float currentInputLevel = 0.0f;
    float currentOutputLevel = 0.0f;
    float peakReverbLevel = 0.0f;  // Peak de diferencia para visualización
    
    // Mutex para thread safety
    std::mutex dataLock;
    
    // Estado de visualización
    bool zoomEnabled = false;
    float dryWetMix = 0.5f;
    float reverbSize = 0.5f;
    float reflectAmount = 0.5f;  // Para controlar intensidad del fade
    
    // Colores del tema
    struct Colours
    {
        inline static const juce::Colour background{0xFF1A1A1A};
        inline static const juce::Colour gridLines{0xFF303030};
        inline static const juce::Colour inputWaveform{0x60FFFFFF};  // Gris semi-transparente
        inline static const juce::Colour outputWaveform{0xFF9E35B0}; // Púrpura principal
        inline static const juce::Colour reverbTail{0x809E35B0};     // Púrpura semi-transparente
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformComponent)
};