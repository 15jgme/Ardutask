#pragma once

#include "Taskmanager.h"

#if defined(_WIN32) 
#if defined(NATIVE)

HWND hwndTimer;   // handle to window for timer messages 
MSG msg;          // message structure 
 
void runMsgPump()
{
    while (GetMessage(&msg, // message structure 
        NULL,           // handle to window to receive the message 
            0,           // lowest message to examine 
            0))          // highest message to examine 
    { 

        // Post WM_TIMER messages to the hwndTimer procedure. 

        if (msg.message == WM_TIMER) 
        { 
            msg.hwnd = hwndTimer; 
        } 

        TranslateMessage(&msg); // translates virtual-key codes 
        DispatchMessage(&msg);  // dispatches message to window 
        break;
    }
}


#endif
#endif