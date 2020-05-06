#pragma once
#include <vector>
#include <list>
#include "clock.h"

class subject
{
    //Lets keep a track of all the clocks we have observing
    std::vector<Clock*> list;

public:
    void Attach(Clock *clock);
    void Detach(Clock *clock);
    void Notify(float sample);
  };
