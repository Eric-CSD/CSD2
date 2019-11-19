#include <iostream>
using namespace std;

class Instrument
{
public:
  Instrument(int instr){
    if(instr == 1){
      sound = "DrumDrumDrum";
    }
    else{
      sound = "Basssszszs";
    }
  }

  int play()
  {
    cout << sound << endl;
    return 0;
  }
private:
  int x;
  string sound;
};

int main()
{
  Instrument drums(1), bass(2);
  drums.play();
  bass.play();
}
