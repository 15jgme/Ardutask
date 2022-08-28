#include <MultiTime.h>
#ifndef STMTIMER_H
#define STMTIMER_H

class STMTimer : public MultiTime
{
public:
    int setTimer(int rate);
};

#endif