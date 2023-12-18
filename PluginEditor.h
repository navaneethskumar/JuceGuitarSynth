/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomSlider.h"
//==============================================================================
/**
*/
class PluckSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PluckSynthAudioProcessorEditor (PluckSynthAudioProcessor&);
    ~PluckSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluckSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluckSynthAudioProcessorEditor)
    juce::Slider pitchShiftKnob;
    juce::Label pitchShiftLabel;

        juce::Slider toneKnob;
        juce::Label toneLabel;
        juce::Slider dampKnob;
        juce::Label dampLabel;
        juce::Slider phaserFreqKnob;
        juce::Label phaserFreqLabel;
        juce::ToggleButton bypassButton;
        
        juce::Slider depthKnob;
        juce::Label depthLabel;
    
        juce::Slider distortionGainKnob;
        juce::Label distortionGainLabel;
        //juce::ComboBox oscillatorComboBox;
        juce::Slider outputGainKnob;
        juce::Label outputGainLabel;
    //
        juce::Slider feedbackSlider;
        juce::Label feedbackLabel;
        juce::Slider delayTimeKnob;
        juce::Label delayTimeLabel;
        juce::Slider dryWetKnob;
        juce::Label dryWetLabel;
    juce::Slider lowPassKnob;
    juce::Label lowPassLabel;
    juce::Slider highPassKnob;
    juce::Label highPassLabel;
    
        //declaring parameters here
        juce::AudioParameterFloat* toneKnobParameter;
        juce::AudioParameterFloat* distGainKnobParameter;

//    
        juce::AudioParameterFloat* feedbackSliderParameter;
        juce::AudioParameterFloat* delayTimeKnobParameter;
        juce::AudioParameterFloat* dryWetKnobParameter;


        juce::AudioParameterFloat* outputGainKnobParameter;
        juce::AudioParameterFloat* depthknobParameter;
        //juce::AudioParameterFloat* dampKnobParameter;
        juce::AudioParameterFloat* lowPassKnobParameter;
        juce::AudioParameterFloat* highPassKnobParameter;
        //juce::AudioParameterFloat* dampKnobParameter;
        juce::AudioParameterFloat* phaserFreqKnobParameter;
//        juce::AudioParameterBool* bypassParameter;
        juce::AudioParameterFloat* pitchShiftParameter;
        juce::Label textLabel;
        juce::Font textFont   { 12.0f };
        juce::Image background;
        CustomSlider Custom;
    
};
