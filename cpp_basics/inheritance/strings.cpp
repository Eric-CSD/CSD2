#include "strings.h"
using namespace std;
//constructor and destructor

Strings::Strings(string name) : Instrument(name)
{
  type = "Strings";
}
Strings::~Strings()
{
}

// methods
void Strings  ::tune()
{
  cout << name << " is being tuned.\n";
}
