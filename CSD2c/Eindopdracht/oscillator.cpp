#include "oscillator.h"

// Constructor
Oscillator::Oscillator() {
}

// Destructor
Oscillator::~Oscillator() {
}

void Oscillator::setFrequency(float frequency) {
  this->frequency = frequency;
}

void Oscillator::setAmplitude(float amplitude) {
  this->amplitude = amplitude;
}

float Oscillator::getSample() {
  return sample;
}
