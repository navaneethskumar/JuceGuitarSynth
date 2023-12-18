/*
  ==============================================================================

    PluckedString.h
    Created: 31 Oct 2023 1:33:50pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PluckedString
{
public:
    PluckedString();
    ~PluckedString();
    void noiseBurst(double sampleRate, double fo);
    float processSample(double sampleRate, int channel, float aVal, float dVal);
    juce::AudioBuffer<float> process(juce::AudioBuffer<float>& buffer,float aVal, float dVal);
    void prepareToPlay(float sampleRate, int samplesPerBlock, int numInputChannels);
    
    bool onOff;
    double frequency;
    void setOscillatorState(bool newState);
    void setFrequency(double frequency);
    void setAmplitude(float amplitude);
    void setNoteDuration(float duration);
    double getAmplitude();
    void turnOn();
    void turnOff();
    bool isOn();
    float amplitude;
    juce::Random random;
    juce::AudioBuffer<float> tempBuffer;
    juce::AudioBuffer<float> circBuff;
     std::vector<float> circularBufferL;
    std::vector<float> circularBufferR;
     double a=0.99;
    double d = 0.99;  // Decay factor
    void setParameters(float aVal, float dVal);
    bool plucky = false;
private:

    double noteDuration;
    int numSamplesRemaining;
    int bufferLength;
    double numInputChannels;
    double sampleRate;
    int pointerL;
    int prev_pointerL;
    int pointerR;
    int prev_pointerR;
    int L;
    float value;
    
    

};

