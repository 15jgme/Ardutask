#include "MultiTime.h"
#include "helpers.h"
#include <iostream> //remove

MultiTime::MultiTime(void (*fn_cb_s)(), int label_s)
{
    fn_cb = fn_cb_s;
    label = label_s;
}

int MultiTime::timerCallback()
{
    fn_cb();
    return 1;
}