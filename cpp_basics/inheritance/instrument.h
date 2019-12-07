#ifndef _INSTRUMENT_H_
#define _INSTRUMENT_H_
#include <iostream>
using namespace std;

class Instrument
{
public:
  Instrument(string name);
  ~Instrument();
  void play();
  void pitch(int pitch);
protected:
  string pitchDesc;
  string sound;
  string name;
  string type;
  string preset;
};

#endif
