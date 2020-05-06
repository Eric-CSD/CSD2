#include "clock.h"
#include "math.h"

Clock::Clock(std::string name)
{
    this->name = name;
}

void Clock::tick(float sample)
{
    this->sample = sample;
    sample++;
}
