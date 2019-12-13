#include "saw.h"
#include "math.h"

Saw::Saw() : Oscillator() {
  cout << "Saw constructor" << endl;
}

Saw::~Saw() {
  cout << "Saw destructor" << endl;
}

// sine wave formula
void Saw::tick(double samplerate) {
  phase += frequency / samplerate;
  sample = ((fmod(phase,1)*2)-1)*amplitude;
}
