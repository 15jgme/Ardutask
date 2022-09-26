#if defined(TEENSY)

#include "TeensyTimer.h"
#include "MultiTime.h"

void foo()
{
    digitalWrite(13,HIGH);   
}

TeensyTimer::TeensyTimer(void (*fn_cb_s)(), int label_s):MultiTime(*fn_cb_s, label_s)
{
    fn_cb();
}

int TeensyTimer::setTimer(float rate_s)
{
    tim_ptr = new IntervalTimer();
    // tim_ptr->begin(fn_cb, 1000000);
    tim_ptr->begin(fn_cb, 1000000.0f/rate_s);
    return 1;
}

#endif