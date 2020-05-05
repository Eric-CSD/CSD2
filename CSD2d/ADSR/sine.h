#ifndef _SINE_H_
#define _SINE_H_
#include "oscillator.h"
#include <iostream>
using namespace std;

class Sine : public Oscillator {
public:
  Sine();
  ~Sine();

  double sine();
protected:

  double sinoid;
};
#endif
