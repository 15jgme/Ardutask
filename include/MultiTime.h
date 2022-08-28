#ifndef MULTITIME_H
#define MULTITIME_H

#include <PlatformDefineList.h>
#include <Taskmanager.h>

enum timerLabel {HRT1, HRT2, HRT3, LRT1, LRT2};

class MultiTime
{
    int rate; //Hz
    timerLabel label;
    Taskmanager * tm_ptr;
public:
    MultiTime(timerLabel l, Taskmanager * tm);
    virtual int setTimer(int rate);
    int timerCallback();
};


#endif