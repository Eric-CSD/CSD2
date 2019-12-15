#ifndef _MELGEN_H_
#define _MELGEN_H_

#include <iostream>
using namespace std;

class Melodygenerator {
public:
  //Constructor and destructor
  Melodygenerator();
  ~Melodygenerator();

void playAM(int amtOfNotes);
void playAdd(int amtOfNotes);
};

#endif
