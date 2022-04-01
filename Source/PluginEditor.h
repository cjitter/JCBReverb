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

    // Declarar punteros para sliders y botons Attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drywetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> diffusionSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> spreadSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeButtonAttachment;

    JCBReverbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JCBReverbAudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED
