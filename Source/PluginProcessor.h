#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <JuceHeader.h>
#include "JC_GENPLUGIN.h"

//==============================================================================
/**
*/
class JCBReverbAudioProcessor  : public AudioProcessor,
                                 public AudioProcessorValueTreeState::Listener // necesario para vincular parámetros
{
public:
    //==============================================================================
    JCBReverbAudioProcessor();
    ~JCBReverbAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Obojetos y declaración de métodos públicos de nuestra clase.
    //==============================================================================
    
    juce::AudioProcessorValueTreeState apvts; // necesita inicializarse en el constructor
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); // implementado al final del .cpp
    void parameterChanged (const String &parameterID, float newValue) override;  // implementado al final del .cpp

    // Para guardar tamaño ventana
    juce::Point<int> getSavedSize() const;
    void setSavedSize (const Point<int>& size);
    juce::Point<int> editorSize;
    
    //==============================================================================
    

protected:
	// c74: since Juce does float sample processing and Gen offers double sample
	// processing, we need to go through input and output buffers
	void assureBufferSize(long bufferSize);
	
private:
    
    //float rmsPreLevelLeft, rmsPreLevelRight, rmsPostLevelLeft, rmsPostLevelRight;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JCBReverbAudioProcessor)
	
	CommonState				*m_JCPluginState;
	
	long					m_CurrentBufferSize;
	t_sample				**m_InputBuffers;
	t_sample				**m_OutputBuffers;
    
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
