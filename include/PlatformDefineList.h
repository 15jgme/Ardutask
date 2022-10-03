#pragma once
/* This file defines the timerTypes based on the 
type of system. Tries to ensure easy crossplatform. */

#if defined(STM32F405xx)
    #include "STMTimer.h"
    // class STMTimer;
    // typedef STMTimer timerType;
    #define timerType STMTimer
#elif defined(TEENSY)
    #include "TeensyTimer.h"
    // class STMTimer;
    // typedef STMTimer timerType;
    #define timerType TeensyTimer
#elif defined(_WIN32)
    #if defined(NATIVE)
        #include "windowsTimer.h"
        // class WindowsTimer;
        // typedef WindowsTimer timerType;
        #define timerType WindowsTimer
    #endif
#elif defined(__linux__)
    #if defined(NATIVE)
        #include "unixTimer.h"
        #define timerType UnixTimer
    #endif
#endif