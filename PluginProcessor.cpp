/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluckSynthAudioProcessor::PluckSynthAudioProcessor()
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
    totalNumVoices = 16;
   
   voices.resize(totalNumVoices);
   noteActive.resize(128, false);
      activeNoteToVoice.resize(128, -1);
    
   toneParameter = new juce::AudioParameterFloat(juce::ParameterID("1", 1), "Tone", 0.5f, 1.0f, 0.95f);
    
   distortionGainParameter = new juce::AudioParameterFloat(juce::ParameterID("2", 2), " Distortion", 0.0f, 100.0f, 10.0f);
    outputGainParameter = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Output Gain", -96.0f, 36.0f, 0.0f);
    
//   dampParameter = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Damp", 0.2f, 3.0f, 0.5f);
   phaserFreqParameter = new juce::AudioParameterFloat(juce::ParameterID("4", 4), "Rate", 0.0f, 20.0f, 2.0f);
   depthParameter = new juce::AudioParameterFloat(juce::ParameterID("5", 5), "Depth", 0.0f, 1.0f, 0.0f);

    feedbackSliderParameter = new juce::AudioParameterFloat(juce::ParameterID("6", 6), "Feedback", 0.0f, 100.0f, 0.0f);
    //double fs = getSampleRate();
    //double fs = 48000;
    delayTimeKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("7", 7), "Delay Time", 0.0f, 2.0f, 0.0f);
    dryWetKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("8", 8), "Dry/Wet", 0.0f, 100.0f, 0.0f);
    pitchShiftKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("9", 9), "SemiTone", -12, 12, 0);
    LPF_frequencyknobParameter = new juce::AudioParameterFloat(juce::ParameterID("10", 10), "LPF_frequency knob", 0.f, 20000.f, 20000.f);
    HPF_frequencyknobParameter = new juce::AudioParameterFloat(juce::ParameterID("11",11), "HPF_frequency knob", 0.f, 20000.f, 0.f);
//   bypassParameter = new juce::AudioParameterBool(juce::ParameterID("7",7),"bypass",true);
   //    // order matters here - add the slider parameter first and then the knob parameter
    addParameter(toneParameter);
 //   addParameter(dampParameter);
    addParameter(distortionGainParameter);
    addParameter(outputGainParameter);
   addParameter(phaserFreqParameter);
   addParameter(depthParameter);
   addParameter(feedbackSliderParameter);
   addParameter(delayTimeKnobParameter);
   addParameter(dryWetKnobParameter);
//    addParameter(pitchShiftKnobParameter);
//    addParameter(LPF_frequencyknobParameter);
//    addParameter(HPF_frequencyknobParameter);
//    MMeffec.updateCoefficients_LPF(*LPF_frequencyknobParameter, getSampleRate());
//    MMeffec.updateCoefficients_HPF(*HPF_frequencyknobParameter, getSampleRate());
    auto numInputs = getTotalNumInputChannels();

    currentLPF_freq = *LPF_frequencyknobParameter;
    currentHPF_freq = *HPF_frequencyknobParameter;
//   addParameter(bypassParameter);

   currentTone = *toneParameter;
   currentDistortionGain = *distortionGainParameter;
 //  currentDamp = *dampParameter;

   currentPhaserFreq = *phaserFreqParameter;
////   // currentBypassState = *bypassParameter;
   currentDepth = *depthParameter;

   currentOutputGain = *outputGainParameter;
//   isBypassed = *bypassParameter;
   //auto numInputs = getTotalNumInputChannels();
    currentFeedback = *feedbackSliderParameter;
    currentDelayTime = *delayTimeKnobParameter;
    currentDryWet = *dryWetKnobParameter;
    currentPitch = *pitchShiftKnobParameter;
}

PluckSynthAudioProcessor::~PluckSynthAudioProcessor()
{
   // tempBuffer.clear();
}

//==============================================================================
const juce::String PluckSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluckSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluckSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluckSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluckSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluckSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluckSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluckSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PluckSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluckSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PluckSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    tempBuffer.setSize(getTotalNumOutputChannels(), samplesPerBlock, true, true, true);
    //tempBuffer.clear();
   
    //    temp2Buffer.setSize(getTotalNumOutputChannels(), samplesPerBlock, true, true, true);
    for (int voiceIndex = 0; voiceIndex < totalNumVoices; ++voiceIndex) {
        voices[voiceIndex].prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    }
    
//    for (int voiceIndex = 0; voiceIndex < totalNumVoices; ++voiceIndex) {
//        Oscillator[voiceIndex].prepareToPlay(sampleRate, samplesPerBlock, getTotalNumInputChannels());
//    }
    ///
    ///
//    // Determine FFT order
//    int minWindowLength = MINBLOCKSPERWINDOW * samplesPerBlock;
//    int order = 0;
//    int windowLength = 1;
//    while (windowLength < minWindowLength)
//    {
//        order++;
//        windowLength *= 2;
//    }
//    shifterBank.resize(getTotalNumOutputChannels());
//    for (auto ch = 0; ch < getTotalNumOutputChannels(); ch++)
//    {
//        shifterBank[ch] = std::unique_ptr<SHIFTER>(new SHIFTER);
//        shifterBank[ch]->init(order);
//    }
    ///
    ///
    //
//    MMeffec.resetDelays(getTotalNumOutputChannels());
        AM.prepareToPlay(sampleRate);

Delay.prepareToPlay(sampleRate, samplesPerBlock, getNumInputChannels());
}

void PluckSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluckSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void PluckSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //tempBuffer.clear();
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

     juce::MidiBuffer::Iterator it(midiMessages);
      juce::MidiMessage currentMessage;
      int samplePosition;

   

    while (it.getNextEvent(currentMessage, samplePosition)) {
        if (currentMessage.isNoteOn()) {
            int noteNumber = currentMessage.getNoteNumber();
            int velocity = currentMessage.getVelocity();
            
            int voiceIndex = findAvailableVoice();
            
            if (voiceIndex >= 0) {
                double frequency = 440.0 * std::pow(2.0, (noteNumber - 69.0) / 12.0);
                voices[voiceIndex].setFrequency(frequency);
                voices[voiceIndex].setAmplitude(velocity / 127.0);
                voices[voiceIndex].setNoteDuration(0.8);
                voices[voiceIndex].turnOn();
                noteActive[noteNumber] = true;
                activeNoteToVoice[noteNumber] = voiceIndex;
                DBG(currentMessage.getNoteNumber());
                voices[voiceIndex].noiseBurst(getSampleRate(),frequency);
                    
            }
        }
        
        if (currentMessage.isNoteOff()) {
            int noteNumber = currentMessage.getNoteNumber();
            if (noteNumber >= 0 && noteNumber <= 127) {
                noteActive[noteNumber] = false;
                int voiceIndex = activeNoteToVoice[noteNumber];
                if (voiceIndex >= 0) {
                    voices[voiceIndex].turnOff();
                    voices[voiceIndex].setAmplitude(0.0);
                    
                }

                
            }
        }
    }

    
    for (int voiceIndex = 0; voiceIndex < voices.size(); ++voiceIndex) {
        if (voices[voiceIndex].isOn()) {
   

            voices[voiceIndex].setParameters(*toneParameter, 0.7);
       //     voices[voiceIndex].d=*dampParameter;
            voices[voiceIndex].d = *toneParameter;
            tempBuffer = voices[voiceIndex].process(buffer,0.8,*toneParameter);
            int numSamplesToProcess = buffer.getNumSamples();
            for (int channel = 0; channel < tempBuffer.getNumChannels(); ++channel) {
                        
                buffer.addFrom(channel, 0, tempBuffer.getReadPointer(channel), numSamplesToProcess, 0.8 / voices.size());
                    }
            
        }
    }
//    if(currentPitch!= *pitchShiftKnobParameter){
//        currentPitch= *pitchShiftKnobParameter;
//    }
//    float hopratio = pow(2.0f, *pitchShiftKnobParameter / 12.0);
//
//    for (auto ch = 0; ch < getTotalNumOutputChannels(); ch++)
//        shifterBank[ch]->step(buffer.getWritePointer(ch), buffer.getNumSamples(), hopratio);

    

    
//    outputGain.processAudio(buffer);

//
//
//
//
   


            

if (*distortionGainParameter != currentDistortionGain) {
            currentDistortionGain = *distortionGainParameter;
        }
//
//
//
    distortionEffect.process(buffer, *distortionGainParameter);



           
    if (*delayTimeKnobParameter != currentDelayTime || *feedbackSliderParameter != currentFeedback || *dryWetKnobParameter != currentDryWet) {
        currentDelayTime = *delayTimeKnobParameter;
        currentFeedback = *feedbackSliderParameter;
        currentDryWet = *dryWetKnobParameter;

    }
    Delay.circularBuffer(buffer, *delayTimeKnobParameter * getSampleRate(), *feedbackSliderParameter, *dryWetKnobParameter);
    float fs = getSampleRate();
    
//        if ( *LPF_frequencyknobParameter != currentLPF_freq || *HPF_frequencyknobParameter != currentHPF_freq )
//        {   lpf.updateCoeffs(*LPF_frequencyknobParameter, fs);
//            currentLPF_freq = *LPF_frequencyknobParameter;
//            currentHPF_freq = *HPF_frequencyknobParameter;
//
//        }
    

//    if ( *LPF_frequencyknobParameter != currentLPF_freq || *HPF_frequencyknobParameter != currentHPF_freq )
//    {   MMeffec.updateCoefficients_LPF(*LPF_frequencyknobParameter, fs);
//        MMeffec.updateCoefficients_HPF(*HPF_frequencyknobParameter, fs);
//
//        currentLPF_freq = *LPF_frequencyknobParameter;
//        currentHPF_freq = *HPF_frequencyknobParameter;

   // }
    //if (totalNumInputChannels == 2) {
   // MMeffec.processaudio(buffer,fs);
//    for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
//    {
//
//        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
//        {
//            buffer.getWritePointer(channel)[sample] = lpf.processAudioSample(buffer.getReadPointer(channel)[sample]);
//        }
//    }
    if (*phaserFreqParameter != currentPhaserFreq || *depthParameter != currentDepth) {

        currentPhaserFreq = *phaserFreqParameter;
        currentDepth = *depthParameter;
    }
    AM.processBlock(buffer, *phaserFreqParameter, *depthParameter);
    if (*outputGainParameter != currentOutputGain) {
        currentOutputGain = *outputGainParameter;
        outputGain.setGain(*outputGainParameter);
    }
      outputGain.processAudio(buffer);


}
int PluckSynthAudioProcessor::findAvailableVoice() {
    for (int i = 0; i < totalNumVoices; ++i) {
        int voiceIndex = (lastAllocatedVoice + 1 + i) % totalNumVoices;
        if (!voices[voiceIndex].isOn()) {
            lastAllocatedVoice = voiceIndex;
            return voiceIndex;
        }
    }
    return -1; // If all voices are in use
}
//==============================================================================
bool PluckSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluckSynthAudioProcessor::createEditor()
{
    return new PluckSynthAudioProcessorEditor (*this);
}

//==============================================================================
void PluckSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluckSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluckSynthAudioProcessor();
}
