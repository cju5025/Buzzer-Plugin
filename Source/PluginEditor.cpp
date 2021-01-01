/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HardClipperAudioProcessorEditor::HardClipperAudioProcessorEditor (HardClipperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (200, 100);
    
    auto& params = processor.getParameters();
    
    //mix slider
    AudioParameterFloat* mMixParameter = (AudioParameterFloat*)params.getUnchecked(0);
    
    mMixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mMixSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 15);
    mMixSlider.setRange(mMixParameter->range.start, mMixParameter->range.end, 0.01f);
    mMixSlider.setValue(*mMixParameter);
    addAndMakeVisible(mMixSlider);
    
    mMixSlider.onValueChange = [this, mMixParameter] {*mMixParameter = mMixSlider.getValue(); };
    mMixSlider.onDragStart = [mMixParameter] {mMixParameter->beginChangeGesture(); };
    mMixSlider.onDragEnd = [mMixParameter] {mMixParameter->endChangeGesture(); };
    
    //threshold slider
    AudioParameterFloat* mThresholdParameter = (AudioParameterFloat*)params.getUnchecked(1);
    
    mThresholdSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mThresholdSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 15);
    mThresholdSlider.setRange(mThresholdParameter->range.start, mThresholdParameter->range.end, 0.0001f);
    mThresholdSlider.setValue(*mThresholdParameter);
    addAndMakeVisible(mThresholdSlider);
    
    mThresholdSlider.onValueChange = [this, mThresholdParameter] {*mThresholdParameter = mThresholdSlider.getValue(); };
    mThresholdSlider.onDragStart = [mThresholdParameter] {mThresholdParameter->beginChangeGesture(); };
    mThresholdSlider.onDragEnd = [mThresholdParameter] {mThresholdParameter->endChangeGesture(); };
}

HardClipperAudioProcessorEditor::~HardClipperAudioProcessorEditor()
{
}

//==============================================================================
void HardClipperAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
}

void HardClipperAudioProcessorEditor::resized()
{
    mMixSlider.setBounds(0, 0, 100, 100);
    mThresholdSlider.setBounds(100, 0, 100, 100);
}
