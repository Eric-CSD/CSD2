#include "sine.h"
using namespace std
Sine::Sine(float frequency)
{
  this->frequency = frequency;
  cout << "Sine - constructor\n";
}

Sine::~Sine()
{
  cout << "Sine - destructor\n";
}

float Sine::getSample()
{
  return sample;
}

void Sine::tick()
{
  cout << "tick\n";
}

void Sine::setFrequency(float frequency);
{
  this-> frequency = frequency;
}

float Sine::getFrequency()
{
  return frequency;
}
