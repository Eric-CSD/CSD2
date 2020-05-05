#include "sine.h"
#include "math.h"

Sine::Sine() : Oscillator() {
}

Sine::~Sine() {
}

// sine wave formula
double Sine::sine() {

  tick();
  sinoid=(getSample()*frequency)/samplerate;
  sinoid= amplitude * (sin(sinoid * (M_PI*2)));
  return sinoid;

}
