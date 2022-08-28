/* This file defines the timerTypes based on the 
type of system. Tries to ensure easy crossplatform. */

#if defined(STM32F405xx)
    #define timerType STMTimer
    #include <STMTimer.h>
#elif defined(_WIN32)
    #define timerType WindowsTimer
    #include <windowsTimer.h>
#endif
