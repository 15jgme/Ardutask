#include "STMTimer.h"
#include "MultiTime.h"

STMTimer::STMTimer(void (*fn_cb_s)(), int label_s):MultiTime(*fn_cb_s, label_s)
{
}

int STMTimer::setTimer(float rate_s)
{
    //Fill me
    return 1;
}