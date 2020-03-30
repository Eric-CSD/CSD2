#ifndef _SIN_LFO_H_
#define _SIN_LFO_H_

#include "oscillator.h"

#include <iostream>
using namespace std;

class Lfo_sine : public Oscillator {
public:
  // Constructor and destructor
  Lfo_sine();
  ~Lfo_sine();

  // Calculation of sine wave
  void tick(double samplerate);
};

#endif
