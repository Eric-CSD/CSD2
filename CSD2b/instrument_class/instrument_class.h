using namespace std;

class Instrument
{
public:
  Instrument(int instr);
  ~Instrument();
  int play();
private:
  string sound;
};
