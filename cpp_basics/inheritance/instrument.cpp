#include <iostream>
#include "instrument.h"
using namespace std;

Instrument::Instrument(string name)
{
  cout << "Instrument added to ensemble: "
  << name << "\n";
  this->name = name;
}

Instrument::~Instrument()
{
}

void Instrument::play()
{
  sound = "*" + name + " Sounds*. " + pitchDesc;
  cout << sound << endl;

}

void Instrument::pitch(int pitch)
{
  if (pitch == 0)
  {
    pitchDesc = "Low pitch range instrument of type: " +type;
  } else if (pitch == 1)
  {
    pitchDesc = "Middle pitch range instrument of type: " +type;
  } else
  {
    pitchDesc = "High pitch range instrument of type: " +type;
  }

}
