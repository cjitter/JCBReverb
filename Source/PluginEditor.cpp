#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JCBReverbAudioProcessorEditor::JCBReverbAudioProcessorEditor (JCBReverbAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    
    auto backgroundImage = ImageCache::getFromMemory(BinaryData::morado_jpg,
                                                     BinaryData::morado_jpgSize);
    
    //if (!backgroundImage.isNull())
    mFondo.setImage(backgroundImage, RectanglePlacement::stretchToFit);
    //else
        //jassert(!backgroundImage.isNull());
    
    addAndMakeVisible(mFondo);
    
    // Creación de textos reajustables
    addAndMakeVisible(txtEntrada);
    txtEntrada.setColour(juce::Colours::whitesmoke);
    txtEntrada.setText("ENTRADA");
    
    addAndMakeVisible(txtDryWet);
    txtDryWet.setColour(juce::Colours::whitesmoke);
    txtDryWet.setText("DRY/WET");
    
    addAndMakeVisible(txtCongelar);
    txtCongelar.setColour(juce::Colours::whitesmoke);
    txtCongelar.setText(juce::CharPointer_UTF8("CONGELAR"));
    
    addAndMakeVisible(txtReflex);
    txtReflex.setColour(juce::Colours::whitesmoke);
    txtReflex.setText(juce::CharPointer_UTF8("REFLEX"));
    
    addAndMakeVisible(txtDamp);
    txtDamp.setColour(juce::Colours::whitesmoke);
    txtDamp.setText("DAMP");
    
    addAndMakeVisible(txtDimension);
    txtDimension.setColour(juce::Colours::whitesmoke);
    txtDimension.setText(juce::CharPointer_UTF8("DIMENSIÓN"));
    
    addAndMakeVisible(txtEstereo);
    txtEstereo.setColour(juce::Colours::whitesmoke);
    txtEstereo.setText(juce::CharPointer_UTF8("ESTÉREO"));
    
    addAndMakeVisible(txtOutput);
    txtOutput.setColour(juce::Colours::whitesmoke);
    txtOutput.setText(juce::CharPointer_UTF8("SALIDA"));
    
