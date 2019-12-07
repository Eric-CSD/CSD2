#include <iostream>
#include "strings.h"
#include "keys.h"
#include "percussion.h"
using namespace std;

int main ()
{
  cout << endl;
  Strings strings("Bass");
  Strings strings2("Guitar");
  Keys keys("Keyboard");
  Percussion drums("Drums");
  cout << endl;

  drums.drumSetup();
  keys.selectPreset("Synthesizer");
  strings2.tune();
  strings.tune();
  cout << endl;

  drums.pitch(0);
  keys.pitch(1);
  strings.pitch(0);
  strings2.pitch(2);
  cout << endl;
  
  drums.play();
  keys.play();
  strings.play();
  strings2.play();
  cout << endl;
  // end program
  return 0;
}
