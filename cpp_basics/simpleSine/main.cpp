#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "synthesizer.h"
#include "sine.h"
#include "saw.h"

int argc;
char **argv;

void threadFunction()
{
  std::cout<< argv[0];
  Synthesizer addSynth;
    addSynth.additiveSynthesis(1, 200, 2, 400, argv[0]);
}
/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */
#define PI_2 6.28318530717959
int main(int argc,char **argv)
{
  thread fun_1(threadFunction);
  fun_1.join();
return 0;
  // Synthesizer addSynth;
  //   addSynth.additiveSynthesis(1, 200, 2, 400, argv[0]);
  // Synthesizer addSynth2;
  //
  //
  //   addSynth2.additiveSynthesis(1, 800, 2, 1600, argv[0]);

  // create a JackModule instance
  // JackModule jack;
  //
  // // init the jack, use program name as JACK client name
  // jack.init(argv[0]);
  // double samplerate = jack.getSamplerate();
  //
  // Sine sine;
  // Saw saw;
  // sine.setFrequency(200);
  // saw.setFrequency(300);
  //
  // // assign a function to the JackModule::onProces
  // jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
  //    jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {
  //
  //   for(unsigned int i = 0; i < nframes; i++) {
  //     outBuf[i] = sine.getSample() + saw.getSample();
  //     sine.tick(samplerate);
  //     saw.tick(samplerate);
  //   }
  //   return 0;
  // };
  //
  // jack.autoConnect();
  //keep the program running and listen for user input, q = quit
  // std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  // bool running = true;
  // while (running)
  // {
  //   switch (std::cin.get()) {
  // 	  case 'q':
  //   		running = false;
  // 			// jack.end();
  //       break;
  //   }
  // }
  //end the program
  return 0;
} // main()
