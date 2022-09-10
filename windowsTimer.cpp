#if defined(_WIN32) 
#if defined(NATIVE)

#include "windowsTimer.h"
#include "MultiTime.h"
#include <iostream>

WindowsTimer::WindowsTimer(int (*fn_cb_s)(), int label_s):MultiTime(*fn_cb_s, label_s)
{

}

int WindowsTimer::setTimer(float rate_s)
{
    rate = rate_s;
    TIMERPROC Timerproc;
    auto res = SetTimer(NULL,                // handle to main window 
                        label,                   // timer identifier change! 
                        int(1/(rate*1000.0f)),                     // 5-second interval 
                        (TIMERPROC) &myTimerProc); // timer callback
    std::cout<<res<<std::endl;
    return 1;
    // Note: need to fill in timerproc
    // https://docs.microsoft.com/en-us/windows/win32/winmsg/using-timers#creating-a-timer
}

#endif
#endif