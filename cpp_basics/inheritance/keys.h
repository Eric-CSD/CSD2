#include "instrument.h"
using namespace std;

class Keys : public Instrument
{
public:
  //constructor and destructor
  Keys(string name);
  ~Keys();

  // methods
  void selectPreset(string);
};
