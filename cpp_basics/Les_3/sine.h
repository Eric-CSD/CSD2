#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include "math.h"

#define SAMPLERATE 441000
#define PI_2 6.28318530717959

class Sine
{
public:
  Sine(float frequency);
  ~Sine();

  float getSample();
  void tick();
  void setFrequency(float frequency);
  float getFrequency();

private:
  float amplitute;
  float frequency;
  float phase;
};
#endif
