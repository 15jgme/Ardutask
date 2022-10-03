#if defined(__linux__) 
#if defined(NATIVE)

#include "unixTimer.h"
#include "MultiTime.h"
#include "io_define.h"
#include <iostream>

// static boost::asio::io_service io;

UnixTimer::UnixTimer(void (*fn_cb_s)(), int label_s):MultiTime(*fn_cb_s, label_s)
{
}

void UnixTimer::linux_callback_wrapper()
{
    std::cout<<"bizz"<<std::endl;
    fn_cb();
    t->expires_at(t->expires_at() + boost::posix_time::seconds(int(1.0f/rate)));
    t->async_wait(boost::bind(&UnixTimer::linux_callback_wrapper, this));
}

int UnixTimer::setTimer(float rate_s)
{
    rate = rate_s;
    t = new boost::asio::deadline_timer(io, boost::posix_time::seconds(int(1.0f/rate)));
    t->async_wait(boost::bind(&UnixTimer::linux_callback_wrapper, this));
    return 1;
}

UnixTimer::~UnixTimer()
{
    delete t;
}

#endif
#endif