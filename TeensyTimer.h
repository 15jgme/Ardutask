#pragma once

#include "MultiTime.h"
#include "timerLabel.h"
#include "helpers.h"
#include <Arduino.h>
// class MultiTime;
class Taskmanager;

class TeensyTimer : public MultiTime
{
    IntervalTimer * tim_ptr;
public:
    int setTimer(float rate_s);
    TeensyTimer(void (*fn_cb_s)(), int label_s);
};
