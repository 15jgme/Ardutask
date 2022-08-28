#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#define TASK_LIMIT 24 // Current limit to 24 tasks
#define TASK_STACK_SIZE 24 // Current limit to 24 tasks can be stacked

#include <Task.h>
#include <MultiTime.h>

class Taskmanager
{

Task taskList[TASK_LIMIT]; // List of pointers to task objects. This is filled as tasks are added
int todoStack[TASK_STACK_SIZE]; // List of tasks to do, low indexed tasks will be completed first
short todoStackSize = 0; // Current number of tasks in the todo list
short tasksUsed = 0; // Current number of task slots used

/* Initialize all timers */
STMTimer HRT1 = STMTimer(HRT1, self);
timerType HRT2 = timerType(HRT2, self);
timerType HRT3 = timerType(HRT3, self);
timerType LRT1 = timerType(LRT1, self);
timerType LRT2 = timerType(LRT2, self);


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