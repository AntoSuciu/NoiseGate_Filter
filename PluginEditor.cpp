/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NoiseGateAudioProcessorEditor::NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    gainSlider.reset (new juce::Slider ("Gain Slider"));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setRange (-70, 0, 1);
    gainSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 40, 20);
    gainSlider->addListener (this);

    gainSlider->setBounds (184, 8, 168, 24);

    gainLabel.reset (new juce::Label ("Gain Label",
                                      TRANS("gain")));
    addAndMakeVisible (gainLabel.get());
    gainLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    gainLabel->setJustificationType (juce::Justification::centredLeft);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    gainLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    gainLabel->setBounds (152, 8, 39, 24);

    releaseSlider.reset (new juce::Slider ("release slider"));
    addAndMakeVisible (releaseSlider.get());
    releaseSlider->setRange (0, 1, 0.1);
    releaseSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    releaseSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 40, 20);
    releaseSlider->addListener (this);

    releaseSlider->setBounds (192, 32, 152, 24);

    release__label.reset (new juce::Label ("release label",
                                           TRANS("release")));
    addAndMakeVisible (release__label.get());
    release__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    release__label->setJustificationType (juce::Justification::centredLeft);
    release__label->setEditable (false, false, false);
    release__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    release__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    release__label->setBounds (128, 32, 71, 24);

    attackSlider.reset (new juce::Slider ("attack slider"));
    addAndMakeVisible (attackSlider.get());
    attackSlider->setRange (0, 1, 0.1);
    attackSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    attackSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 40, 20);
    attackSlider->addListener (this);

    attackSlider->setBounds (192, 56, 151, 24);

    attack__label.reset (new juce::Label ("attack label",
                                          TRANS("attack")));
    addAndMakeVisible (attack__label.get());
    attack__label->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    attack__label->setJustificationType (juce::Justification::centredLeft);
    attack__label->setEditable (false, false, false);
    attack__label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    attack__label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    attack__label->setBounds (144, 56, 47, 24);

    holdtimeSlider.reset (new juce::Slider ("holdtime slider"));
    addAndMakeVisible (holdtimeSlider.get());
    holdtimeSlider->setRange (0, 1, 0.1);
    holdtimeSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    holdtimeSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 40, 20);
    holdtimeSlider->addListener (this);

    holdtimeSlider->setBounds (192, 80, 151, 24);

    holdtimeLabel.reset (new juce::Label ("holdtime label",
                                          TRANS("holdtime")));
    addAndMakeVisible (holdtimeLabel.get());
    holdtimeLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    holdtimeLabel->setJustificationType (juce::Justification::centredLeft);
    holdtimeLabel->setEditable (false, false, false);
    holdtimeLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    holdtimeLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    holdtimeLabel->setBounds (128, 80, 71, 24);

    attackSlider2.reset (new juce::Slider ("attack slider"));
    addAndMakeVisible (attackSlider2.get());
    attackSlider2->setRange (0, 1, 0.1);
    attackSlider2->setSliderStyle (juce::Slider::LinearHorizontal);
    attackSlider2->setTextBoxStyle (juce::Slider::TextBoxRight, false, 40, 20);
    attackSlider2->addListener (this);

    attackSlider2->setBounds (192, 104, 151, 24);

    alabel.reset (new juce::Label ("a label",
                                   TRANS("a\n")));
    addAndMakeVisible (alabel.get());
    alabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    alabel->setJustificationType (juce::Justification::centredLeft);
    alabel->setEditable (false, false, false);
    alabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    alabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    alabel->setBounds (160, 104, 24, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 200);


    //[Constructor] You can add your own custom stuff here..
    getProcessor()->RequestUIUpdate();
    startTimer(200); //porneste temporizatorul cu un interval de 200 ms
    //[/Constructor]
}

NoiseGateAudioProcessorEditor::~NoiseGateAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainSlider = nullptr;
    gainLabel = nullptr;
    releaseSlider = nullptr;
    release__label = nullptr;
    attackSlider = nullptr;
    attack__label = nullptr;
    holdtimeSlider = nullptr;
    holdtimeLabel = nullptr;
    attackSlider2 = nullptr;
    alabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NoiseGateAudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff9d76af));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void NoiseGateAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void NoiseGateAudioProcessorEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    NoiseGateAudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider.get())
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        ourProcessor->setParameter(NoiseGateAudioProcessor::gain, (float)gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider.get())
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
        ourProcessor->setParameter(NoiseGateAudioProcessor::release, (float)gainSlider->getValue());
        //[/UserSliderCode_releaseSlider]
    }
    else if (sliderThatWasMoved == attackSlider.get())
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        ourProcessor->setParameter(NoiseGateAudioProcessor::attack, (float)gainSlider->getValue());
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == holdtimeSlider.get())
    {
        //[UserSliderCode_holdtimeSlider] -- add your slider handling code here..
        ourProcessor->setParameter(NoiseGateAudioProcessor::holdtime, (float)gainSlider->getValue());
        //[/UserSliderCode_holdtimeSlider]
    }
    else if (sliderThatWasMoved == attackSlider2.get())
    {
        //[UserSliderCode_attackSlider2] -- add your slider handling code here..
        //[/UserSliderCode_attackSlider2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void NoiseGateAudioProcessorEditor::timerCallback()
{
    NoiseGateAudioProcessor* ourProcessor = getProcessor();
    if (ourProcessor->NeedsUIUpdate())
    {
        gainSlider->setValue(ourProcessor->getParameter(NoiseGateAudioProcessor::gain), juce::dontSendNotification);

        //thresholdSlider->setValue(ourProcessor->getParameter(NoiseGateAudioProcessor::threshold), juce::dontSendNotification);
        ourProcessor->ClearUIUpdateFlag();
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="NoiseGateAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="NoiseGateAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="200">
  <BACKGROUND backgroundColour="ff9d76af"/>
  <SLIDER name="Gain Slider" id="f4a0c5eaa4dbd9b8" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="184 8 168 24" min="-70.0"
          max="0.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Gain Label" id="593accca3e12dcaa" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="152 8 39 24" edTextCol="ff000000"
         edBkgCol="0" labelText="gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="release slider" id="fa89fc99f3e64e5c" memberName="releaseSlider"
          virtualName="" explicitFocusOrder="0" pos="192 32 152 24" min="0.0"
          max="1.0" int="0.1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="release label" id="c9d8ac868179ed48" memberName="release__label"
         virtualName="" explicitFocusOrder="0" pos="128 32 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="release" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="attack slider" id="c1e07b24de359df3" memberName="attackSlider"
          virtualName="" explicitFocusOrder="0" pos="192 56 151 24" min="0.0"
          max="1.0" int="0.1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="attack label" id="b5089b47ef59130d" memberName="attack__label"
         virtualName="" explicitFocusOrder="0" pos="144 56 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="holdtime slider" id="1341323d31902a22" memberName="holdtimeSlider"
          virtualName="" explicitFocusOrder="0" pos="192 80 151 24" min="0.0"
          max="1.0" int="0.1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="holdtime label" id="70c34e1f041f2130" memberName="holdtimeLabel"
         virtualName="" explicitFocusOrder="0" pos="128 80 71 24" edTextCol="ff000000"
         edBkgCol="0" labelText="holdtime" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="attack slider" id="ea4b6ca69ef2e99f" memberName="attackSlider2"
          virtualName="" explicitFocusOrder="0" pos="192 104 151 24" min="0.0"
          max="1.0" int="0.1" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="a label" id="11bb6d5a97fa664e" memberName="alabel" virtualName=""
         explicitFocusOrder="0" pos="160 104 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="a&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

