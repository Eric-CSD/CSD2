#ifndef _SYNTH_H_
#define _SYNTH_H_

#include <iostream>
using namespace std;

class Synthesizer {
public:
  //Constructor and destructor
  Synthesizer();
  ~Synthesizer();
int argc;
char **argv;
int additiveSynthesis(int osc1, int freq1, int osc2, int freq2, char* argv);
protected:
};

#endif
