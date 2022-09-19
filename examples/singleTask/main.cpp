#include "Ardutask.h"
#include "dummyTask.hpp"
#include "helpers.h"

Taskmanager* taskMan;

#ifdef EMBEDDED
#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  taskMan = new Taskmanager();
  taskMan->addtask(&dt);
}

void loop() {
  // put your main code here, to run repeatedly:
  taskMan->run();
}
#endif

#ifdef NATIVE
#include <iostream>
#include <windows.h>
#include <stdio.h>

bool firstRun = true;
// MSG msg;

int main()
{
  while(true)
  {
    if(firstRun)
    {
      taskMan = new Taskmanager();
      taskMan->addtask(&dt);
      firstRun = false;
    }
    // log_m("begin");
    taskMan->run();
    
    runMsgPump();
  }
}

#endif