//    addAndMakeVisible(txtTitulo);
//    txtTitulo.setColour(juce::Colours::whitesmoke);
//    txtTitulo.setText(juce::CharPointer_UTF8("JCBReverbST 0.2.3"));
    
    addAndMakeVisible (titleLink);
    titleLink.setURL(juce::URL("https://github.com/cjitter"));
    titleLink.setColour (juce::HyperlinkButton::textColourId, juce::Colours::azure);
    titleLink.changeWidthToFitText();
    titleLink.setFont(juce::Font(10.f), true);
    titleLink.setTooltip (TRANS("https://github.com/cjitter"));
    titleLink.setButtonText (TRANS("JCBReverbST 0.2.4"));
    
    // Labels COMP Y EQ
    addAndMakeVisible(labelThd);
    labelThd.setColour(juce::Colours::white);
    labelThd.setText(juce::CharPointer_UTF8("THD"));
    
    addAndMakeVisible(labelRatio);
    labelRatio.setColour(juce::Colours::white);
    labelRatio.setText(juce::CharPointer_UTF8("RAT"));
    
    addAndMakeVisible(labelAtk);
    labelAtk.setColour(juce::Colours::white);
    labelAtk.setText(juce::CharPointer_UTF8("ATK"));
    
    addAndMakeVisible(labelRel);
    labelRel.setColour(juce::Colours::white);
    labelRel.setText(juce::CharPointer_UTF8("REL"));
    
    addAndMakeVisible(labelMakeUp);
    labelMakeUp.setColour(juce::Colours::white);
    labelMakeUp.setText(juce::CharPointer_UTF8("MAKE UP"));
    
    addAndMakeVisible(labelOnComp);
    labelOnComp.setColour(juce::Colours::white);
    labelOnComp.setText(juce::CharPointer_UTF8("ON COMP"));
    
    //
    addAndMakeVisible(labelHPF);
    labelHPF.setColour(juce::Colours::white);
    labelHPF.setText(juce::CharPointer_UTF8("HPF"));
    
    addAndMakeVisible(labelLPF);
    labelLPF.setColour(juce::Colours::white);
    labelLPF.setText(juce::CharPointer_UTF8("LPF"));
    //
    
    addAndMakeVisible(labelOnEQ);
    labelOnEQ.setColour(juce::Colours::white);
    labelOnEQ.setText(juce::CharPointer_UTF8("EQ ON"));
    
    addAndMakeVisible(labelEQLowFreq);
    labelEQLowFreq.setColour(juce::Colours::white);
    labelEQLowFreq.setText(juce::CharPointer_UTF8("LOW"));
    
    addAndMakeVisible(labelEQLowGain);
    labelEQLowGain.setColour(juce::Colours::white);
    labelEQLowGain.setText(juce::CharPointer_UTF8("GAIN"));

    addAndMakeVisible(labelEQMidFreq);
    labelEQMidFreq.setColour(juce::Colours::white);
    labelEQMidFreq.setText(juce::CharPointer_UTF8("MID"));

    addAndMakeVisible(labelEQMidGain);
    labelEQMidGain.setColour(juce::Colours::white);
    labelEQMidGain.setText(juce::CharPointer_UTF8("GAIN"));

    addAndMakeVisible(labelEQHighFreq);
    labelEQHighFreq.setColour(juce::Colours::white);
    labelEQHighFreq.setText(juce::CharPointer_UTF8("HIGH"));

    addAndMakeVisible(labelEQHighGain);
    labelEQHighGain.setColour(juce::Colours::white);
    labelEQHighGain.setText(juce::CharPointer_UTF8("GAIN"));
    
    
    // Creación de sliders y botones con sus respectivos Attachments
    addAndMakeVisible(inputSlider);
    inputSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    inputSlider.setColour(juce::Slider::thumbColourId, juce::Colours::darkviolet);
    inputSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    inputSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    inputSlider.setDoubleClickReturnValue(true, 1.0);
    inputSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                   "a_input",
                                                                                                   inputSlider);
    
    addAndMakeVisible(drywetSlider);
    drywetSlider.setSliderStyle(juce::Slider::LinearVertical);
    drywetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    drywetSlider.setColour(juce::Slider::thumbColourId, juce::Colours::darkviolet);
    drywetSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    drywetSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    drywetSlider.setDoubleClickReturnValue (true, 0.33);
    drywetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "b_drywet",
                                                                                                    drywetSlider);
    
    addAndMakeVisible(freezeSlider);
    freezeSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    freezeSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    freezeSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    freezeSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    freezeSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    freezeSlider.setDoubleClickReturnValue (true, 0);
    freezeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "g_freeze",
                                                                                                    freezeSlider);
    
    
    addAndMakeVisible(reflexSlider);
    reflexSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    reflexSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    reflexSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    reflexSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::darkviolet);
    reflexSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    reflexSlider.setDoubleClickReturnValue (true, 0.5);
    reflexSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                  "c_reflect",
                                                                                                  reflexSlider);
    
    
    addAndMakeVisible(dampSlider);
    dampSlider.setSliderStyle (juce::Slider::LinearVertical);
    dampSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    dampSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    dampSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    dampSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    dampSlider.setDoubleClickReturnValue (true, 0.86);
    dampSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                  "d_damp",
                                                                                                  dampSlider);
    
    addAndMakeVisible(dimensionSlider);
    dimensionSlider.setSliderStyle (juce::Slider::LinearVertical);
    dimensionSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    dimensionSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    dimensionSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    dimensionSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    dimensionSlider.setDoubleClickReturnValue (true, 1.0);
    dimensionSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                       "e_size",
                                                                                                       dimensionSlider);

    addAndMakeVisible(spreadSlider);
    spreadSlider.setSliderStyle (juce::Slider::LinearVertical);
    spreadSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    spreadSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    spreadSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    spreadSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    spreadSlider.setDoubleClickReturnValue (true, 0.5);
    spreadSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "f_st",
                                                                                                    spreadSlider);
    
    //Output
    addAndMakeVisible (outputSlider);
    outputSlider.setSliderStyle (juce::Slider::LinearVertical);
    outputSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    outputSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    outputSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    outputSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    outputSlider.setDoubleClickReturnValue (true, 1);
    outputSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "m_output",
                                                                                                    outputSlider);
    
    // COMP
    addAndMakeVisible(thdSlider);
    //thdSlider.setTooltip (TRANS("Umbral en dB (0 -50 dB)"));
    thdSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    thdSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    thdSlider.setColour (juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    thdSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::deepskyblue);
    thdSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    
    thdSlider.setDoubleClickReturnValue (true, -12);
    thdSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "s_thd",
                                                                                                 thdSlider);
    
    addAndMakeVisible(ratioSlider);
    ratioSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    ratioSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    ratioSlider.setColour (juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    ratioSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::deepskyblue);
    ratioSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    ratioSlider.setDoubleClickReturnValue (true, 2);
    ratioSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                   "t_ratio",
                                                                                                   ratioSlider);
    
    addAndMakeVisible(atkSlider);
    atkSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    atkSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    atkSlider.setColour (juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    atkSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::deepskyblue);
    atkSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    atkSlider.setDoubleClickReturnValue (true, 15);
    atkSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "u_atk",
                                                                                                 atkSlider);
    
    addAndMakeVisible(relSlider);
    relSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    relSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    relSlider.setColour (juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    relSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::deepskyblue);
    relSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    relSlider.setDoubleClickReturnValue (true, 25);
    relSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "v_rel",
                                                                                                 relSlider);
    
    addAndMakeVisible(makeupSlider);
    makeupSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    makeupSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    makeupSlider.setColour (juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    makeupSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::deepskyblue);
    makeupSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    makeupSlider.setDoubleClickReturnValue (true, 0);
    makeupSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                   "w_makeup",
                                                                                                    makeupSlider);
    

    addAndMakeVisible(onCompSlider);
    onCompSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    onCompSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    onCompSlider.setColour (juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    onCompSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::deepskyblue);
    onCompSlider.setColour(juce::Slider::trackColourId, juce::Colours::whitesmoke);
    onCompSlider.setDoubleClickReturnValue (true, 1);
    onCompSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "r_onoffCOMP",
                                                                                                    onCompSlider);
    
    // FILTROS
    addAndMakeVisible (hpfSlider);
    hpfSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    hpfSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    hpfSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    hpfSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    hpfSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    hpfSlider.setDoubleClickReturnValue (true, 20);
    hpfSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "l_hpf",
                                                                                                 hpfSlider);
    
    addAndMakeVisible (lpfSlider);
    lpfSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    lpfSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    lpfSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkviolet);
    lpfSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::whitesmoke);
    lpfSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::violet);
    lpfSlider.setDoubleClickReturnValue (true, 20);
    lpfSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "k_lpf",
                                                                                                 lpfSlider);
    // EQ
    addAndMakeVisible(onEqSlider);
    onEqSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    onEqSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    onEqSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    onEqSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::whitesmoke);
    onEqSlider.setColour(juce::Slider::trackColourId, juce::Colours::seagreen);
    onEqSlider.setDoubleClickReturnValue (true, 0);
    onEqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                  "q_onoffEQ",
                                                                                                  onEqSlider);
    
    addAndMakeVisible (lowFreqSlider);
    lowFreqSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    lowFreqSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    lowFreqSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    lowFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
    lowFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    lowFreqSlider.setDoubleClickReturnValue (true, 500);
    lowFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                     "n_lowFreq",
                                                                                                     lowFreqSlider);
    
    addAndMakeVisible (lowGainSlider);
    lowGainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    lowGainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    lowGainSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    lowGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
    lowGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    lowGainSlider.setDoubleClickReturnValue (true, 0);
    lowGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                     "h_lowGain",
                                                                                                     lowGainSlider);
    
    addAndMakeVisible (peakFreqSlider);
    peakFreqSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    peakFreqSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    peakFreqSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    peakFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
    peakFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    peakFreqSlider.setDoubleClickReturnValue (true, 500);
    peakFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                      "o_peakFreq",
                                                                                                      peakFreqSlider);
    
    addAndMakeVisible (peakGainSlider);
    peakGainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    peakGainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    peakGainSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    peakGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
    peakGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    peakGainSlider.setDoubleClickReturnValue (true, 0);
    peakGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                      "i_peakGain",
                                                                                                      peakGainSlider);
    
    addAndMakeVisible (hiFreqSlider);
    hiFreqSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    hiFreqSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    hiFreqSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    hiFreqSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
    hiFreqSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    hiFreqSlider.setDoubleClickReturnValue (true, 500);
    hiFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "p_hiFreq",
                                                                                                    hiFreqSlider);
    
    addAndMakeVisible (hiGainSlider);
    hiGainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    hiGainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    hiGainSlider.setColour (juce::Slider::thumbColourId, juce::Colours::seagreen);
    hiGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::seagreen);
    hiGainSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::whitesmoke);
    hiGainSlider.setDoubleClickReturnValue (true, 0);
    hiGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "j_hiGain",
                                                                                                    hiGainSlider);
    

    
    
    // Tamaño reajustable
    auto size = processor.getSavedSize();
    setResizable(true, true);
    setSize(size.x, size.y);
    setResizeLimits(ancho*1.65f, alto*1.65f, ancho*2.65, alto*2.65);
    getConstrainer()->setFixedAspectRatio(ancho/alto);
}

