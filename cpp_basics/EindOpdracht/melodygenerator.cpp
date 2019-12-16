#include "synthesizer.h"
#include "melodygenerator.h"
#include <random>
/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */
 Melodygenerator::Melodygenerator() {
 }

 Melodygenerator::~Melodygenerator() {
 }

 void Melodygenerator::playAM(int amtOfNotes) {
   std::random_device dev;
       std::mt19937 rng(dev());
   int nextNote = 0;
   int note = 0;
   Synthesizer AMSynth;
   while (note < amtOfNotes){
     std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100);
     nextNote =dist100(rng);
     std::cout<< "Osc1: " << (50+(nextNote*5)) << "   Osc2: " << 20+(20*(nextNote%50)) << endl;
     AMSynth.AMSynth(1, 50+(nextNote*5),1, 20+(100*(nextNote%10)));
     note += 1;
   }
 }

 void Melodygenerator::playAdd(int amtOfNotes) {
   std::random_device dev;
       std::mt19937 rng(dev());
   float nextNote = 0;
   float nextNote2 =0;
   int note = 0;
   Synthesizer addSynth;
   while (note < amtOfNotes){
     std::uniform_int_distribution<std::mt19937::result_type> dist7(1,7);
     switch (dist7(rng)){
      case 1:
        nextNote =60;
        break;
      case 2:
        nextNote =62;
        break;
      case 3:
        nextNote =64;
        break;
      case 4:
        nextNote =65;
        break;
      case 5:
        nextNote =67;
        break;
      case 6:
        nextNote =69;
        break;
      case 7:
        nextNote =71;
        break;
     }
     std::uniform_int_distribution<std::mt19937::result_type> dist72(1,7);
     switch (dist72(rng)){
      case 1:
        nextNote2 =72;
        break;
      case 2:
        nextNote2 =74;
        break;
      case 3:
        nextNote2 =76;
        break;
      case 4:
        nextNote2 =77;
        break;
      case 5:
        nextNote2 =79;
        break;
      case 6:
        nextNote2 =81;
        break;
      case 7:
        nextNote2 =83;
        break;
     }
     nextNote =(440. * exp(.057762265 * (nextNote - 69.)));
     nextNote2 =(440. * exp(.057762265 * (nextNote2 - 69.)));
     std::cout<< "Osc1: " << nextNote << "   Osc2: " << nextNote2 << endl;
     addSynth.addSynth(1, nextNote,1, nextNote2);
     note += 1;
   }
 }
