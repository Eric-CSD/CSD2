#ifndef _SYNTHESIZER_H_
#define _SYNTHESIZER_H_
#include "synthesizer.h"
#include <iostream>
#include "generator.h"
#include "sine.h"
#include "envelope.h"
#include "clock.h"
#include "subject.h"
using namespace std;

class Synthesizer : public Generator {
public:
  Synthesizer();
  ~Synthesizer();

  //getters and setters
  double noteOn();
  double noteOff();
  void   setEnvelope(float a,float d,float s,float r);
  void setPitch(float f);
  Sine sine;
  Envelope envelope;
  Clock clock2();
  Clock clock1();

protected:
  double output;
};
#endif