JCBReverbAudioProcessorEditor::~JCBReverbAudioProcessorEditor()
{
}

//==============================================================================
void JCBReverbAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (juce::Colours::black);
    
    txtEntrada.draw  (g, 1.0f);
    txtDryWet.draw   (g, 1.0f);
    txtReflex.draw   (g, 1.0f);
    txtDamp.draw   (g, 1.0f);
    txtDimension.draw (g, 1.0f);
    txtEstereo.draw  (g, 1.0f);
    txtTitulo.draw   (g, 1.0f);
    
}

void JCBReverbAudioProcessorEditor::resized()
{
    auto altoAll = 45.0;
    
    auto xInput = (getWidth() * (1.25+50)/ancho);
    auto yInput = getHeight() * altoAll/alto;
    auto wInput = getWidth()  * 16./ancho;
    auto hInput = getHeight() * 115./alto;
    
    auto xDryWet = (getWidth() * (63+50)/ancho);
    auto yDryWet = getHeight() * altoAll/alto;
    auto wDryWet = getWidth()  * 16./ancho;
    auto hDryWet = getHeight() * 115./alto;
    
    auto xFreeze = getWidth()  * 165/ancho;
    auto yFeeze = getHeight()  * 90/alto;
    auto wFreeze = getWidth()  * 75/ancho;
    auto hFreeze = getHeight() * 17/alto;
    
    auto xReflex = getWidth()  * 274/ancho;
    auto yReflex = getHeight() * (altoAll-5)/alto;
    auto wReflex = getWidth()  * 150/ancho;
    auto hReflex = getHeight() * 115/alto;
    
    auto xDamp = (getWidth()   * (442+25)/ancho);
    auto yDamp = getHeight() * altoAll/alto;
    auto wDamp = getWidth()  * 16./ancho;
    auto hDamp = getHeight() * 115./alto;
    
    auto xDimension = (getWidth() * (515+10)/ancho);
    auto yDimension = getHeight() * altoAll/alto;
    auto wDimension = getWidth()  * 16./ancho;
    auto hDimension = getHeight() * 115./alto;
    
    auto xSpread = (getWidth() * (583)/ancho);
    auto ySpread = getHeight() * altoAll/alto;
    auto wSpread = getWidth()  * 16./ancho;
    auto hSpread = getHeight() * 115./alto;
    
    // Output
 
    auto xOutput = (getWidth() * (600+50)/ancho);
    auto yOutput = getHeight() * altoAll/alto;
    auto wOutput = getWidth()  * 16./ancho;
    auto hOutput = getHeight() * 115./alto;
    
    // COMP
    auto xThd = getWidth()  * 8/ancho;
    auto yThd = getHeight() * 2/alto;
    auto wThd = getWidth()  * 48/ancho;
    auto hThd = getHeight() * 48/alto;
    
    auto xRatio = getWidth()  * 56/ancho;
    auto yRatio = getHeight() * 2/alto;
    auto wRatio = getWidth()  * 48/ancho;
    auto hRatio = getHeight() * 48/alto;
    
    auto xAtk = getWidth()  * 104/ancho;
    auto yAtk = getHeight() * 2/alto;
    auto wAtk = getWidth()  * 48/ancho;
    auto hAtk = getHeight() * 48/alto;
    
    auto xRel = getWidth()  * 152/ancho;
    auto yRel = getHeight() * 2/alto;
    auto wRel = getWidth()  * 48/ancho;
    auto hRel = getHeight() * 48/alto;
    
    auto xMake = getWidth()  * 200/ancho;
    auto yMake = getHeight() * 2/alto;
    auto wMake = getWidth()  * 48/ancho;
    auto hMake = getHeight() * 48/alto;
    
    auto xOnComp = getWidth()  * 254/ancho;
    auto yOnComp = getHeight() * 2/alto;
    auto wOnComp = getWidth()  * 46/ancho;
    auto hOnComp = getHeight() * 48/alto;
    
    // Filtros
    auto xHpf = getWidth()  * 300/ancho;
    auto yHpf = getHeight() * 2/alto;
    auto wHpf = getWidth()  * 48/ancho;
    auto hHpf = getHeight() * 48/alto;
    
    auto xLpf = getWidth()  * 348/ancho;
    auto yLpf = getHeight() * 2/alto;
    auto wLpf = getWidth()  * 48/ancho;
    auto hLpf = getHeight() * 48/alto;
    
    // EQ
    auto xOnEq = getWidth()  * 396/ancho;
    auto yOnEq = getHeight() * 2/alto;
    auto wOnEq = getWidth()  * 46/ancho;
    auto hOnEq = getHeight() * 48/alto;
    
    auto xLowFreq = getWidth()  * 444/ancho;
    auto yLowFreq = getHeight() * 2/alto;
    auto wLowFreq = getWidth()  * 44/ancho;
    auto hLowFreq = getHeight() * 48/alto;
    
    auto xLowGain = getWidth()  * 479.5f/ancho;
    auto yLowGain = getHeight() * 2/alto;
    auto wLowGain = getWidth()  * 44/ancho;
    auto hLowGain = getHeight() * 48/alto;
    
    auto xPeakFreq = getWidth()  * 531/ancho;
    auto yPeakFreq = getHeight() * 2/alto;
    auto wPeakFreq = getWidth()  * 44/ancho;
    auto hPeakFreq = getHeight() * 48/alto;
    
    auto xPeakGain = getWidth()  * 567/ancho;
    auto yPeakGain = getHeight() * 2/alto;
    auto wPeakGain = getWidth()  * 44/ancho;
    auto hPeakGain = getHeight() * 48/alto;
    
    auto xHiFreq = getWidth()  * 618/ancho;
    auto yHiFreq = getHeight() * 2/alto;
    auto wHiFreq = getWidth()  * 44/ancho;
    auto hHiFreq = getHeight() * 48/alto;
    
    auto xHiGain = getWidth()  * 654/ancho;
    auto yHiGain = getHeight() * 2/alto;
    auto wHiGain = getWidth()  * 44/ancho;
    auto hHiGain = getHeight() * 48/alto;
    
    
    // URL
    auto xUrl    = getWidth()  * 272/ancho;
    auto yUrl    = getHeight() * 170/alto;
    auto wUrl    = getHeight() * 500/ancho;
    auto hUrl    = getHeight() * 24/alto;
    

    
    
    
    // Corrección offset
    auto correct = 11;
    
    processor.setSavedSize({getWidth(), getHeight()});
    
    txtEntrada.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/17.f,
                                                                                correct+getHeight()/1.27f,
                                                                                getWidth(),
                                                                                getHeight()/25.f)));
    
    
    txtEntrada.setFontHeight (getHeight()/10.f);
    
    txtDryWet.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(2.5f*getWidth()/17.f,
                                                                               correct+getHeight()/1.27f,
                                                                               getWidth(),
                                                                               getHeight()/25.f)));
    
    txtDryWet.setFontHeight (getHeight()/10.f);
    
    txtCongelar.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(4.25f*getWidth()/17.f,
                                                                                 correct+getHeight()/1.27f,
                                                                                 getWidth(),
                                                                                 getHeight()/25.f)));
    
    txtCongelar.setFontHeight (getHeight()/10.f);
    
    txtReflex.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(8.14f*getWidth()/17.f,
                                                                               correct+getHeight()/1.47f,
                                                                               getWidth(),
                                                                               getHeight()/25.f)));
    
    txtReflex.setFontHeight (getHeight()/10.f);
    
    txtDamp.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(  (11.25f*getWidth())/17.f,
                                                                               correct+getHeight()/1.27f,
                                                                               getWidth(),
                                                                               getHeight()/25.f)));
    
    txtDamp.setFontHeight (getHeight()/10.f);
    
    txtDimension.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>( 12.45f*getWidth()/17.f,
                                                                                 correct+getHeight()/1.27f,
                                                                                 getWidth(),
                                                                                 getHeight()/25.f)));
    
    txtDimension.setFontHeight (getHeight()/10.f);
    
    txtEstereo.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>( 14.f*getWidth()/17.f,
                                                                                correct+getHeight()/1.27f,
                                                                                getWidth(),
                                                                                getHeight()/25.f)));
    
    txtEstereo.setFontHeight (getHeight()/10.f);
    
    
    txtOutput.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>((15.5f*getWidth()/17.f) + 10,
                                                                                correct+getHeight()/1.27f,
                                                                                getWidth(),
                                                                                getHeight()/25.f)));
    
    txtOutput.setFontHeight (getHeight()/10.f);
    
//    txtTitulo.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(7.555f*getWidth()/17.f,
//                                                                               correct+getHeight()/1.15f,
//                                                                               getWidth(),
//                                                                               getHeight()/20.f)));
//
//    txtTitulo.setFontHeight (getHeight()/20.f);
    
    
    

    // set Bounds
    mFondo.setBoundsRelative(0.f, 0.f, 1.f, 1.f);
    
    inputSlider.setBounds     (xInput, yInput+correct, wInput, hInput);
    drywetSlider.setBounds    (xDryWet, yDryWet+correct, wDryWet, hDryWet);
    freezeSlider.setBounds    (xFreeze, yFeeze+correct, wFreeze, hFreeze);

    reflexSlider.setBounds    (xReflex, yReflex+correct, wReflex, hReflex);
    dampSlider.setBounds      (xDamp, yDamp+correct, wDamp, hDamp);

    dimensionSlider.setBounds (xDimension, yDimension+correct, wDimension, hDimension);
    spreadSlider.setBounds    (xSpread, ySpread+correct, wSpread, hSpread);
    
    outputSlider.setBounds    (xOutput, yOutput+correct, wOutput, hOutput);

    
    thdSlider.setBounds       (xThd, yThd, wThd, hThd);
    ratioSlider.setBounds     (xRatio, yRatio, wRatio, hRatio);
    atkSlider.setBounds       (xAtk, yAtk, wAtk, hAtk);
    relSlider.setBounds       (xRel, yRel, wRel, hRel);
    makeupSlider.setBounds    (xMake, yMake, wMake, hMake);
    onCompSlider.setBounds    (xOnComp, yOnComp, wOnComp, hOnComp);

    hpfSlider.setBounds       (xHpf, yHpf, wHpf, hHpf);
    lpfSlider.setBounds       (xLpf, yLpf, wLpf, hLpf);
    
    onEqSlider.setBounds      (xOnEq, yOnEq, wOnEq, hOnEq);
    lowFreqSlider.setBounds   (xLowFreq, yLowFreq, wLowFreq, hLowFreq);
    lowGainSlider.setBounds   (xLowGain, yLowGain, wLowGain, hLowGain);
    peakFreqSlider.setBounds  (xPeakFreq, yPeakFreq, wPeakFreq, hPeakFreq);
    peakGainSlider.setBounds  (xPeakGain, yPeakGain, wPeakGain, hPeakGain);
    hiFreqSlider.setBounds    (xHiFreq, yHiFreq, wHiFreq, hHiFreq);
    hiGainSlider.setBounds    (xHiGain, yHiGain, wHiGain, hHiGain);
    
    titleLink.setBounds       (xUrl, yUrl, wUrl, hUrl);
    
    // LABELS COMP
    labelThd.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/30.f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelThd.setFontHeight    (getHeight()/10.f);
    
    labelRatio.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/9.55f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelRatio.setFontHeight    (getHeight()/10.f);
    
    labelAtk.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/5.79f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelAtk.setFontHeight    (getHeight()/10.f);
    
    labelRel.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/4.15f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelRel.setFontHeight    (getHeight()/10.f);
    
    labelMakeUp.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/3.35f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelMakeUp.setFontHeight    (getHeight()/10.f);
    
    labelOnComp.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/2.7f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelOnComp.setFontHeight    (getHeight()/10.f);
    
    
    
    
    //
    labelHPF.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/2.21f,
                                                                              correct+getHeight()/11.98f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelHPF.setFontHeight    (getHeight()/12.f);
    
    
    labelLPF.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.915f,
                                                                              correct+getHeight()/11.98f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelLPF.setFontHeight    (getHeight()/12.f);

    //
    
    
    
    
    labelOnEQ.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.725f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelOnEQ.setFontHeight    (getHeight()/10.f);
    
    labelEQLowFreq.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.535f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelEQLowFreq.setFontHeight    (getHeight()/10.f);
    
    labelEQLowGain.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.425f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelEQLowGain.setFontHeight    (getHeight()/10.f);
    
    labelEQMidFreq.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.284f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelEQMidFreq.setFontHeight    (getHeight()/10.f);
    
    labelEQMidGain.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.210f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelEQMidGain.setFontHeight    (getHeight()/10.f);
    
    labelEQHighFreq.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.114f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelEQHighFreq.setFontHeight    (getHeight()/10.f);
    
    labelEQHighGain.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/1.05f,
                                                                              correct+getHeight()/5.75f,
                                                                              getWidth(),
                                                                              getHeight()/25.f)));
    labelEQHighGain.setFontHeight    (getHeight()/10.f);
    
    


}
