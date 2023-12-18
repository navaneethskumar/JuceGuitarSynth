/*
  ==============================================================================

    PluckedString.cpp
    Created: 31 Oct 2023 1:33:50pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "PluckedString.h"
#include <JuceHeader.h>

PluckedString::PluckedString(){


    frequency = 440;
    a = 0.7f;
    d = 0.7f;
    bufferLength=512;
    L=100;
    numInputChannels=2;
    sampleRate=44100;
    pointerL=0;
    prev_pointerL=0;
    pointerR=0;
    prev_pointerR=0;
    onOff=false;
    value=0;
    noteDuration=2.0;
    plucky=false;
    amplitude = 0.5;
    
}
PluckedString::~PluckedString(){}

void PluckedString::prepareToPlay(float newSampleRate, int samplesPerBlock, int totalNumOutputChannels){
    // Calculate the required buffer length
    
    // Initialize the circular buffer with random noise
    this->numInputChannels= totalNumOutputChannels;
    sampleRate = newSampleRate;
    bufferLength = samplesPerBlock;
    
    circularBufferL.resize(L, 0.0f);
    circularBufferR.resize(L, 0.0f);
    
    tempBuffer.setSize(numInputChannels, samplesPerBlock, true, true, true);
    //tempBuffer.clear();
    circBuff.setSize(totalNumOutputChannels,L);
//    circBuff.clear();
            pointerL=0;
            prev_pointerL= L-1;

            pointerR=0;
            prev_pointerR= L-1;
    
}
void PluckedString::setNoteDuration(float duration){
    
    noteDuration=duration;
    numSamplesRemaining=noteDuration*sampleRate;
}
void PluckedString::setFrequency(double freq) {
    frequency = freq;
}
void PluckedString::setParameters(float aVal, float dVal){
    a=aVal;
    d=dVal;
    
}
void PluckedString::setAmplitude(float amp) {
    amplitude = amp;
}
double PluckedString::getAmplitude(){

    return amplitude;
}
void PluckedString::turnOn() {
    onOff = true;
    if(plucky){
        if(numSamplesRemaining==0){
            turnOff();
        }
    }
}

void PluckedString::turnOff() {
    onOff = false;
    
}

bool PluckedString::isOn(){
    return onOff;
}
void PluckedString::noiseBurst(double sampleRate , double fo){

    //create the noise burst of length L and padded zeros upto 2 seconds
    if (onOff) {
        frequency=fo;
        L = round(sampleRate / frequency);
        
//        for(int channel=0; channel<numInputChannels; ++channel){
//            for (int i = 0; i < L; ++i){
//    circBuff.getWritePointer(channel)[i]= (random.nextFloat() - 0.5f) * 2.0f;}
//        }
//        pointerL=0;
//        prev_pointerL= L-1;
//
//        pointerR=0;
//        prev_pointerR= L-1;
//
//
//    }

       // bufferLength = round(sampleRate * noteDuration);
        
        circularBufferL.resize(L, 0.0f);
        circularBufferR.resize(L, 0.0f);

        for (int i = 0; i < L; ++i)
            circularBufferL[i]= (random.nextFloat() - 0.5f) * 2.0f;
        for (int i = 0; i < L; ++i)
            circularBufferR[i]= (random.nextFloat() - 0.5f) * 2.0f;

        pointerL=0;
        prev_pointerL= L-1;

        pointerR=0;
        prev_pointerR= L-1;


    }
        

}
float PluckedString::processSample(double sampleRate, int channel, float aVal, float dVal){
    
//    value = d*(circBuff.getReadPointer(channel)[pointerL]*a + circBuff.getReadPointer(channel)[prev_pointerL] * (1-a));
//           circBuff.getWritePointer(channel)[pointerL]=value;
//           pointerL++;
//               if(pointerL>=L){
//
//                   pointerL=0;
//               }
//
//           prev_pointerL=pointerL;
//
//       }
    a=aVal;
    d=dVal;
//    if(channel==0){
//
//        value = d *(circBuff.getReadPointer(channel)[pointerL]*a + circBuff.getReadPointer(channel)[prev_pointerL] * (1-a));
//        circBuff.getWritePointer(channel)[pointerL]=value;
//
//            if(pointerL>=L){
//
//                pointerL=0;
//            }
//        pointerL++;
//        prev_pointerL=pointerL;
//
//    }
//        //
////
//    if(channel==1){
//
//    value = d* (circBuff.getReadPointer(channel)[pointerR]*a + circBuff.getReadPointer(channel)[prev_pointerR] * (1-a));
//        circBuff.getWritePointer(channel)[pointerR] = value;
//
//            if(pointerR>=L){
//
//                pointerR=0;
//            }
//        pointerR++;
//        prev_pointerR=pointerR;
//
//    }
    
    if(channel==0){

        value = d*(circularBufferL[pointerL]*a + circularBufferL[prev_pointerL] * (1-a));
        circularBufferL[pointerL]=value;
        prev_pointerL=pointerL;
        pointerL++;
            if(pointerL>=L){

                pointerL=0;
            }

        
        
    }
        //
//                           circularBuffer.getWritePointer(channel)[pointer] = value;
    if(channel==1){

    value = d*(circularBufferR[pointerR]*a + circularBufferR[prev_pointerR] * (1-a));
        circularBufferR[pointerR] = value;
        prev_pointerR=pointerR;
        pointerR++;
            if(pointerR>=L){

                pointerR=0;
            }

        

    }
   
    return value;


}
juce::AudioBuffer<float> PluckedString::process(juce::AudioBuffer<float>& buffer,float aVal,float dVal) {
    d=dVal;
    a=aVal;
   // tempBuffer.clear();
    if (amplitude!=0.0 && onOff) {
        
        for(int channel =0; channel<buffer.getNumChannels();++channel){
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
                //     int channel=0;
                float sampleValueL=0;
            sampleValueL =processSample(sampleRate,channel,a,d) * amplitude;
                tempBuffer.getWritePointer(channel)[sample] = sampleValueL;
//                buffer.getWritePointer(channel)[sample]=sampleValueL;
                
            }
            //numSamplesRemaining--;
        }
//        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
//            int channel=1;
//            float sampleValueR = processSample(sampleRate, channel) * amplitude;
//             tempBuffer.getWritePointer(channel)[sample] = sampleValueR;
//
////
////
////
//          }
//

           return tempBuffer;
    }
    else{//tempBuffer.clear();
        return tempBuffer;}
    return tempBuffer;
       
}



