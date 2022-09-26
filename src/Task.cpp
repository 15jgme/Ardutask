#include "Task.h"
#include <iostream>

Task::Task(float rate_des)
{
    rate_hz = rate_des;
}

bool Task::updateShouldRun(int dynamicDivisor)
{
    counter++;
    if(counter >= (divisor*dynamicDivisor))
    {
        counter = 0;
        return true;
    }else{
        return false;
    }
}