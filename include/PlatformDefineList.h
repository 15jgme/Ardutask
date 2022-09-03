/* This file defines the timerTypes based on the 
type of system. Tries to ensure easy crossplatform. */

#if defined(STM32F405xx)
    #include <STMTimer.h>
    typedef STMTimer timerType;
#elif defined(_WIN32)
    #if defined(NATIVE)
        #include <windowsTimer.h>
        typedef WindowsTimer timerType;
    #endif
#endif
