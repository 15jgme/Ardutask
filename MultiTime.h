#pragma once

typedef void (*callback)();
class MultiTime
{
protected:
    float rate; //Hz
    callback fn_cb;
    int label;
public:
    MultiTime(void(*fn_cb_s)(), int label_s);
    virtual int setTimer(float rate_s) = 0;
    int timerCallback();
};
