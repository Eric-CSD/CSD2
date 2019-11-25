#include <iostream>
#include "instrument_class.h"
using namespace std;


Instrument::Instrument(int instr)
{
  if(instr == 1){
    sound = "DrumDrumDrum";
  }
  else{
    sound = "Basssszszs";
  }
}

Instrument::~Instrument()
{
  cout << "Instruments - Destructor\n";
}

int Instrument::play()
{
  cout << sound << endl;
  return 0;
}
