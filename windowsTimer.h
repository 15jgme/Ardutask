#pragma once

#include <MultiTime.h>
#include <timerLabel.h>

class Taskmanager;
#include <windows.h>
#include <map>

class WindowsTimer : public MultiTime
{
public:
  int setTimer(float rate_s);
  WindowsTimer(int (*fn_cb_s)(), int label_s);
  static void CALLBACK myTimerProc(
    HWND unnamedParam1,
    UINT unnamedParam2,
    UINT_PTR idEvent,
    DWORD unnamedParam4);
  static std::map<UINT_PTR, WindowsTimer*> m_CMyClassMap; //declaration

};

