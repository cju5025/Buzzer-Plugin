#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HardClipperAudioProcessor::HardClipperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mMixParameter = new AudioParameterFloat("mix", "Mix", 0.f, 1.f, 0.3f));
    addParameter(mThresholdParameter = new AudioParameterFloat("threshold", "Threshold", 0.01f, 0.1f, 0.f));
}

HardClipperAudioProcessor::~HardClipperAudioProcessor()
{
}

//==============================================================================
const juce::String HardClipperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HardClipperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HardClipperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HardClipperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HardClipperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HardClipperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HardClipperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HardClipperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HardClipperAudioProcessor::getProgramName (int index)
{
    return {};
}

void HardClipperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HardClipperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HardClipperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HardClipperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HardClipperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int i = 0; i < buffer.getNumSamples(); ++i) {

        auto input = channelData[i];
        auto cleanOut = channelData[i];

            if (input > *mThresholdParameter)
            {
            input = *mThresholdParameter;
            }
            else if (input < -*mThresholdParameter)
            {
            input = -*mThresholdParameter;
            }
            
            channelData[i] = ((1 - *mMixParameter) * cleanOut) + (*mMixParameter * input);        }
    }
}

//==============================================================================
bool HardClipperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HardClipperAudioProcessor::createEditor()
{
    return new HardClipperAudioProcessorEditor (*this);
}

//==============================================================================
void HardClipperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HardClipperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HardClipperAudioProcessor();
}
