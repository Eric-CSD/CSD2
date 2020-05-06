#include "subject.h"
#include <algorithm>

using namespace std;
//methods for adding to the observer list

void subject::Attach(Clock *clock)
{
    list.push_back(clock);
}
void subject::Detach(Clock *clock)
{
    list.erase(std::remove(list.begin(), list.end(), clock), list.end());
}

void subject::Notify(float sample)
{
    for(vector<Clock*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->Update(sample);
        }
    }
}
