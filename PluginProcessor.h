/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


#include <complex>
#include <vector>
#include "PluckedString.h"
#include "AmplitudeModulation.h"
#include "delayEffect.h"
#include "Distortion.h"
#include "gainControl.h"


typedef std::complex<float> Cfloat;
constexpr auto MINBLOCKSPERWINDOW = 16;
//==============================================================================
/**
*/

class PluckSynthAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    PluckSynthAudioProcessor();
    ~PluckSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    int findAvailableVoice();
    float frequencyInHz = 0.0f;
private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluckSynthAudioProcessor)
    
    std::vector<bool> noteActive;  // Tracks active MIDI notes
   int totalNumVoices;
   //juce::Array<Voice> voices; // An array of Voice instances
   int lastAllocatedVoice;
   
   std::vector<int> activeNoteToVoice;
   juce::AudioBuffer<float> tempBuffer;
   juce::AudioBuffer<float> temp2Buffer;
   std::vector<PluckedString> voices;
   AmplitudeModulation AM;
   gainControl outputGain;
   delayEffect Delay;
   //std::vector<OscillatorClass> Oscillator;
   Distortion distortionEffect;
   juce::AudioParameterFloat* toneParameter;
   //juce::AudioParameterFloat* dampParameter;
   //juce::AudioParameterFloat* gainParameter;
   juce::AudioParameterFloat* phaserFreqParameter;
   juce::AudioParameterFloat* depthParameter;
   
   juce::AudioParameterFloat* distortionGainParameter;
   
   juce::AudioParameterFloat* outputGainParameter;
   
   juce::AudioParameterBool* bypassParameter;
   juce::AudioParameterFloat* feedbackSliderParameter;
   juce::AudioParameterFloat* delayTimeKnobParameter;
   juce::AudioParameterFloat* dryWetKnobParameter;
   juce::AudioParameterFloat* pitchShiftKnobParameter;
   juce::AudioParameterFloat* LPF_frequencyknobParameter;
   juce::AudioParameterFloat* HPF_frequencyknobParameter;
   float currentTone;
   float currentDamp;
   
   float currentPhaserFreq;
   
   float currentDepth;
   float currentDistortionGain;
   float currentLPF_freq;
   float currentHPF_freq;

   float currentOutputGain;
   float currentFeedback;
   float currentDelayTime;
   float currentDryWet;
   bool isBypassed;
   float currentPitch=0;
    

};
