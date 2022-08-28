#include <MultiTime.h>
#include <windows.h>

#ifndef WINDOWSTIMER_H
#define WINDOWSTIMER_H

class WindowsTimer : public MultiTime
{
public:
    int setTimer(int rate);
    void CALLBACK myTimerProc(
      HWND unnamedParam1,
      UINT unnamedParam2,
      UINT unnamedParam3,
      DWORD unnamedParam4){timerCallback()}

};

#endif