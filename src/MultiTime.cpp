#include <MultiTime.h>

MultiTime::MultiTime(timerLabel l, Taskmanager * tm)
{
    label = l;
    tm_ptr = tm;
}

int MultiTime::timerCallback()
{
    /* Check which type of timer we are, hit the desired callback accordingly */
    switch(label)
    {
    case HRT1:
        tm_ptr->HRT1_callback();
        break;
    case HRT2:
        tm_ptr->HRT2_callback();
        break;
    case HRT3:
        tm_ptr->HRT3_callback();
        break;
    case LRT1:
        tm_ptr->LRT1_callback();
        break;
    case LRT2:
        tm_ptr->LRT2_callback();
        break;
    default:
        break;
    }
    return 1;
}