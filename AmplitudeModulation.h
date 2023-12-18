/*
  ==============================================================================

    AmplitudeModulation.h
    Created: 7 Nov 2023 2:56:42am
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AmplitudeModulation
{
public:
    AmplitudeModulation();
    ~AmplitudeModulation();
    void prepareToPlay(double newSampleRate);
    void processBlock(juce::AudioBuffer<float>& buffer,double frequency,double depth);
    double modulationFrequency;
    double modulationDepth;

private:

double sampleRate;
    double phase;
//double phase;
};
