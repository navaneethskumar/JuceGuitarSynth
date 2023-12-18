/*
  =============================================================================
    Distortion.c
    Created: 1 Nov 2023 7:07:19
    Author:  Navaneeth Suresh Kuma
  ============================================================================
*/

#include "Distortion.h"

Distortion::Distortion()
{
    // Constructor code here
    drive=0.0;
}

Distortion::~Distortion()
{
    // Destructor code here
}

void Distortion::process(juce::AudioBuffer<float>& buffer, float gain)
{
    drive=gain;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
       
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
           
            buffer.getWritePointer(channel)[sample] = std::tanh(buffer.getReadPointer(channel)[sample] * (1+drive)*10);
            
        }
    }
}
