#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class JCBReverbAudioProcessorEditor : public AudioProcessorEditor
{
public:
    JCBReverbAudioProcessorEditor (JCBReverbAudioProcessor&);
    ~JCBReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    // Declarar variables
    int const ancho {700};
    int const alto  {200};
    
    // Textos de parámetros
    juce::DrawableText txtEntrada;
    juce::DrawableText txtDryWet;
    juce::DrawableText txtTamano;
    juce::DrawableText txtFiltro;
    juce::DrawableText txtDifusion;
    juce::DrawableText txtEstereo;
    juce::DrawableText txtCongelar;
    juce::DrawableText txtTitulo;

    // Imagen de fondo como componente
    juce::ImageComponent mFondo;

    // Sliders y botones GUI
    juce::Slider inputSlider;
    juce::Slider drywetSlider;
    juce::Slider sizeSlider;
    juce::Slider dampSlider;
    juce::Slider diffusionSlider;
    juce::Slider spreadSlider;
    juce::Slider freezeButton;
    
    juce::Slider thdSlider;
    juce::Slider ratioSlider;
    juce::Slider atkSlider;
    juce::Slider relSlider;
    juce::Slider makeupSlider;
    juce::Slider onCompSlider;
    
    juce::Slider lowFreqSlider;
    juce::Slider lowGainSlider;
    juce::Slider peakFreqSlider;
    juce::Slider peakGainSlider;
    juce::Slider hiFreqSlider;
    juce::Slider lpfSlider;
    juce::Slider hpfSlider;
    juce::Slider hiGainSlider;
    juce::Slider onEqSlider;

    // Declarar punteros para sliders y botons Attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drywetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> diffusionSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> spreadSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeButtonAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thdSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> atkSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> relSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> makeupSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> onCompSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hiFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lpfSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hpfSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hiGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> onEqSliderAttachment;

    
    
    
    

    JCBReverbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JCBReverbAudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED
