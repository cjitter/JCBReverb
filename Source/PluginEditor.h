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
    
    juce::TooltipWindow tooltipVentana;
    
    // Declarar variables
    int const ancho {700};
    int const alto  {200};
    
    // Textos de parámetros
    juce::DrawableText txtEntrada;
    juce::DrawableText txtDryWet;
    juce::DrawableText txtCongelar;
    juce::DrawableText txtReflex;
    juce::DrawableText txtDamp;
    juce::DrawableText txtDimension;
    juce::DrawableText txtEstereo;
    juce::DrawableText txtOutput;

    juce::DrawableText txtTitulo;

    juce::DrawableText labelThd;
    juce::DrawableText labelRatio;
    juce::DrawableText labelAtk;
    juce::DrawableText labelRel;
    juce::DrawableText labelMakeUp;
    juce::DrawableText labelOnComp;
    
    juce::DrawableText labelHPF;
    juce::DrawableText labelLPF;

    juce::DrawableText labelOnEQ;
    juce::DrawableText labelEQLowFreq;
    juce::DrawableText labelEQLowGain;
    juce::DrawableText labelEQMidFreq;
    juce::DrawableText labelEQMidGain;
    juce::DrawableText labelEQHighFreq;
    juce::DrawableText labelEQHighGain;
    
    juce::HyperlinkButton titleLink;

    // Imagen de fondo como componente
    juce::ImageComponent mFondo;

    // Sliders y botones GUI
    juce::Slider inputSlider;
    juce::Slider drywetSlider;
    juce::Slider reflexSlider;
    juce::Slider dampSlider;
    juce::Slider dimensionSlider;
    juce::Slider spreadSlider;
    juce::Slider freezeSlider;
    
    juce::Slider thdSlider;
    juce::Slider ratioSlider;
    juce::Slider atkSlider;
    juce::Slider relSlider;
    juce::Slider makeupSlider;
    juce::Slider onCompSlider;
    
    juce::Slider hpfSlider;
    juce::Slider lpfSlider;
    
    juce::Slider onEqSlider;
    juce::Slider lowFreqSlider;
    juce::Slider lowGainSlider;
    juce::Slider peakFreqSlider;
    juce::Slider peakGainSlider;
    juce::Slider hiFreqSlider;
    juce::Slider hiGainSlider;
    juce::Slider outputSlider;
    
    

    // Declarar punteros para sliders y botons Attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drywetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> reflexSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dimensionSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> spreadSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeSliderAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thdSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> atkSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> relSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> makeupSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> onCompSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hpfSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lpfSliderAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> onEqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hiFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hiGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputSliderAttachment;
    
    
    JCBReverbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JCBReverbAudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED
