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
    txtEntrada.setColour(juce::Colours::violet);
    txtEntrada.setText("ENTRADA");
    
    addAndMakeVisible(txtDryWet);
    txtDryWet.setColour(juce::Colours::violet);
    txtDryWet.setText("DRY/WET");
    
    addAndMakeVisible(txtTamano);
    txtTamano.setColour(juce::Colours::violet);
    txtTamano.setText(juce::CharPointer_UTF8("REFLEX"));
    
    addAndMakeVisible(txtFiltro);
    txtFiltro.setColour(juce::Colours::violet);
    txtFiltro.setText("DAMP");
    
    addAndMakeVisible(txtDifusion);
    txtDifusion.setColour(juce::Colours::violet);
    txtDifusion.setText(juce::CharPointer_UTF8("TAMAÑO"));
    
    addAndMakeVisible(txtEstereo);
    txtEstereo.setColour(juce::Colours::violet);
    txtEstereo.setText(juce::CharPointer_UTF8("ESTÉREO"));
    
    addAndMakeVisible(txtCongelar);
    txtCongelar.setColour(juce::Colours::violet);
    txtCongelar.setText(juce::CharPointer_UTF8("CONGELAR"));
    
    addAndMakeVisible(txtTitulo);
    txtTitulo.setColour(juce::Colours::darkviolet);
    txtTitulo.setText(juce::CharPointer_UTF8("JCBReverbST 0.2.3"));
    
    // Creación de sliders y botones con sus respectivos Attachments
    addAndMakeVisible(inputSlider);
    inputSlider.setSliderStyle(juce::Slider::LinearVertical);
    inputSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    inputSlider.setColour(juce::Slider::thumbColourId, juce::Colours::violet);
    inputSlider.setColour(juce::Slider::trackColourId, juce::Colours::violet);
    inputSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    inputSlider.setDoubleClickReturnValue(true, 1.0);
    inputSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                   "a_input",
                                                                                                   inputSlider);
    
    addAndMakeVisible(drywetSlider);
    drywetSlider.setSliderStyle(juce::Slider::LinearVertical);
    drywetSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    drywetSlider.setColour(juce::Slider::thumbColourId, juce::Colours::violet);
    drywetSlider.setColour(juce::Slider::trackColourId, juce::Colours::violet);
    drywetSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    drywetSlider.setDoubleClickReturnValue (true, 0.33);
    drywetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "b_drywet",
                                                                                                    drywetSlider);
    
    
    addAndMakeVisible(sizeSlider);
    sizeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 1, 1);
    sizeSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    sizeSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    sizeSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    sizeSlider.setDoubleClickReturnValue (true, 0.5);
    sizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                  "c_reflect",
                                                                                                  sizeSlider);
    
    
    addAndMakeVisible(dampSlider);
    dampSlider.setSliderStyle (juce::Slider::LinearVertical);
    dampSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    dampSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    dampSlider.setColour(juce::Slider::trackColourId, juce::Colours::violet);
    dampSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    dampSlider.setDoubleClickReturnValue (true, 0.86);
    dampSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                  "d_damp",
                                                                                                  dampSlider);
    
    addAndMakeVisible(diffusionSlider);
    diffusionSlider.setSliderStyle (juce::Slider::LinearVertical);
    diffusionSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    diffusionSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    diffusionSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    diffusionSlider.setColour(juce::Slider::trackColourId, juce::Colours::violet);
    diffusionSlider.setDoubleClickReturnValue (true, 1.0);
    diffusionSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                       "e_size",
                                                                                                       diffusionSlider);

    addAndMakeVisible(spreadSlider);
    spreadSlider.setSliderStyle (juce::Slider::LinearVertical);
    spreadSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 1, 1);
    spreadSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    spreadSlider.setColour(juce::Slider::trackColourId, juce::Colours::violet);
    spreadSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    spreadSlider.setDoubleClickReturnValue (true, 0.5);
    spreadSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "f_st",
                                                                                                    spreadSlider);
    
    addAndMakeVisible(freezeButton);
    freezeButton.setSliderStyle (juce::Slider::LinearHorizontal);
    freezeButton.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    freezeButton.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    freezeButton.setColour(juce::Slider::backgroundColourId, juce::Colours::violet);
    freezeButton.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    freezeButton.setDoubleClickReturnValue (true, 0);
    freezeButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "g_freeze",
                                                                                                    freezeButton);
    
    /////////////
    
    addAndMakeVisible(thdSlider);
    //thdSlider.setTooltip (TRANS("Umbral en dB (0 -50 dB)"));
    thdSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    thdSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    thdSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    thdSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    thdSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    
    thdSlider.setDoubleClickReturnValue (true, -12);
    thdSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "s_thd",
                                                                                                 thdSlider);
    
    addAndMakeVisible(ratioSlider);
    ratioSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    ratioSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    ratioSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    ratioSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    ratioSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    ratioSlider.setDoubleClickReturnValue (true, 2);
    ratioSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                   "t_ratio",
                                                                                                   ratioSlider);
    
    addAndMakeVisible(atkSlider);
    atkSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    atkSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    atkSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    atkSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    atkSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    atkSlider.setDoubleClickReturnValue (true, 15);
    atkSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "u_atk",
                                                                                                 atkSlider);
    
    addAndMakeVisible(relSlider);
    relSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    relSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    relSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    relSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    relSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    relSlider.setDoubleClickReturnValue (true, 25);
    relSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                 "v_rel",
                                                                                                 relSlider);
    
    addAndMakeVisible(makeupSlider);
    makeupSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    makeupSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 80, 20);
    makeupSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    makeupSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::violet);
    makeupSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    makeupSlider.setDoubleClickReturnValue (true, 0);
    makeupSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                   "w_makeup",
                                                                                                    makeupSlider);
    

    addAndMakeVisible(onCompSlider);
    onCompSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    onCompSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 1, 1);
    onCompSlider.setColour (juce::Slider::thumbColourId, juce::Colours::violet);
    onCompSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::violet);
    onCompSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkviolet);
    onCompSlider.setDoubleClickReturnValue (true, 0);
    onCompSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts,
                                                                                                    "r_onoffCOMP",
                                                                                                    onCompSlider);
    
    
    



    
    
    
    
    
    
    /////////////
    auto size = processor.getSavedSize();
    setResizable(true, true);
    setSize(size.x, size.y);
    setResizeLimits(ancho*1.5, alto*1.5, ancho*2.5, alto*2.5);
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
    txtTamano.draw   (g, 1.0f);
    txtFiltro.draw   (g, 1.0f);
    txtDifusion.draw (g, 1.0f);
    txtEstereo.draw  (g, 1.0f);
    txtTitulo.draw   (g, 1.0f);
    
}

void JCBReverbAudioProcessorEditor::resized()
{
    auto altoAll = 45.0;
    
    auto xInput = getWidth() * 1.25/ancho;
    auto yInput = getHeight() * altoAll/alto;
    auto wInput = getWidth() * 116./ancho;
    auto hInput = getHeight() * 115./alto;
    
    auto xDryWet = getWidth() * 63/ancho;
    auto yDryWet = getHeight() * altoAll/alto;
    auto wDryWet = getWidth() * 116./ancho;
    auto hDryWet = getHeight() * 115./alto;
    
    auto xSize = getWidth() * 272/ancho;
    auto ySize = getHeight() * (altoAll-5)/alto;
    auto wSize = getWidth() * 150/ancho;
    auto hSize = getHeight() * 115/alto;
    
    auto xDamp = getWidth() * 442./ancho;
    auto yDamp = getHeight() * altoAll/alto;
    auto wDamp = getWidth() * 116./ancho;
    auto hDamp = getHeight() * 115./alto;
    
    auto xDiffusion = getWidth() * 515/ancho;
    auto yDiffusion = getHeight() * altoAll/alto;
    auto wDiffusion = getWidth() * 116./ancho;
    auto hDiffusion = getHeight() * 115./alto;
    
    auto xSpread = getWidth() * 595/ancho;
    auto ySpread = getHeight() * altoAll/alto;
    auto wSpread = getWidth() * 116./ancho;
    auto hSpread = getHeight() * 115./alto;
    
    auto xButton = getWidth() * 165/ancho;
    auto yButton = getHeight() * 90/alto;
    auto wButton = getWidth() * 75/ancho;
    auto hButton = getHeight() * 17/alto;
    
    /////////////
    
    auto xThd = getWidth() * 8/ancho;
    auto yThd = getHeight() * 2/alto;
    auto wThd = getWidth() * 48/ancho;
    auto hThd = getHeight() * 48/alto;
    
    //48, 8, 48, 48
    auto xRatio = getWidth() * 56/ancho;
    auto yRatio = getHeight() * 2/alto;
    auto wRatio = getWidth() * 48/ancho;
    auto hRatio = getHeight() * 48/alto;
    
    auto xAtk = getWidth() * 104/ancho;
    auto yAtk = getHeight() * 2/alto;
    auto wAtk = getWidth() * 48/ancho;
    auto hAtk = getHeight() * 48/alto;
    
    auto xRel = getWidth() * 152/ancho;
    auto yRel = getHeight() * 2/alto;
    auto wRel = getWidth() * 48/ancho;
    auto hRel = getHeight() * 48/alto;
    
    auto xMake = getWidth() * 200/ancho;
    auto yMake = getHeight() * 2/alto;
    auto wMake = getWidth() * 48/ancho;
    auto hMake = getHeight() * 48/alto;
    
    auto xOnComp = getWidth() * 248/ancho;
    auto yOnComp = getHeight() * 2/alto;
    auto wOnComp = getWidth() * 48/ancho;
    auto hOnComp = getHeight() * 48/alto;

    ////////////
    auto correct = 11;
    
    processor.setSavedSize({getWidth(), getHeight()});
    
    txtEntrada.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(getWidth()/17.f,
                                                                                correct+getHeight()/1.27f,
                                                                                getWidth(),
                                                                                getHeight()/25.f)));
    
    
    txtEntrada.setFontHeight (getHeight()/10.f);
    
    txtDryWet.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(2.5*getWidth()/17.f,
                                                                               correct+getHeight()/1.27f,
                                                                               getWidth(),
                                                                               getHeight()/25.f)));
    
    txtDryWet.setFontHeight (getHeight()/10.f);
    
    txtCongelar.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(4.25*getWidth()/17.f,
                                                                                 correct+getHeight()/1.27f,
                                                                                 getWidth(),
                                                                                 getHeight()/25.f)));
    
    txtCongelar.setFontHeight (getHeight()/10.f);
    
    txtTamano.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(8*getWidth()/17.f,
                                                                               correct+getHeight()/1.27f,
                                                                               getWidth(),
                                                                               getHeight()/25.f)));
    
    txtTamano.setFontHeight (getHeight()/10.f);
    
    txtFiltro.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(11.85*getWidth()/17.f,
                                                                               correct+getHeight()/1.27f,
                                                                               getWidth(),
                                                                               getHeight()/25.f)));
    
    txtFiltro.setFontHeight (getHeight()/10.f);
    
    txtDifusion.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(13.5*getWidth()/17.f,
                                                                                 correct+getHeight()/1.27f,
                                                                                 getWidth(),
                                                                                 getHeight()/25.f)));
    
    txtDifusion.setFontHeight (getHeight()/10.f);
    
    txtEstereo.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(15.5*getWidth()/17.f,
                                                                                correct+getHeight()/1.27f,
                                                                                getWidth(),
                                                                                getHeight()/25.f)));
    
    txtEstereo.setFontHeight (getHeight()/10.f);
    
    txtTitulo.setBoundingBox(juce::Parallelogram<float>(juce::Rectangle<float>(7.52*getWidth()/17.f,
                                                                               correct+getHeight()/1.15f,
                                                                               getWidth(),
                                                                               getHeight()/20.f)));
    
    txtTitulo.setFontHeight (getHeight()/20.f);
    

    // Bounds
    mFondo.setBoundsRelative(0.f, 0.f, 1.f, 1.f);
    
    inputSlider.setBounds     (xInput, yInput+correct, wInput, hInput);
    drywetSlider.setBounds    (xDryWet, yDryWet+correct, wDryWet, hDryWet);
    sizeSlider.setBounds      (xSize, ySize+correct, wSize, hSize);
    dampSlider.setBounds      (xDamp, yDamp+correct, wDamp, hDamp);
    diffusionSlider.setBounds (xDiffusion, yDiffusion+correct, wDiffusion, hDiffusion);
    spreadSlider.setBounds    (xSpread, ySpread+correct, wSpread, hSpread);
    freezeButton.setBounds    (xButton, yButton+correct, wButton, hButton);
    
    thdSlider.setBounds       (xThd, yThd, wThd, hThd);
    ratioSlider.setBounds     (xRatio, yRatio, wRatio, hRatio);
    atkSlider.setBounds       (xAtk, yAtk, wAtk, hAtk);
    relSlider.setBounds       (xRel, yRel, wRel, hRel);
    makeupSlider.setBounds    (xMake, yMake, wMake, hMake);
    onCompSlider.setBounds    (xOnComp, yOnComp, wOnComp, hOnComp);

    
}
