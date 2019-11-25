using namespace std;

class Instrument
{
public:
  Instrument(int instr);
  ~Instrument();
  int play();
private:
  int x;
  string sound;
};
