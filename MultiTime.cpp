#include "MultiTime.h"
#include "helpers.h"
#include <iostream> //remove

MultiTime::MultiTime(int (*fn_cb_s)(), int label_s)
{
    fn_cb = fn_cb_s;
    fn_cb(); //Runs here

    label = label_s;
}

int MultiTime::timerCallback()
{
    // This code is reached! 
    fn_cb(); //Not here
    return 1;
}