/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class IDelayAudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener
{
public:
    IDelayAudioProcessorEditor (IDelayAudioProcessor&);
    ~IDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    IDelayAudioProcessor& processor;
    
    Random random;
    Slider wetSlider;
    Label wetLabel;
    Slider drySlider;
    Label dryLabel;
    Slider timeSlider;
    Label timeLabel;
    
    void sliderValueChanged(Slider* slider) override;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IDelayAudioProcessorEditor)
};
