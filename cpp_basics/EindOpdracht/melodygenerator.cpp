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
   int nextNote = 0;
   int note = 0;
   Synthesizer addSynth;
   while (note < amtOfNotes){
     std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100);
     nextNote =dist100(rng)+5;
     std::cout<< "Osc1: " << (nextNote*6) << "   Osc2: " << (nextNote*9) << endl;
     addSynth.addSynth(1, (nextNote*6),1, (nextNote*9));
     note += 1;
   }
 }
