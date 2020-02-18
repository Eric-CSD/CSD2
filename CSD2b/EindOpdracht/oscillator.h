#ifndef _OSC_H_
#define _OSC_H_
#include <iostream>
using namespace std;

#define PI_2 6.28318530717959

class Oscillator{
public:
  //Constructor and destructor
  Oscillator();
  ~Oscillator();

  //getters and setters
  void setFrequency(float frequency);

  //return the current sample
  float getSample();
  float getAmplitude();
protected:
  float amplitude = 0.1;
  float frequency;
  float phase;
  // contains the current sample
  float sample;
  float samplerate;
};

#endif
