#ifndef _DIST_H_
#define _DIST_H_

#include <iostream>
#include "math.h"
using namespace std;

class Distortion {
public:
  Distortion();
  ~Distortion();

  float getSample(float input);

protected:
  float distorted_sample;

};

#endif
