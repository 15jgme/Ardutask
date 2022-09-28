#include "Taskmanager.h"
// #include <MultiTime.h>
#include "helpers.h"
#include <iostream>

/* Initialize statics in cpp at the bequest of the compiler */
int Taskmanager::HRT1List_size = 0;
int Taskmanager::HRT2List_size = 0;
int Taskmanager::HRT3List_size = 0;
int Taskmanager::LRT1List_size = 0;
int Taskmanager::LRT2List_size = 0;
volatile short Taskmanager::todoStackSize = 0;

short Taskmanager::HRT1_overrun = 1;
short Taskmanager::HRT2_overrun = 1;
short Taskmanager::HRT3_overrun = 1;
short Taskmanager::LRT1_overrun = 1;
short Taskmanager::LRT2_overrun = 1;

/* Values for dynamic divising gains */
float Taskmanager::kp_HRT1 = 1.0;
float Taskmanager::kp_HRT2 = 1.0;
float Taskmanager::kp_HRT3 = 1.0;
float Taskmanager::kp_LRT1 = 1.0;
float Taskmanager::kp_LRT2 = 1.0;

int Taskmanager::HRT1List[TASK_LIMIT];
int Taskmanager::HRT2List[TASK_LIMIT];
int Taskmanager::HRT3List[TASK_LIMIT];
int Taskmanager::LRT1List[TASK_LIMIT];
int Taskmanager::LRT2List[TASK_LIMIT];
volatile int Taskmanager::todoStack[TASK_STACK_SIZE];
Task* Taskmanager::taskList[TASK_LIMIT];

Taskmanager::Taskmanager()
{
    HRT1_t.setTimer(HRT1_freq); // Hz
    HRT2_t.setTimer(HRT2_freq); // Hz
    HRT3_t.setTimer(HRT3_freq); // Hz
    LRT1_t.setTimer(LRT1_freq); // Hz
    LRT2_t.setTimer(LRT2_freq); // Hz
}

int Taskmanager::run()
{
    if(todoStackSize > 0)
    {
        taskList[todoStack[0]]->update(); // Run task in stack
        // log_m(std::to_string(todoStackSize).c_str());
        for(int i = 0; i < todoStackSize; i++)
        {
            todoStack[i] = todoStack[i+1];
        }
        todoStackSize--;
    }
    return 1;
}

int Taskmanager::addtask(Task * t)
{
    taskList[tasksUsed] = t;
    taskList[tasksUsed]->init(); // Call initailization of task

    int inst = 1; // Begin with first instance, 1 referes to active
    
    /* Assign instance to task by checking tasks already in list */
    if(tasksUsed > 0) // Only do so if there is more than one item in list
    {
        for(int i = 0; i<tasksUsed; i++) // Navigate all tasks
        {
            if(taskList[tasksUsed]->getID() == taskList[i]->getID()) // Check task ID
            {
                inst++; // Iterate if same ID found
            }
        }
    }
    taskList[tasksUsed]->setInst(inst); // Set instance of task

    int task_loc = tasksUsed; // Local variable
    tasksUsed++; // Increase used tasks
    float taskRate = t->getRate();

    /* Perform timer assignment */
    if(taskRate >= HRT2_freq)
    {
        HRT1List[HRT1List_size] = task_loc;
        HRT1List_size++;
        int div = HRT1_freq/taskRate > float(int(HRT1_freq/taskRate)) ? int(HRT1_freq/taskRate)+1 : int(HRT1_freq/taskRate);
        t->setDivisor(div);
    } else if (HRT2_freq >= taskRate && taskRate > HRT3_freq)
    {
        HRT2List[HRT2List_size] = task_loc;
        HRT2List_size++;
        int div = HRT2_freq/taskRate > float(int(HRT2_freq/taskRate)) ? int(HRT2_freq/taskRate)+1 : int(HRT2_freq/taskRate);
        t->setDivisor(div);
    } else if (HRT3_freq >= taskRate && taskRate > LRT1_freq)
    {
        HRT3List[HRT3List_size] = task_loc;
        HRT3List_size++;
        int div = HRT3_freq/taskRate > float(int(HRT3_freq/taskRate)) ? int(HRT3_freq/taskRate)+1 : int(HRT3_freq/taskRate);
        t->setDivisor(div);
    } else if (LRT1_freq >= taskRate && taskRate > LRT2_freq)
    {
        LRT1List[LRT1List_size] = task_loc;
        LRT1List_size++;
        int div = LRT1_freq/taskRate > float(int(LRT1_freq/taskRate)) ? int(LRT1_freq/taskRate)+1 : int(LRT1_freq/taskRate);
        t->setDivisor(div);
    } else if (LRT2_freq >= taskRate)
    {
        LRT2List[LRT2List_size] = task_loc;
        LRT2List_size++;
        int div = LRT2_freq/taskRate > float(int(LRT2_freq/taskRate)) ? int(LRT2_freq/taskRate)+1 : int(LRT2_freq/taskRate);
        t->setDivisor(div);
    }else{
        log_m("Error: Timer not assigned for task");
        return 0;
    }
    

    return 1; // Return all good by default, could implement try/catch
}

