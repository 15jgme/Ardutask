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

#if defined(__linux__)
#if defined(NATIVE)
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
// #include "Linux_io_service_wrapper.hpp"
#include <io_define.h>
#include <iostream>

// Linux_io_service_wrapper * lio = new Linux_io_service_wrapper();
// boost::asio::io_service io;
// lio->setIO(*io);

void runMsgPump()
{
    // lio->run();
    // std::cout<<io.run()<<std::endl;
    std::cout<<"asjdaskdjh"<<std::endl;
    io.run_one();
}
#endif
#endif