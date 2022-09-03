#if defined(_WIN32) 
#if defined(NATIVE)

#include <windowsTimer.h>

int WindowsTimer::setTimer(int freq)
{
    TIMERPROC Timerproc;
    auto res = SetTimer(NULL,                // handle to main window 
                        label,                   // timer identifier 
                        int(1/rate),                     // 5-second interval 
                        (TIMERPROC) &myTimerProc); // timer callback
    return 1;
    // Note: need to fill in timerproc
    // https://docs.microsoft.com/en-us/windows/win32/winmsg/using-timers#creating-a-timer
}

#endif
#endif