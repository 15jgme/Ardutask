#include "Task.h"

Task::Task(float rate_des)
{
    rate_hz = rate_des;
}

bool Task::updateShouldRun(int dynamicDivisor)
{
    counter++;
    switch (counter >= (divisor*dynamicDivisor))
    {
    case true:
        return true;
        counter = 0;
        break;
    case false:
        return false;
        break;
    }
}