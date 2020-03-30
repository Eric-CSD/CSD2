#include "sine.h"

// Constructor
Sine::Sine() : Oscillator() {
}

// Destructor
Sine::~Sine() {
}

// sine wave formula
void Sine::tick(double samplerate) {
  phase += frequency / samplerate;
  sample = amplitude * (sin(phase * PI_2));
}
