/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
IDelayAudioProcessor::IDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

IDelayAudioProcessor::~IDelayAudioProcessor()
{
}

//==============================================================================
const String IDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String IDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void IDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void IDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    
    dbuf.setSize(getNumOutputChannels(),  100000);
    dbuf.clear();
    
    dw = 0;
    dr = 1;
    ds = 50000;
}

void IDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void IDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    int numSamples = buffer.getNumSamples();
    float wet_now = wet;
    float dry_now = dry;
    int ds_now = ds;
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    
    for (int i = 0; i < numSamples; ++i)
    {
        dbuf.setSample(0, dw, channelDataL[i]);
        channelDataL[i] = dry_now * channelDataL[i] + wet_now * dbuf.getSample(0, dr);
        
        dbuf.setSample(1, dw, channelDataR[i]);
        channelDataR[i] = dry_now * channelDataL[i] + wet_now * dbuf.getSample(1, dr);
        
        dw = (dw + 1 ) % ds_now ;
        dr = (dr + 1 ) % ds_now ;

    }
    
    
}

//==============================================================================
bool IDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* IDelayAudioProcessor::createEditor()
{
    return new IDelayAudioProcessorEditor (*this);
}

//==============================================================================
void IDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void IDelayAudioProcessor::set_wet(float val)
{
    wet = val;
}

void IDelayAudioProcessor::set_dry(float val)
{
    dry = val;
}

void IDelayAudioProcessor::set_ds(int val)
{
    ds = val;
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IDelayAudioProcessor();
}
