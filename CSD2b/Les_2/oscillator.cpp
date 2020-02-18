#include <iostream>
#include "oscillator.h"
using namespace std;

Oscillator::Oscillator(float freq){
  this->freq = freq;
  cout << "Oscillator - Constructor\n";
}

Oscillator::~Oscillator(){
  cout << "Oscillator - Destructor\n";
}

void Oscillator::setFreq(float freq){
  cout << "setFreq";
  if (freq < 0 || freq > 22050){
    cout << "ERROR Frequency stom";
    return;
  }
  else{
    this->freq = freq;
  }
}

float Oscillator::getFreq(){
  cout << "getFreq";
  return freq;
}
