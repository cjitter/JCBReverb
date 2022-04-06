#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JCBReverbAudioProcessor::JCBReverbAudioProcessor() : apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
, m_CurrentBufferSize(0)
{
    // use a default samplerate and vector size here, reset it later
    m_JCPluginState = (CommonState *)JC_GENPLUGIN::create(44100, 64);
    JC_GENPLUGIN::reset(m_JCPluginState);
    
    m_InputBuffers = new t_sample *[JC_GENPLUGIN::num_inputs()];
    m_OutputBuffers = new t_sample *[JC_GENPLUGIN::num_outputs()];
    
    for (int i = 0; i < JC_GENPLUGIN::num_inputs(); i++) {
        m_InputBuffers[i] = NULL;
    }
    for (int i = 0; i < JC_GENPLUGIN::num_outputs(); i++) {
        m_OutputBuffers[i] = NULL;
    }
    
    // MUY IMPORTNTE: vincular parámetros de gen~ con el APVTS
    for (int i = 0; i < JC_GENPLUGIN::num_params(); i++)
    {
        auto name = juce::String (JC_GENPLUGIN::getparametername (m_JCPluginState, i));
        apvts.addParameterListener (name, this);
    }
    
}

JCBReverbAudioProcessor::~JCBReverbAudioProcessor()
{
    JC_GENPLUGIN::destroy(m_JCPluginState);
    
    // destruir parámetros del apvts
    for (int i = 0; i < JC_GENPLUGIN::num_params(); i++)
    {
    auto name = juce::String (JC_GENPLUGIN::getparametername(m_JCPluginState, i));
    apvts.removeParameterListener(name, this);
    }
    
}

//==============================================================================
const String JCBReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int JCBReverbAudioProcessor::getNumParameters()
{
    return JC_GENPLUGIN::num_params();
}

////////////////////////////////

float JCBReverbAudioProcessor::getParameter (int index)
{
    t_param value;
    t_param min = JC_GENPLUGIN::getparametermin(m_JCPluginState, index);
    t_param range = fabs(JC_GENPLUGIN::getparametermax(m_JCPluginState, index) - min);
    
    JC_GENPLUGIN::getparameter(m_JCPluginState, index, &value);
    
    value = (value - min) / range;
    
    return value;
}

void JCBReverbAudioProcessor::setParameter (int index, float newValue)
{
    t_param min = JC_GENPLUGIN::getparametermin(m_JCPluginState, index);
    t_param range = fabs(JC_GENPLUGIN::getparametermax(m_JCPluginState, index) - min);
    t_param value = newValue * range + min;

    JC_GENPLUGIN::setparameter(m_JCPluginState, index, value, NULL);
}

////////////////////////////////

const String JCBReverbAudioProcessor::getParameterName (int index)
{
    return String(JC_GENPLUGIN::getparametername(m_JCPluginState, index));
}

const String JCBReverbAudioProcessor::getParameterText (int index)
{
    String text = String(getParameter(index));
    text += String(" ");
    text += String(JC_GENPLUGIN::getparameterunits(m_JCPluginState, index));
    
    return text;
}

const String JCBReverbAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String JCBReverbAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool JCBReverbAudioProcessor::isInputChannelStereoPair (int index) const
{
    return JC_GENPLUGIN::num_inputs() == 2;
}

bool JCBReverbAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return JC_GENPLUGIN::num_outputs() == 2;
}

bool JCBReverbAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool JCBReverbAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool JCBReverbAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double JCBReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JCBReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int JCBReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JCBReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String JCBReverbAudioProcessor::getProgramName (int index)
{
    return String();
}

void JCBReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JCBReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // initialize samplerate and vectorsize with the correct values
    m_JCPluginState->sr = sampleRate;
    m_JCPluginState->vs = samplesPerBlock;
    
    assureBufferSize(samplesPerBlock);
}

void JCBReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void JCBReverbAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
//        buffer.clear (i, 0, buffer.getNumSamples());

    assureBufferSize(buffer.getNumSamples());
    
    // fill input buffers
    for (int i = 0; i < JC_GENPLUGIN::num_inputs(); i++) {
        if (i < getTotalNumInputChannels()) {
            for (int j = 0; j < m_CurrentBufferSize; j++) {
                m_InputBuffers[i][j] = buffer.getReadPointer(i)[j];
            }
        } else {
            memset(m_InputBuffers[i], 0, m_CurrentBufferSize *  sizeof(double));
        }
    }
    
    // process audio
    JC_GENPLUGIN::perform(m_JCPluginState,
                           m_InputBuffers,
                           JC_GENPLUGIN::num_inputs(),
                           m_OutputBuffers,
                           JC_GENPLUGIN::num_outputs(),
                           buffer.getNumSamples());
    
    // fill output buffers
    for (int i = 0; i < getTotalNumOutputChannels(); i++) {
        if (i < JC_GENPLUGIN::num_outputs()) {
            for (int j = 0; j < buffer.getNumSamples(); j++) {
                buffer.getWritePointer(i)[j] = m_OutputBuffers[i][j];
            }
        } else {
            buffer.clear (i, 0, buffer.getNumSamples());
        }
    }
}

//==============================================================================
bool JCBReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to true if you choose to supply an editor)
}

AudioProcessorEditor* JCBReverbAudioProcessor::createEditor()
{
    return new JCBReverbAudioProcessorEditor (*this);
    //return new GenericAudioProcessorEditor (*this);
}

//==============================================================================
void JCBReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
//    auto editor = apvts.state.getOrCreateChildWithName ("editor", nullptr);
//    editor.setProperty ("size-x", editorSize.x, nullptr);
//    editor.setProperty ("size-y", editorSize.y, nullptr);
    
    juce::MemoryOutputStream miMemoria (destData, true);
    apvts.state.writeToStream (miMemoria);
}

void JCBReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
 
    auto tree = juce::ValueTree::readFromData (data, sizeInBytes);
    if (tree.isValid()) {
        apvts.state = tree;
        
//        auto editor = apvts.state.getChildWithName ("editor");
//        if (editor.isValid())
//        {
//            editorSize.setX (editor.getProperty ("size-x", 700));
//            editorSize.setY (editor.getProperty ("size-y", 200));
//            if (auto* activeEditor = getActiveEditor())
//                activeEditor->setSize (editorSize.x, editorSize.y);
//        }
        
    }
}

Point<int> JCBReverbAudioProcessor::getSavedSize() const
{
    return editorSize;
}

void JCBReverbAudioProcessor::setSavedSize (const Point<int>& size)
{
    editorSize = size;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JCBReverbAudioProcessor();
}

//==============================================================================
// C74 added methods

void JCBReverbAudioProcessor::assureBufferSize(long bufferSize)
{
    if (bufferSize > m_CurrentBufferSize) {
        for (int i = 0; i < JC_GENPLUGIN::num_inputs(); i++) {
            if (m_InputBuffers[i]) delete m_InputBuffers[i];
            m_InputBuffers[i] = new t_sample[bufferSize];
        }
        for (int i = 0; i < JC_GENPLUGIN::num_outputs(); i++) {
            if (m_OutputBuffers[i]) delete m_OutputBuffers[i];
            m_OutputBuffers[i] = new t_sample[bufferSize];
        }
        
        m_CurrentBufferSize = bufferSize;
    }
}

//==============================================================================
// Implementación  para APVTS: createParameterLayout y parameterChanged

