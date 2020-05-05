#include "envelope.h"
#include "math.h"
#include "generator.h"

Envelope::Envelope() : Generator() {

}

Envelope::~Envelope() {
}

void Envelope::setADSR(float attack,float decay,float sustain, float release) {
  this->attack = attack;
  this->decay = decay;
  this->sustain = sustain;
  this->release = release;
  att=samplerate*(attack/1000);
  dec=samplerate*(decay/1000);
  rele=samplerate*(release/1000);
}
float Envelope::ads() {

  if(getSample()<=att){
    amp=getSample()/att;
  } else if (getSample()>att && getSample()<=att+dec && amp>sustain){
    amp= 1-((getSample()-att)/dec);
  } else{
    amp = sustain;
  }
  tick();
return amp;
}

float Envelope::rel() {
  if(amp> 0){
    amp -=1/rele;
  }
  setSample(0);
return amp;
}
