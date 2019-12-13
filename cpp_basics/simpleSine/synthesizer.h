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
int additiveSynthesis(float osc1, float freq1, float osc2, float freq2);
int AMSynth(float freq1, float freq2);
protected:
};

#endif
