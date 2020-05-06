
#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "generator.h"
#include "sine.h"
#include "oscillator.h"
#include "synthesizer.h"
#include "envelope.h"


/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */



int main(int argc,char **argv)
{
  // create a JackModule instance
  JackModule jack;
  Synthesizer synthesizer;
  //ADSR initialized values and noteOff message + frequency
  int note = 0;
  float a = 0;
  float d = 0;
  float s = 0;
  float r = 0;
  float f = 0;

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);

  //assign a function to the JackModule::onProces
  jack.onProcess = [&synthesizer,&note](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      if (note == 0){
        outBuf[i]= synthesizer.noteOn();
      };
      if (note == 1){
        outBuf[i]= synthesizer.noteOff();
      }
      // outBuf[i] = amplitude * sin(phase * PI_2 );
      // phase += frequency / samplerate;
    }

    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  std::cout << "Press 's' to start or stop the note.\n";
  std::cout << "Press 'a' to set new envelope.\n";
  std::cout << "Press 'w' to set a new pitch.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case 'q':
        running = false;
        jack.end();
        break;
      case 's':
        note =(1+note)%2;
        break;
      case 'a':
        std::cout << "Attack in milliseconds:\n";
        std::cin>>a;
        std::cout << "Decay in milliseconds:\n";
        std::cin>>d;
        std::cout << "Sustain in amplitude (0-1):\n";
        std::cin>>s;
        std::cout << "Release in milliseconds:\n";
        std::cin>>r;
        synthesizer.setEnvelope(a,d,s,r);
        break;
      case 'w':
        std::cout << "Frequency in Hz:\n";
        std::cin>>f;
        synthesizer.setPitch(f);
        break;
    }
  }

  //end the program
  return 0;
} // main()
