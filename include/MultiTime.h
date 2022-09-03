#ifndef MULTITIME_H
#define MULTITIME_H

// #include <PlatformDefineList.h>
// #include <Taskmanager.h>


enum timerLabel {HRT1, HRT2, HRT3, LRT1, LRT2};
class Taskmanager;

class MultiTime
{
protected:
    int rate; //Hz
    Taskmanager * tm_ptr;
public:
    timerLabel label;
    MultiTime(timerLabel label_t, Taskmanager * tm);
    virtual int setTimer(int rate);
    int timerCallback();
};


#endif