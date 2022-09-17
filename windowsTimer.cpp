#if defined(_WIN32) 
#if defined(NATIVE)

#include "windowsTimer.h"
#include "MultiTime.h"
#include <iostream>


std::map<UINT_PTR, WindowsTimer*> WindowsTimer::m_CMyClassMap;  //definition

WindowsTimer::WindowsTimer(int (*fn_cb_s)(), int label_s):MultiTime(*fn_cb_s, label_s)
{

}

void CALLBACK WindowsTimer::myTimerProc(HWND unnamedParam1, UINT unnamedParam2, UINT_PTR idEvent, DWORD unnamedParam4)
{
    m_CMyClassMap[idEvent]->timerCallback();
}

int WindowsTimer::setTimer(float rate_s)
{
    rate = rate_s;
    TIMERPROC Timerproc;
    UINT_PTR id = SetTimer(NULL,                // handle to main window 
                        label,                   // timer identifier change! 
                        int((1/rate)*1000.0f),                     // 5-second interval 
                        (TIMERPROC) &myTimerProc); // timer callback
    
    m_CMyClassMap[id] = this; 
    std::cout<<id<<std::endl;
    return 1;
    // Note: need to fill in timerproc
    // https://docs.microsoft.com/en-us/windows/win32/winmsg/using-timers#creating-a-timer
}

#endif
#endif