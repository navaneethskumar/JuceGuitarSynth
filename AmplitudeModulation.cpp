/*
  ==============================================================================

    AmplitudeModulation.cpp
    Created: 7 Nov 2023 2:56:42am
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "AmplitudeModulation.h"

AmplitudeModulation::AmplitudeModulation()
    : phase(0.0f), modulationFrequency(500.0), modulationDepth(0.5), sampleRate(44100.0) {}
AmplitudeModulation::~AmplitudeModulation(){}
void AmplitudeModulation::prepareToPlay(double newSampleRate)
{
    sampleRate = newSampleRate;
}

void AmplitudeModulation::processBlock(juce::AudioBuffer<float>& buffer, double frequency, double depth)
{
    int numChannels = buffer.getNumChannels();
    modulationDepth = depth;
    modulationFrequency = frequency;

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        double phaseIncrement = frequency / sampleRate;

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {

            float delayedSample = channelData[sample] * std::sin(phase);
            
            channelData[sample] += static_cast<float>(modulationDepth * delayedSample);


            phase += static_cast<float>(phaseIncrement);
            if (phase >= juce::MathConstants<float>::twoPi)
                phase -= juce::MathConstants<float>::twoPi;
        }
    }
}
