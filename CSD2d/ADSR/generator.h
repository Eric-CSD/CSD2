#ifndef _GENERATOR_H_
#define _GENERATOR_H_
#include <iostream>
#include "clock.h"
using namespace std;

class Generator{
public:
  Generator();
  ~Generator();

  void tick();
  float getSample();
  void setSample(float newSample);
protected:
  double sample = 0;
  double samplerate = 44100;
};
#endif
