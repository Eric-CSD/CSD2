#ifndef _SIN_H_
#define _SIN_H_

#include "oscillator.h"

#include <iostream>
using namespace std;

class Sine : public Oscillator {
public:
  // Constructor and destructor
  Sine();
  ~Sine();

  // Calculation of sine wave
  void tick(double samplerate);
};

#endif
