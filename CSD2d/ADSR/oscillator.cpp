#include "oscillator.h"
#include "math.h"

Oscillator::Oscillator() : Generator() {
}

Oscillator::~Oscillator() {
}

void Oscillator::setFrequency(float frequency) {
  this->frequency = frequency;
}
float Oscillator::getAmplitude(){
  return amplitude;
}
