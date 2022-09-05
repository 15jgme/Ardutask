#pragma once

#include <MultiTime.h>
#include <timerLabel.h>

class Taskmanager;
#include <windows.h>

class WindowsTimer : public MultiTime
{
public:
    int setTimer(float rate_s);
    WindowsTimer(int (*fn_cb_s)(), int label_s);
    void CALLBACK myTimerProc(
      HWND unnamedParam1,
      UINT unnamedParam2,
      UINT unnamedParam3,
      DWORD unnamedParam4){timerCallback();}

};

