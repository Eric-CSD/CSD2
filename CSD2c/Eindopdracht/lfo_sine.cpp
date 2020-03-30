#include "lfo_sine.h"

// Constructor
Lfo_sine::Lfo_sine() : Oscillator() {
}

// Destructor
Lfo_sine::~Lfo_sine() {
}

// sine wave formula made so it moves between 0 and 1
void Lfo_sine::tick(double samplerate) {
  phase += frequency / samplerate;
  sample = (0.5 * (sin(phase * PI_2)) + 0.5);
}
