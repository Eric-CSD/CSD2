#include "percussion.h"
using namespace std;
//constructor and destructor

Percussion::Percussion(string name) : Instrument(name)
{
  type = "Percussion";
}
Percussion::~Percussion()
{
}

// methods
void Percussion::drumSetup()
{
  cout << "Setting up percussion\n";
}
