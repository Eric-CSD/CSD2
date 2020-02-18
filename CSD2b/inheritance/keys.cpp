#include "keys.h"
using namespace std;
//constructor and destructor

Keys::Keys(string name) : Instrument(name)
{
  type = "Keys";
}
Keys::~Keys()
{
}

// methods
void Keys  ::selectPreset(string preset)
{
  cout << "Selecting keys preset:" << preset << endl;
}
