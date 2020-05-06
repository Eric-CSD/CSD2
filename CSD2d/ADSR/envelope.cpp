#include "envelope.h"
#include "math.h"
#include "generator.h"

Envelope::Envelope() : Generator() {

}

Envelope::~Envelope() {
}
//sets ADSR values
void Envelope::setADSR(float attack,float decay,float sustain, float release) {
  this->attack = attack;
  this->decay = decay;
  this->sustain = sustain;
  this->release = release;
  att=samplerate*(attack/1000);
  dec=samplerate*(decay/1000);
  rele=samplerate*(release/1000);
}
//calculates envelope for attack decay sustain
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
//calculates release envelope
float Envelope::rel() {
  if(amp> 0){
    amp -=1/rele;
  }
  setSample(0);
return amp;
}
