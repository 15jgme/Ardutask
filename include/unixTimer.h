#pragma once

#include <stdio.h>
#include <signal.h>
#include <MultiTime.h>
#include <timerLabel.h>

class Taskmanager;

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

class UnixTimer : public MultiTime
{
  void linux_callback_wrapper();
  boost::asio::deadline_timer * t;

public:
  int setTimer(float rate_s);
  UnixTimer(void (*fn_cb_s)(), int label_s);
  ~UnixTimer();
};

