#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "circBuffer.h"
#include "stutterEffect.h"
#include "osc.h"
/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */
//osc variables
float oscLfoSpeedR;
float oscLfoSpeedL;
float stutterDelay;

//stutter bufferlength
int stutterOn;
float stutterTrigger = 0;
float ampPhase = 0;
int ampPhaseTick= 0;

// subclass OSC into a local class so we can provide our own callback
class localOSC : public OSC
{
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  // osc "paramater" name
  string msgpath=path;
    // if osc "parameter" name is /oscLfoSpeedR
    if(!msgpath.compare("/oscLfoSpeedR")){
      oscLfoSpeedR = argv[0]->f;
    }
    // if osc "parameter" name is /oscLfoSpeedL
    if(!msgpath.compare("/oscLfoSpeedL")){
      oscLfoSpeedL = argv[0]->f;
    }
    // if osc "parameter" name is /stutterDelay
    if(!msgpath.compare("/stutterDelay")){
      stutterDelay = argv[0]->f;
    }
    // if osc "parameter" name is /stutterOn
    if(!msgpath.compare("/stutterOn")){
      stutterOn = argv[0]->f;
    }
    return 0;
  }
};

// preset settings
float delayTime = 500;
int stutter = 0;

int main(int argc,char **argv)
{
  // create a JackModule instance
  JackModule jack;

  // init the jack, use program name as JACK client name
  jack.init(argv[0]);
  float sampleRate = jack.getSamplerate();

  // setting up OSC server
  localOSC osc;
  string serverport="10024";
  osc.init(serverport);
  osc.set_callback("/oscLfoSpeedR","f");
  osc.set_callback("/oscLfoSpeedL","f");
  osc.set_callback("/stutterDelay","f");
  osc.set_callback("/stutterOn","f");
  osc.start();
  cout << "Listening on port " << serverport << endl;

  // create the stutterEffect instance
  stutterEffect stutterEffect(sampleRate, delayTime, stutter);

  // assign a function to the JackModule::onProces
  jack.onProcess = [&stutterEffect](jack_default_audio_sample_t *inBuf,
  jack_default_audio_sample_t *outBufL, jack_default_audio_sample_t *outBufR, jack_nframes_t nframes)
  {
    for(unsigned int i = 0; i < nframes; i++)
    {
      if(i==0){
        stutterTrigger=fmod((stutterTrigger+1),2*(((delayTime/1000)*44100)/256));
      }
      // write the output

      ampPhase =abs(sin((ampPhaseTick/((delayTime/1000)*44100))*M_PI));
      ampPhaseTick +=1;
      if(stutter ==0){
        stutterEffect.write(inBuf[i]);
        outBufL[i] = inBuf[i];
        outBufR[i] = inBuf[i];
      } else  {
        stutterEffect.write(inBuf[i]);
        if(stutterTrigger<((delayTime/1000)*44100)/256){
        outBufL[i] = stutterEffect.readLeft()*ampPhase;
        outBufR[i] = stutterEffect.readRight()*ampPhase;
      } else {
        stutterEffect.writeNoLoop(inBuf[i]);
        outBufL[i] = inBuf[i]*ampPhase;
        outBufR[i] = inBuf[i]*ampPhase;
      }

      }
    }
    return 0;
  };

  jack.autoConnect();

  //keep the program running and listen for user input, q = quit
  std::cout << "\n\nPress 'q' to quit.\n";
  std::cout << "Press 's1' to turn on stutter, press 's0' to turn it off.\n";
  std::cout << "Press 'l' change stutter length.\n";
  bool running = true;
  while (running)
  {
    if (stutterOn == 1){
      stutter = stutterOn;
      stutterEffect.setStutter(stutter);
      delayTime = stutterDelay;
      stutterEffect.setTime(delayTime);
    } else {
      stutter = stutterOn;
      stutterEffect.setStutter(stutter);

    }
    // switch (std::cin.get())
    // {
    //   // user input for quiting and changing settings
    //   case 'q':
    //     running = false;
    //     jack.end();
    //     break;
    //   case 's':
    //     int newStutter;
    //     std::cin >> newStutter;
    //     stutter = newStutter;
    //     stutterEffect.setStutter(stutter);
    //     break;
    //   case 'l':
    //     float newTime;
    //     std::cin >> newTime;
    //
    //     delayTime = newTime;
    //     stutterEffect.setTime(delayTime);
    //     stutterEffect.setTime(newTime);
    //     break;
    //   }
  }

  //end the program
  return 0;
} // main()
