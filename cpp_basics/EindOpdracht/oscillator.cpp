#include "oscillator.h"

Oscillator::Oscillator() {
}

Oscillator::~Oscillator() {
}

void Oscillator::setFrequency(float frequency) {
  this->frequency = frequency;
}
float Oscillator::getAmplitude(){
  return amplitude;
}
float Oscillator::getSample() {
  return sample;
}
