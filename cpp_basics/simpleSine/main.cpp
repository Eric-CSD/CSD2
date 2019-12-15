#include <iostream>
#include "synthesizer.h"
/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */
int main(int argc,char **argv){
  Synthesizer AMSynth;
  AMSynth.AMSynth(1, 40,1, 880);
  Synthesizer addSynth2;
  addSynth2.addSynth(1, 400, 2, 500);
  return 0;
} // main()
