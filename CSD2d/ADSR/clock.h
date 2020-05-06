#ifndef _CLOCK_H_
#define _CLOCK_H_
#include <iostream>
using namespace std;

class Clock
{
    //Name of the clock ticker
    //observer for tick
    std::string name;
    float sample;
public:
    Clock(std::string n);
    void tick(float sample);
    virtual void Update(float sample) = 0;
};

#endif
