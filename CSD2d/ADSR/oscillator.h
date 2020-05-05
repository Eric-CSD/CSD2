#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include "generator.h"
#include <iostream>
using namespace std;

class Oscillator : public Generator {
public:
  Oscillator();
  ~Oscillator();

  //getters and setters
  void setFrequency(float frequency);
  float getAmplitude();
protected:
  float amplitude = 0.4;
  float frequency = 440;
  float phase;
};
#endif
