#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#define TASK_LIMIT 24 // Current limit to 24 tasks
#define TASK_STACK_SIZE 24 // Current limit to 24 tasks can be stacked

#include <Task.h>
#include <MultiTime.h>
#include <PlatformDefineList.h>

class Taskmanager
{
Task taskList[TASK_LIMIT]; // List of pointers to task objects. This is filled as tasks are added
int todoStack[TASK_STACK_SIZE]; // List of tasks to do, low indexed tasks will be completed first

Task HRT1List[TASK_LIMIT]; // HRT1 arrary list
int HRT1List_size = 0; // Size of HRT1 list
Task HRT2List[TASK_LIMIT]; // HRT2 arrary list
int HRT2List_size = 0; // Size of HRT2 list
Task HRT3List[TASK_LIMIT]; // HRT3 arrary list
int HRT3List_size = 0; // Size of HRT3 list
Task LRT1List[TASK_LIMIT]; // LRT1 arrary list
int LRT1List_size = 0; // Size of LRT1 list
Task LRT2List[TASK_LIMIT]; // LRT2 arrary list
int LRT2List_size = 0; // Size of LRT2 list

short todoStackSize = 0; // Current number of tasks in the todo list
short tasksUsed = 0; // Current number of task slots used

/* Initialize all timers */
timerType HRT1_t = timerType(HRT1, this);
timerType HRT2_t = timerType(HRT2, this);
timerType HRT3_t = timerType(HRT3, this);
timerType LRT1_t = timerType(LRT1, this);
timerType LRT2_t = timerType(LRT2, this);


public:
Taskmanager(){}
int addtask(Task * t);
int removetask(int ID, int inst);

/* Declare all timer callbacks */
int HRT1_callback();
int HRT2_callback();
int HRT3_callback();
int LRT1_callback();
int LRT2_callback();

};

#endif