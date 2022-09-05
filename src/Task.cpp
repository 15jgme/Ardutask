#include <Task.h>

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