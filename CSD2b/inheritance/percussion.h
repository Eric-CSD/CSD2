#include "instrument.h"
using namespace std;

class Percussion : public Instrument
{
public:
  //constructor and destructor
  Percussion(string name);
  ~Percussion();

  // methods
  void drumSetup();
};
