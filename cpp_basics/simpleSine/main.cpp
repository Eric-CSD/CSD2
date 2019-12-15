#include <iostream>
#include "synthesizer.h"
#include <thread>
/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */
int main(int argc,char **argv){
  Synthesizer addSynth;
  addSynth.AMSynth(200, 440);
  Synthesizer addSynth2;
  addSynth2.addSynth(1, 400, 2, 500);
  return 0;
} // main()
