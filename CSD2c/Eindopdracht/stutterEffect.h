#pragma once
#include "circBuffer.h"
#include <iostream>

class stutterEffect
{
public:
  // initializes the circ buffers for both channels
  CircBuffer buffL;
  CircBuffer buffR;
  // Constructor and destructor
  stutterEffect(float sampleRate, float delayTime, int stutter);
  ~stutterEffect();
  // write sample to the buffers
  void write(float inSample);
  void writeNoLoop(float inSample);
  // output the output samples and dry signal
  inline float readLeft() {return (outSampleL) + inSample;}
  inline float readRight() {return (outSampleR) + inSample ;}
  // set settings
  inline void setTime(float delayTime) {this->delaySize = 441000 /(sampleRate * (delayTime/1000));}
  inline void setSamplerate(float sampleRate) {this->sampleRate = sampleRate;}
  inline void setStutter(int stutter) {this->stutter = stutter;}
protected:
  int sampleRate;
  float delaySize;
  // settings
  int stutter;
  float stutterTime;
  // storage of samples
  float inSample;
  float outSampleL;
  float outSampleR;
  float lastSampleL;
  float lastSampleR;
};
