#include "sine.h"
#include "math.h"

Sine::Sine() : Oscillator() {
}

Sine::~Sine() {
}

// sine wave formula
void Sine::tick(double samplerate) {
  phase += frequency / samplerate;
  sample = amplitude * (sin(phase * PI_2));
}