int Taskmanager::removetask(int ID, int inst)
{
    /* This function removes a given task instance from the todo stack */

    /* First we find the location of the task in the stack */

    bool found = false;
    for(int i = 0; i<tasksUsed; i++)
    {
        if(taskList[i]->getID() == ID && taskList[i]->getInst())
        {
            found = true;
            break;
        }
    }

    if(!found){log_m("Warn: task to remove not found");} // Provide warning if not found
    else // Continue otherwise
    {   
        tasksUsed--;
        for(int i = 0; i<tasksUsed; i++)
        {
            taskList[i] = taskList[i+1]; // Shift to the left deleting task at i
        }
    }
    return 1;
}

void Taskmanager::HRT1_callback()
{
    for(int i = 0; i < HRT1List_size; i++)
    {
        if(taskList[HRT1List[i]]->updateShouldRun(int(HRT1_overrun*kp_HRT1)))
        {
            if(todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
            {
                todoStack[todoStackSize] = HRT1List[i]; // Add current task to todo stack
                todoStackSize++;
                if(HRT1_overrun>1){HRT1_overrun--;}
            }
            else
            {
                HRT1_overrun++;
            }
        }
    }
}

void Taskmanager::HRT2_callback()
{
    for(int i = 0; i < HRT2List_size; i++)
    {
        if(taskList[HRT2List[i]]->updateShouldRun(int(HRT2_overrun*kp_HRT2)))
        {
            if(todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
            {
                todoStack[todoStackSize] = HRT2List[i]; // Add current task to todo stack
                todoStackSize++;
                if(HRT2_overrun>1){HRT2_overrun--;}
            }
            else
            {
                HRT2_overrun++;
            }
        }
    }
}

void Taskmanager::HRT3_callback()
{
    for(int i = 0; i < HRT3List_size; i++)
    {
        if(taskList[HRT3List[i]]->updateShouldRun(int(HRT3_overrun*kp_HRT3)))
        {
            if(todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
            {
                todoStack[todoStackSize] = HRT3List[i]; // Add current task to todo stack
                todoStackSize++;
                if(HRT3_overrun>1){HRT3_overrun--;}
            }
            else
            {
                HRT3_overrun++;
            }
        }
    }
}

void Taskmanager::LRT1_callback()
{
    for(int i = 0; i < LRT1List_size; i++)
    {
        if(taskList[LRT1List[i]]->updateShouldRun(int(LRT1_overrun*kp_LRT1)))
        {
            if(todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
            {
                todoStack[todoStackSize] = LRT1List[i]; // Add current task to todo stack
                todoStackSize++;
                if(LRT1_overrun>1){LRT1_overrun--;}
            }
            else
            {
                LRT1_overrun++;
            }   
        }   
    }
}

void Taskmanager::LRT2_callback()
{
    for(int i = 0; i < LRT2List_size; i++)
    {
        if(taskList[LRT2List[i]]->updateShouldRun(int(LRT2_overrun*kp_LRT2)))
        {
            if(todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
            {
                todoStack[todoStackSize] = LRT2List[i]; // Add current task to todo stack
                todoStackSize++;
                if(LRT2_overrun>1){LRT2_overrun--;}
            }
            else
            {
                LRT2_overrun++;
            }   
        }
    }
}