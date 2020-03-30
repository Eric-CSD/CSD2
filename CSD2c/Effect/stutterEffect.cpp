#include "stutterEffect.h"
#include "circBuffer.h"
#include <math.h>

stutterEffect::stutterEffect(float sampleRate, float delayTime, int stutter)
{
  // sets size and allocates buffers
  buffL.resetSize(441000);
  buffL.allocateBuffer();
  buffL.setDistanceRW(440999);
  buffR.resetSize(441000);
  buffR.allocateBuffer();
  buffR.setDistanceRW(440999);
  // sets settings
  setSamplerate(sampleRate);
  setTime(delayTime);
  setStutter(stutter);
}

stutterEffect::~stutterEffect(){}

void stutterEffect::write(float inSample)
{
//amount of samples to write in buffer
  stutterTime = delaySize;
  if(stutter==0){
    for(int i = 0; i < stutterTime; i++)
      {
        // write input to buffer
        buffL.write(inSample);
        buffL.incrWriteH();
        buffR.write(inSample);
        buffR.incrWriteH();

        outSampleL = buffL.read();
        buffL.incrReadH();
        outSampleR = buffR.read();
        buffR.incrReadH();
      }
    }else{

    for(int i = 0; i < stutterTime; i++)
      {
      // read output when stutter is on
      outSampleL = buffL.read();
      buffL.incrReadH();

      outSampleR = buffR.read();
      buffR.incrReadH();
    }
  }
}
void stutterEffect::writeNoLoop(float inSample)
{
//amount of samples to write in buffer
  stutterTime = delaySize;
    for(int i = 0; i < stutterTime; i++)
      {
        // write input to buffer
        buffL.write(inSample);
        buffL.incrWriteH();
        buffR.write(inSample);
        buffR.incrWriteH();
      }
}
