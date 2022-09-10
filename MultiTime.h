#pragma once

class MultiTime
{
protected:
    float rate; //Hz
    int (*fn_cb)();
    int label;
public:
    MultiTime(int(*fn_cb_s)(), int label_s);
    virtual int setTimer(float rate_s) = 0;
    int timerCallback();
};
