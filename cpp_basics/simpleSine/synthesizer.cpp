#include <iostream>
#include "jack_module.h"
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
//Additive Synthesizer with 2 oscillators
int Synthesizer::addSynth(float osc1, float freq1, float osc2, float freq2)
{
  double  amplitude = 0;
  JackModule jack;
  jack.init();
  double samplerate = jack.getSamplerate();
    Square oscillator1;
    Saw oscillator2;
    oscillator1.setFrequency(freq1);
    oscillator2.setFrequency(freq2);
    jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
       jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

      for(unsigned int i = 0; i < nframes; i++) {
        outBuf[i] = (oscillator1.getSample() + oscillator2.getSample())*amplitude;
        oscillator1.tick(samplerate);
        oscillator2.tick(samplerate);
      }
      return 0;
    };
    jack.autoConnect();
    while (amplitude<1){
      amplitude += 0.000000002;
    }
    while (amplitude>0){
      amplitude -= 0.000000002;
    }
    jack.end();
  return 0;
}
//AM Synthesizer with 2 sine oscillators
int Synthesizer::AMSynth(float osc1, float freq1, float osc2, float freq2)
{
  double  amplitude = 0;
  JackModule jack;
  jack.init();
  double samplerate = jack.getSamplerate();
    Sine oscillator1;
    Sine oscillator2;
    oscillator1.setFrequency(freq1);
    oscillator2.setFrequency(freq2);
    jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
       jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

      for(unsigned int i = 0; i < nframes; i++) {
        outBuf[i] = ((oscillator1.getSample() * ((oscillator2.getSample())+oscillator2.getAmplitude())/2)*amplitude)*20;
        oscillator1.tick(samplerate);
        oscillator2.tick(samplerate);
      }
      return 0;
    };
    jack.autoConnect();
    while (amplitude<1){
      amplitude += 0.000002;
    }
    while (amplitude>0){
      amplitude -= 0.000000005;
    }
    jack.end();
  return 0;
}
