#pragma once 

#define TASK_LIMIT 24 // Current limit to 24 tasks
#define TASK_STACK_SIZE 24 // Current limit to 24 tasks can be stacked

#include "Task.h"
#include "timerLabel.h"
#include "PlatformDefineList.h"

enum timerLabel;

class Taskmanager
{
    static Task* taskList[TASK_LIMIT]; // List of pointers to task objects. This is filled as tasks are added
    volatile static int todoStack[TASK_STACK_SIZE]; // List of tasks to do, low indexed tasks will be completed first

    static int HRT1List[TASK_LIMIT]; // HRT1 arrary list
    static int HRT1List_size; // Size of HRT1 list
    static int HRT2List[TASK_LIMIT]; // HRT2 arrary list
    static int HRT2List_size; // Size of HRT2 list
    static int HRT3List[TASK_LIMIT]; // HRT3 arrary list
    static int HRT3List_size; // Size of HRT3 list
    static int LRT1List[TASK_LIMIT]; // LRT1 arrary list
    static int LRT1List_size; // Size of LRT1 list
    static int LRT2List[TASK_LIMIT]; // LRT2 arrary list
    static int LRT2List_size; // Size of LRT2 list

    static short HRT1_overrun; 
    static short HRT2_overrun;
    static short HRT3_overrun;
    static short LRT1_overrun;
    static short LRT2_overrun;

    /* Gains for dynamic divising */
    static float kp_HRT1;
    static float kp_HRT2;
    static float kp_HRT3;
    static float kp_LRT1;
    static float kp_LRT2;

    float HRT1_freq = 100.0f; // Frequency of HR timer 1, Hz
    float HRT2_freq = 50.0f; // Frequency of HR timer 2, Hz
    float HRT3_freq = 10.0f; // Frequency of HR timer 3, Hz
    float LRT1_freq = 1.0f; // Frequency of LR timer 1, Hz
    float LRT2_freq = 0.1f; // Frequency of LR timer 2, Hz

    volatile static short todoStackSize; // Current number of tasks in the todo list
    short tasksUsed = 0; // Current number of task slots used

public:
    Taskmanager();
    int run();
    int addtask(Task * t);
    int removetask(int ID, int inst);
    /* Declare all timer callbacks */
    static void HRT1_callback();
    static void HRT2_callback();
    static void HRT3_callback();
    static void LRT1_callback();
    static void LRT2_callback();

    /* Initialize all timers */
    timerType HRT1_t = timerType(&HRT1_callback, static_cast<int>(HRT1));
    timerType HRT2_t = timerType(&HRT2_callback, static_cast<int>(HRT2));
    timerType HRT3_t = timerType(&HRT3_callback, static_cast<int>(HRT3));
    timerType LRT1_t = timerType(&LRT1_callback, static_cast<int>(LRT1));
    timerType LRT2_t = timerType(&LRT2_callback, static_cast<int>(LRT2));
    virtual ~Taskmanager(){}
};
