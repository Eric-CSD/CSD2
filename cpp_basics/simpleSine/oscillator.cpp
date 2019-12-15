#include "oscillator.h"

Oscillator::Oscillator() {
  cout << "Oscillator constructor" << endl;
}

Oscillator::~Oscillator() {
  cout << "Oscillator destructor" << endl;
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
