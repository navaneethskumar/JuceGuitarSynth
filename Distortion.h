/*
  ==============================================================================

    Distortion.h
    Created: 6 Oct 2023 1:23:44pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Distortion
{
public:
    Distortion();
 
   ~Distortion();
   void process(juce::AudioBuffer<float>& buffer, float gain);
//
private:
    float drive;

};

