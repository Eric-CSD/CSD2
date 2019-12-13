#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "synthesizer.h"
#define PI_2 6.28318530717959

Synthesizer::Synthesizer() {
  cout << "Synthesizer constructor" << endl;
}

Synthesizer::~Synthesizer() {
  cout << "Synthesizer destructor" << endl;
}


int Synthesizer::additiveSynthesis(int osc1, int freq1, int osc2, int freq2,char* argv)
{
  JackModule jack;
  jack.init(argv);
  double samplerate = jack.getSamplerate();
  Saw oscillator1;
  Sine oscillator2;
  // if (osc1==1){
  //   Sine oscillator1;
  // } else if (osc1==2){
  //   Saw oscillator1;
  // } else if (osc1==3){
  //   Square oscillator1;
  // }
  //
  // if (osc2==1){
  //   Sine oscillator2;
  // } else if (osc2==2){
  //   Saw oscillator2;
  // } else if (osc2==3){
  //   Square oscillator2;
  // }
  oscillator1.setFrequency(freq1);
  oscillator2.setFrequency(freq2);
  // assign a function to the JackModule::onProces
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      outBuf[i] = oscillator1.getSample() + oscillator2.getSample();
      oscillator1.tick(samplerate);
      oscillator2.tick(samplerate);
    }
    return 0;
  };
  jack.autoConnect();
  // JackModule jack;
  //
  // // init the jack, use program name as JACK client name
  // jack.init(argv);
  // double samplerate = jack.getSamplerate();
  //
  // Sine sine;
  // Saw saw;
  // sine.setFrequency(200);
  // saw.setFrequency(300);

  // assign a function to the JackModule::onProces
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
  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get()) {
      case 'q':
        running = false;
        // jack.end();
        break;
    }
  }
  return 0;
}
