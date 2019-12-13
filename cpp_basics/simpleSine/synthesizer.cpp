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


int Synthesizer::additiveSynthesis(float osc1, float freq1, float osc2, float freq2)
{
  JackModule jack;
  jack.init();
  double samplerate = jack.getSamplerate();
    Saw oscillator1;
    Square oscillator2;
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

  std::cout << "\n\nPress 'q' when you want to quit the program.\n";
  bool running = true;
  while (running){
    switch (std::cin.get()) {
      case 'q':
        running = false;
        jack.end();
        break;
    }
}
  return 0;
}

int Synthesizer::AMSynth(float freq1, float freq2)
{
  JackModule jack;
  jack.init();
  double samplerate = jack.getSamplerate();
    Sine oscillator1;
    Sine oscillator2;
    oscillator1.setFrequency(freq1);
    oscillator2.setFrequency(freq2);
    // assign a function to the JackModule::onProces
    jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
       jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

      for(unsigned int i = 0; i < nframes; i++) {
        outBuf[i] = oscillator1.getSample() + ((oscillator2.getSample()+1)/2);
        oscillator1.tick(samplerate);
        oscillator2.tick(samplerate);
      }
      return 0;
    };
    jack.autoConnect();

  bool running = true;
  while (running){
    switch (std::cin.get()) {
      case 'q':
        running = false;
        jack.end();
        break;
    }
}
  return 0;
}
