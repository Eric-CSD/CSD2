class Oscillator{
public:
  Oscillator(float freq);
  ~Oscillator();
  void setFreq(float freq);
  float getFreq();
private:
  float freq;
};
