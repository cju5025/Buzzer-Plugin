/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HardClipperAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HardClipperAudioProcessorEditor (HardClipperAudioProcessor&);
    ~HardClipperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Slider mMixSlider;
    Slider mThresholdSlider;
    
    HardClipperAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HardClipperAudioProcessorEditor)
};
