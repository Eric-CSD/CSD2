#include "distortion.h"


// Constructor
Distortion::Distortion(){
}

// Destructor
Distortion::~Distortion(){
}

float Distortion::getSample(float input){
  return distorted_sample = (2/M_PI) * atan(input);
}
