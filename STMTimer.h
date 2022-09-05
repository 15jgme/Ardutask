#pragma once

#include "MultiTime.h"
#include "timerLabel.h"
// class MultiTime;
class Taskmanager;

class STMTimer : public MultiTime
{
public:
    int setTimer(float rate_s);
    STMTimer(int (*fn_cb_s)(), int label_s);
};