juce::AudioProcessorValueTreeState::ParameterLayout JCBReverbAudioProcessor::createParameterLayout()
{
    const int versionHint = 24;

    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    
    auto input = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("a_input", versionHint),//AU Logic
                                                             juce::CharPointer_UTF8("Entrada"),
                                                             NormalisableRange<float>(0.f,
                                                                                      1.0f,
                                                                                      0.01,
                                                                                      1.f),
                                                             1.0f);
    
    auto drywet = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("b_drywet", versionHint),
                                                              juce::CharPointer_UTF8("Dry Wet"),
                                                              NormalisableRange<float>(0.f,
                                                                                       1.0f,
                                                                                       0.01,
                                                                                       1.f),
                                                              0.33f);
    
    auto reflect = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("c_reflect", versionHint),
                                                            juce::CharPointer_UTF8("Reflex"),
                                                            NormalisableRange<float>(0.f,
                                                                                     1.0f,
                                                                                     0.01,
                                                                                     4.75f),
                                                            0.86f);
    

    auto damp = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("d_damp", versionHint),
                                                            juce::CharPointer_UTF8("Damp"),
                                                            NormalisableRange<float>(0.f,
                                                                                     1.0f,
                                                                                     0.01,
                                                                                     1.f),
                                                            0.8f);

    auto size = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("e_size", versionHint),
                                                                 juce::CharPointer_UTF8("Dimensión"),
                                                                 NormalisableRange<float>(0.5f,
                                                                                          2.f,
                                                                                          0.25f,
                                                                                          1.f),
                                                                 1.f);

    
    auto st = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("f_st", versionHint),
                                                              juce::CharPointer_UTF8("Estéreo"),
                                                              NormalisableRange<float>(0.f,
                                                                                       1.0f,
                                                                                       0.01,
                                                                                       1.f),
                                                              0.5f);

    
    auto freeze = std::make_unique<juce::AudioParameterInt>(juce::ParameterID("g_freeze", versionHint),
                                                              juce::CharPointer_UTF8("Congelar"),
                                                              0,
                                                              1,
                                                              0);
    
    // EQ
    
    auto eq_lowgain = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("h_lowGain", versionHint),
                                                              juce::CharPointer_UTF8("Gain low"),
                                                              NormalisableRange<float>(-30.f,
                                                                                        30.f,
                                                                                        0.1f,
                                                                                        1.f),
                                                              0.f);
    
    auto eq_peakgain = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("i_peakGain", versionHint),
                                                              juce::CharPointer_UTF8("Gain mid"),
                                                              NormalisableRange<float>(-30.f,
                                                                                        30.f,
                                                                                        0.1f,
                                                                                        1.f),
                                                              0.f);
    
    auto eq_higain = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("j_hiGain", versionHint),
                                                              juce::CharPointer_UTF8("Gain high"),
                                                              NormalisableRange<float>(-30.f,
                                                                                        30.f,
                                                                                        0.1f,
                                                                                        1.f),
                                                              0.f);
    
    // HPF y LPF
    
    auto lpf = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("k_lpf", versionHint),
                                                              juce::CharPointer_UTF8("Freq LPF"),
                                                              NormalisableRange<float>(100.f,
                                                                                       20000.f,
                                                                                       1.f,
                                                                                       0.5f),
                                                              20000.f);
    
    auto hpf = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("l_hpf", versionHint),
                                                              juce::CharPointer_UTF8("Freq HPF"),
                                                              NormalisableRange<float>(20.f,
                                                                                       5000.f,
                                                                                       1.f,
                                                                                       0.5f),
                                                              20.f);
    
    // OUTPUT
    
    auto outputs = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("m_output", versionHint),
                                                              juce::CharPointer_UTF8("Salida"),
                                                              NormalisableRange<float>(0.f,
                                                                                       1.f,
                                                                                       0.01f,
                                                                                       1.f),
                                                              1.f);
    
    // FREQ EQ
    
    auto eq_lowfreq = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("n_lowFreq", versionHint),
                                                              juce::CharPointer_UTF8("Freq Low"),
                                                              NormalisableRange<float>(20.f,
                                                                                       800.f,
                                                                                       1.f,
                                                                                       0.25f),
                                                              500.f);

    
    auto eq_peakfreq = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("o_peakFreq", versionHint),
                                                              juce::CharPointer_UTF8("Freq Mid"),
                                                              NormalisableRange<float>(100.f,
                                                                                       2500.f,
                                                                                       1.f,
                                                                                       0.25f),
                                                              800.f);
    
    auto eq_hifreq = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("p_hiFreq", versionHint),
                                                              juce::CharPointer_UTF8("Freq High"),
                                                              NormalisableRange<float>(800.f,
                                                                                       15000.f,
                                                                                       1.f,
                                                                                       0.25f),
                                                              2000.f);
    
    auto eq_onoff = std::make_unique<juce::AudioParameterInt>(juce::ParameterID("q_onoffEQ", versionHint),
                                                              juce::CharPointer_UTF8("On/Off EQ"),
                                                              0,
                                                              1,
                                                              0);
    
    // COMP
    
    auto comp_onoff = std::make_unique<juce::AudioParameterInt>(juce::ParameterID("r_onoffCOMP", versionHint),
                                                              juce::CharPointer_UTF8("COMP on/off"),
                                                              0,
                                                              1,
                                                              0);
    
    auto comp_thd = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("s_thd", versionHint),
                                                              juce::CharPointer_UTF8("COMP THD"),
                                                              NormalisableRange<float>(-50.f,
                                                                                       0.f,
                                                                                       1.f,
                                                                                       1.f),
                                                              -12.f);
    
    auto comp_ratio = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("t_ratio", versionHint),
                                                              juce::CharPointer_UTF8("COMP Ratio"),
                                                              NormalisableRange<float>(1.f,
                                                                                       10.f,
                                                                                       1.f,
                                                                                       1.f),
                                                              2.f);
    
    auto comp_atk = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("u_atk", versionHint),
                                                              juce::CharPointer_UTF8("COMP Ataque"),
                                                              NormalisableRange<float>(10.f,
                                                                                       150.f,
                                                                                       1.f,
                                                                                       1.f),
                                                              15.f);
    
    auto comp_rel = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("v_rel", versionHint),
                                                              juce::CharPointer_UTF8("COMP Release"),
                                                              NormalisableRange<float>(15.f,
                                                                                       500.f,
                                                                                       1.f,
                                                                                       1.f),
                                                              25.f);
    
    auto comp_makeup = std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("w_makeup", versionHint),
                                                              juce::CharPointer_UTF8("COMP Makeup"),
                                                              NormalisableRange<float>(-6.f,
                                                                                       6.f,
                                                                                       1.f,
                                                                                       1.f),
                                                              0.f);
    
    
    
    params.push_back(std::move(input));
    params.push_back(std::move(drywet));
    params.push_back(std::move(reflect));
    params.push_back(std::move(damp));
    params.push_back(std::move(size));
    params.push_back(std::move(st));
    params.push_back(std::move(freeze));
    
    params.push_back(std::move(eq_lowgain));
    params.push_back(std::move(eq_peakgain));
    params.push_back(std::move(eq_higain));

    params.push_back(std::move(lpf));
    params.push_back(std::move(hpf));
    
    params.push_back(std::move(outputs));

    params.push_back(std::move(eq_lowfreq));
    params.push_back(std::move(eq_peakfreq));
    params.push_back(std::move(eq_hifreq));
    params.push_back(std::move(eq_onoff));

        
    params.push_back(std::move(comp_onoff));
    params.push_back(std::move(comp_thd));
    params.push_back(std::move(comp_ratio));
    params.push_back(std::move(comp_atk));
    params.push_back(std::move(comp_rel));
    
    params.push_back(std::move(comp_makeup));

    
//    params.push_back(std::move(lowgain));
//    params.push_back(std::move(peakgain));
//    params.push_back(std::move(higain));
//
//    params.push_back(std::move(lowpassfreq));
//    params.push_back(std::move(highpassfreq));
//
//    params.push_back(std::move(outputs));
//
//    params.push_back(std::move(lowfreq));
//    params.push_back(std::move(peakfreq));
//    params.push_back(std::move(hifreq));
//    params.push_back(std::move(eqonoff));
//
//    params.push_back(std::move(componoff));
//    params.push_back(std::move(comp_thd));
//    params.push_back(std::move(comp_ratio));
//    params.push_back(std::move(comp_atk));
//    params.push_back(std::move(comp_rel));

    
    return { params.begin(), params.end() };
}

void JCBReverbAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    auto index = apvts.getParameter(parameterID)->getParameterIndex();
    JC_GENPLUGIN::setparameter(m_JCPluginState, index, newValue, nullptr);
}
