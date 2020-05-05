#include "synthesizer.h"
#include "math.h"
#include "generator.h"
#include "oscillator.h"
#include "sine.h"
#include "envelope.h"

Synthesizer::Synthesizer() : Generator() {
    sine.setFrequency(440);
    envelope.setADSR(500,500,0.5,500);
}

Synthesizer::~Synthesizer() {
}



double Synthesizer::noteOn() {
  output = sine.sine()*envelope.ads();
  return output;
}

double Synthesizer::noteOff(){
  output = sine.sine()*envelope.rel();
  return output;
}

void Synthesizer::setEnvelope(float a,float d,float s,float r){
  envelope.setADSR(a,d,s,r);
}

void Synthesizer::setPitch(float f){
  sine.setFrequency(f);
}
