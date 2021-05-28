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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NoiseGateAudioProcessorEditor  : public AudioProcessorEditor,
                                       public Timer,
                                       public juce::Slider::Listener
{
public:
    //==============================================================================
    NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor* ownerFilter);
    ~NoiseGateAudioProcessorEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    NoiseGateAudioProcessor* getProcessor() const
    {
        return static_cast <NoiseGateAudioProcessor*>(getAudioProcessor());
    }
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::Label> gainLabel;
    std::unique_ptr<juce::Slider> releaseSlider;
    std::unique_ptr<juce::Label> release__label;
    std::unique_ptr<juce::Slider> attackSlider;
    std::unique_ptr<juce::Label> attack__label;
    std::unique_ptr<juce::Slider> holdtimeSlider;
    std::unique_ptr<juce::Label> holdtimeLabel;
    std::unique_ptr<juce::Slider> attackSlider2;
    std::unique_ptr<juce::Label> alabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

