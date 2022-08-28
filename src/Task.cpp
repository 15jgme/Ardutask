#include <Task.h>

bool Task::shouldRun(int trigger)
{
    if(counter >= trigger)
    {
        return true;
    }else{
        return false;
    }
}