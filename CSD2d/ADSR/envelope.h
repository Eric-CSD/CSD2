#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_
#include "envelope.h"
#include <iostream>
#include "generator.h"

using namespace std;

class Envelope : public Generator {
public:
  Envelope();
  ~Envelope();

  //getters and setters
void setADSR(float attack,float decay,float sustain, float release);
float ads();
float rel();
protected:
  float attack;
  float decay;
  float sustain;
  float release;
  float amp;
  float att;
  float dec;
  float rele;
};
#endif
