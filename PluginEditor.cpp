/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluckSynthAudioProcessorEditor::PluckSynthAudioProcessorEditor (PluckSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (660, 400);
    
    setLookAndFeel(&Custom);
    addAndMakeVisible(toneLabel);
    toneLabel.setText("Decay", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(toneKnob);
    
    
    
    addAndMakeVisible(distortionGainKnob);
    distortionGainLabel.setText("Distortion", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(distortionGainKnob);
    
    //outputgain
    addAndMakeVisible(outputGainLabel);
    outputGainLabel.setText("Output Gain", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(outputGainKnob);
    
    //rate
    
    addAndMakeVisible(phaserFreqLabel);
    phaserFreqLabel.setText("Tremolo Rate", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(phaserFreqKnob);
    
    //depth
    addAndMakeVisible(depthLabel);
    depthLabel.setText("Tremolo Depth", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(depthKnob);
    
    // styling
    addAndMakeVisible(feedbackLabel);
    addAndMakeVisible(delayTimeLabel);
    addAndMakeVisible(dryWetLabel);
    feedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(feedbackSlider);
    
    
    delayTimeLabel.setText("Delay Time", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(delayTimeKnob);
    
    
    
    dryWetLabel.setText("Wetness(%)", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(dryWetKnob);
    

//    addAndMakeVisible(lowPassLabel);
//    toneLabel.setText("High Cut", juce::NotificationType::dontSendNotification);
//    addAndMakeVisible(lowPassKnob);
//    //
//    addAndMakeVisible(highPassLabel);
//    toneLabel.setText("Low Cut", juce::NotificationType::dontSendNotification);
//    addAndMakeVisible(highPassKnob);
    
//    addAndMakeVisible(pitchShiftLabel);
//    pitchShiftLabel.setText("Pitch Shift", juce::NotificationType::dontSendNotification);
//    addAndMakeVisible(pitchShiftKnob);
    
    //feedback styling
    
    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    feedbackSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 30, 20);
    
    //label
    
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    feedbackLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    feedbackLabel.setJustificationType(juce::Justification::centredTop);
    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    feedbackLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    //Delay time knob styling
    
    delayTimeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    delayTimeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    delayTimeKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    delayTimeKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 30, 20);
    //label
    
    
    delayTimeLabel.attachToComponent(&delayTimeKnob, false);
    delayTimeLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    delayTimeLabel.setJustificationType(juce::Justification::centredTop);
    delayTimeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    delayTimeLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    // Dry/Wet Knob Styling
    dryWetKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dryWetKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    dryWetKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    dryWetKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 20);
    //label
    
    
    dryWetLabel.attachToComponent(&dryWetKnob, false);
    dryWetLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    dryWetLabel.setJustificationType(juce::Justification::centredTop);
    dryWetLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    dryWetLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    //
    
    toneKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    toneKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    toneKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    toneKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    toneKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    toneLabel.attachToComponent(&toneKnob, false);
    toneLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    toneLabel.setJustificationType(juce::Justification::centredTop);
    toneLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    toneLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    distortionGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    distortionGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    distortionGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    distortionGainKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    distortionGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    distortionGainLabel.attachToComponent(&distortionGainKnob, false);
    
    distortionGainLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    distortionGainLabel.setJustificationType(juce::Justification::centredTop);
    distortionGainLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    distortionGainLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    outputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    outputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    outputGainKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    outputGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    outputGainLabel.attachToComponent(&outputGainKnob, false);
    outputGainLabel.setFont(juce::Font(17.0f, juce::Font::plain));
    outputGainLabel.setJustificationType(juce::Justification::centredTop);
    
    outputGainLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    outputGainLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    phaserFreqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserFreqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserFreqKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    phaserFreqKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    phaserFreqKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    phaserFreqLabel.attachToComponent(&phaserFreqKnob, false);
    phaserFreqLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    phaserFreqLabel.setJustificationType(juce::Justification::centredTop);
    phaserFreqLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    phaserFreqLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    depthKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    depthKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    depthKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    depthLabel.attachToComponent(&depthKnob, false);
    depthLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    depthLabel.setJustificationType(juce::Justification::centredTop);
    depthLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    depthLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    //
    // pitch styling
    
    
    pitchShiftKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    pitchShiftKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchShiftKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    pitchShiftKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    pitchShiftKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    pitchShiftLabel.attachToComponent(&pitchShiftKnob, false);
    pitchShiftLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    pitchShiftLabel.setJustificationType(juce::Justification::centredTop);
    pitchShiftLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    pitchShiftLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    ///
    
    lowPassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowPassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lowPassKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    lowPassKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    lowPassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    lowPassLabel.attachToComponent(&lowPassKnob, false);
    lowPassLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    lowPassLabel.setJustificationType(juce::Justification::centredTop);
    lowPassLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    lowPassLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    highPassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    highPassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    highPassKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    highPassKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    highPassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    highPassLabel.attachToComponent(&highPassKnob, false);
    highPassLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    highPassLabel.setJustificationType(juce::Justification::centredTop);
    highPassLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    highPassLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    //
    ///
    auto parameterTree = audioProcessor.getParameters();
    
    toneKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    
    distGainKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    
    outputGainKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    
    phaserFreqKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    depthknobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);
    
    feedbackSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(5);
    delayTimeKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(6);
    dryWetKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(7);
//    pitchShiftParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(8);
//    lowPassKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(9);
//    highPassKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(10);
    
    
    //
    
    
    
    
    toneKnob.setRange(toneKnobParameter->range.start, toneKnobParameter->range.end, toneKnobParameter->range.interval);
    
    
    
    distortionGainKnob.setRange(distGainKnobParameter->range.start, distGainKnobParameter->range.end, distGainKnobParameter->range.interval);
    
    
    outputGainKnob.setRange(outputGainKnobParameter->range.start, outputGainKnobParameter->range.end, outputGainKnobParameter->range.interval);
    
    phaserFreqKnob.setRange(phaserFreqKnobParameter->range.start, phaserFreqKnobParameter->range.end, phaserFreqKnobParameter->range.interval);
    
    depthKnob.setRange(depthknobParameter->range.start, depthknobParameter->range.end, depthknobParameter->range.interval);
    feedbackSlider.setRange(feedbackSliderParameter->range.start, feedbackSliderParameter->range.end, feedbackSliderParameter->range.interval);
    
    delayTimeKnob.setRange(delayTimeKnobParameter->range.start, delayTimeKnobParameter->range.end, delayTimeKnobParameter->range.interval);
    
    dryWetKnob.setRange(dryWetKnobParameter->range.start, dryWetKnobParameter->range.end, dryWetKnobParameter->range.interval);
    
//    pitchShiftKnob.setRange(pitchShiftParameter->range.start, pitchShiftParameter->range.end, pitchShiftParameter->range.interval);
//    lowPassKnob.setRange(lowPassKnobParameter->range.start, lowPassKnobParameter->range.end, lowPassKnobParameter->range.interval);
//    
//    highPassKnob.setRange(highPassKnobParameter->range.start, highPassKnobParameter->range.end, highPassKnobParameter->range.interval);
    
    //
    
    toneKnob.setValue(0.95f, juce::NotificationType::dontSendNotification);
    
    
    
    distortionGainKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    
    outputGainKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    
    phaserFreqKnob.setValue(2.0f, juce::NotificationType::dontSendNotification);
    
    depthKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    feedbackSlider.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    delayTimeKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    dryWetKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    pitchShiftKnob.setValue(0, juce::NotificationType::dontSendNotification);
    
    lowPassKnob.setValue(20000.0f, juce::NotificationType::dontSendNotification);
    highPassKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    //
    
    feedbackSlider.onValueChange = [this]
    {
        *feedbackSliderParameter = feedbackSlider.getValue();
    };
    
    delayTimeKnob.onValueChange = [this]
    {
        *delayTimeKnobParameter = delayTimeKnob.getValue();
    };
    
    
    dryWetKnob.onValueChange = [this]
    {
        *dryWetKnobParameter = dryWetKnob.getValue();
    };
    
    toneKnob.onValueChange = [this]
    {
        *toneKnobParameter = toneKnob.getValue();
    };
    
    
    distortionGainKnob.onValueChange = [this]
    {
        *distGainKnobParameter = distortionGainKnob.getValue();
    };
    
    outputGainKnob.onValueChange = [this]
    {
        *outputGainKnobParameter = outputGainKnob.getValue();
    };
    phaserFreqKnob.onValueChange = [this]
    {
        *phaserFreqKnobParameter = phaserFreqKnob.getValue();
    };
    
    depthKnob.onValueChange = [this]
    {
        *depthknobParameter = depthKnob.getValue();
    };
    
//    pitchShiftKnob.onValueChange = [this]
//    {
//        *pitchShiftParameter = pitchShiftKnob.getValue();
//        
//    };
//    lowPassKnob.onValueChange = [this]
//    {
//        *lowPassKnobParameter = lowPassKnob.getValue();
//    };
//
//    highPassKnob.onValueChange = [this]
//    {
//        *highPassKnobParameter = highPassKnob.getValue();
//    };
}
PluckSynthAudioProcessorEditor::~PluckSynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void PluckSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);


    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
   
    
    
    
    background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
   // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    
   // background = juce::ImageCache::getFromMemory(BinaryData::guitar_jpg, BinaryData::guitar_jpgSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

    g.setColour (juce::Colours::whitesmoke);
    g.setFont(24.0f);
    
    g.setOpacity(0.9f);

//    g.drawFittedText ("Pluck Synth", getLocalBounds(), juce::Justification::centredTop, 1);
    // Define the background colors for the bordered divisions
//    juce::Colour division1Color = juce::Colours::purple.darker(0.8);
//    // Change this to your desired color
//    juce::Colour division2Color = juce::Colours::purple.darker(0.8);  // Change this to your desired color
    
 
  
}

void PluckSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;



    feedbackSlider.setBounds(5 * x, 3.5 * y, 2.4 * x, 2.4 * y);

    delayTimeKnob.setBounds(3.4 * x, 3.5 * y, 2.4 * x, 2.4 * y);

    dryWetKnob.setBounds(5 * x,6.7 * y, 2.4 * x, 2.4 * y);
toneKnob.setBounds(0.15 * x, 3.8 * y, 2.1 * x, 2.1* y);
distortionGainKnob.setBounds(1.5 * x, 3.8 * y, 2.1 * x, 2.1 * y);
//dampKnob.setBounds(5.9 * x, 3.2 * y, 4 * x, 4 * y);

    phaserFreqKnob.setBounds(7.6 * x, 2.5 * y, 2.6 * x, 2.6 * y);
   depthKnob.setBounds(7 * x, 7 * y, 2.6 * x, 2.6 * y);
//    lowPassKnob.setBounds(7.2 * x, 5.2 * y, 2.2 * x, 2.2 * y);
//   highPassKnob.setBounds(8 * x, 7.2 * y, 2.2 * x, 2.2 * y);
//
outputGainKnob.setBounds(0.5 * x,  6.8* y, 2.8 * x, 2.8 * y);

//pitchShiftKnob.setBounds(7.5 * x, 7.5 * y, 2.2 * x, 2.2 * y);
//
}
