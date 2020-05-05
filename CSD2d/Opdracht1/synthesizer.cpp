#include <iostream>
#include "jack_module.h"
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "synthesizer.h"
#define PI_2 6.28318530717959

Synthesizer::Synthesizer() {
}

Synthesizer::~Synthesizer() {
}
//Additive Synthesizer with 4 oscillators
int Synthesizer::addSynth(float osc1, float freq1, float osc2, float freq2)
{
  double  ampOsc1 = 0;
  double  ampOsc2 = 0;
  double  ampOsc3 = 0;
  double  ampOsc4 = 0;
  JackModule jack;
  jack.init();
  double samplerate = jack.getSamplerate();
  Square oscillator1;
  Saw oscillator3;
  Saw oscillator2;
  Square oscillator4;
  oscillator1.setFrequency(freq1);
  oscillator2.setFrequency(freq2);
  oscillator3.setFrequency(freq1);
  oscillator4.setFrequency(freq2);
  jack.onProcess = [&](jack_default_audio_sample_t *inBuf,
     jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {

    for(unsigned int i = 0; i < nframes; i++) {
      oscillator1.tick(samplerate);
      oscillator2.tick(samplerate);
      oscillator3.tick(samplerate);
      oscillator4.tick(samplerate);
      outBuf[i] = ampOsc1*(oscillator1.getSample());
      outBuf[i] += ampOsc2*oscillator2.getSample();
      outBuf[i] += ampOsc3*oscillator3.getSample();
      outBuf[i] += ampOsc4*oscillator4.getSample();
      outBuf[i] *= 0.1;
    }
    return 0;
  };
  jack.autoConnect();
  while (ampOsc1<1){
    ampOsc1 += 0.00000001;
  }
  while (ampOsc2<1){
    ampOsc2 += 0.00000001;
  }
  while (ampOsc3<1){
    ampOsc3 += 0.00000001;
  }
  while (ampOsc4<1){
    ampOsc4 += 0.00000001;
  }
  while (ampOsc1>0){
    ampOsc1 -= 0.000000005;
    ampOsc2 -= 0.000000005;
    ampOsc3 -= 0.000000005;
    ampOsc4 -= 0.000000005;
  }
  jack.end();
  return 0;
}
//AM Synthesizer with 2 sine oscillators
int Synthesizer::AMSynth(float osc1, float freq1, float osc2, float freq2)
{
  double  ampOsc1 = 0;
  double  ampOsc2 = 0;
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
      oscillator1.tick(samplerate);
      oscillator2.tick(samplerate);
      outBuf[i] = ampOsc1*(oscillator1.getSample());
      outBuf[i] *= (oscillator2.getSample()+oscillator2.getAmplitude())/2*ampOsc2;
      outBuf[i] *= 5;
    }
    return 0;
  };
  jack.autoConnect();
  while (ampOsc1<1){
    ampOsc1 += 0.000000002;
  }
  while (ampOsc2<1){
    ampOsc2 += 0.000000002;
  }
  while (ampOsc1>0){
    ampOsc1 -= 0.000000001;
    ampOsc2 -= 0.000000001;
  }
  jack.end();
  return 0;
}
