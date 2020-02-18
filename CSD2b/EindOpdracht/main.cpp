#include <iostream>
#include "melodygenerator.h"
#include "synthesizer.h"
/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

 //User interface for SynthSong
int main(int argc,char **argv){
bool program = true;
int noteAmt = 0;
Melodygenerator melody;
while (program){
  std::cout << "\nWelcome to Super SynthSong!\n\n";
  std::cout << "Enter 1 to play AM Synth Song\n";
  std::cout << "Enter 2 to play Additive Synth Song\n";
  std::cout << "Press q to exit\n";
  bool running = true;
  while (running)
  {
    switch (std::cin.get())
    {
      case '1':
        running = false;
        std::cout << "\nHow many notes do you want to play?\n";
        std::cin >> noteAmt;
        while (!cin.good())
        {
          cin.clear();
          cin.ignore(INT_MAX, '\n');
          std::cout << "Enter a valid number!\n";
        }
        melody.playAM(noteAmt);
        break;
      case '2':
        running = false;
        std::cout << "\nHow many notes do you want to play?\n";
        std::cin >> noteAmt;
        while (!cin.good())
        {
          cin.clear();
          cin.ignore(INT_MAX, '\n');
          std::cout << "Enter a valid number!\n";
        }
        melody.playAdd(noteAmt);
        break;
      case 'q':
        program = false;
        running = false;
        break;
      }
  }
}
} // main()
