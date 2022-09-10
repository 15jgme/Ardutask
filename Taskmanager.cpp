#include "Taskmanager.h"
// #include <MultiTime.h>
#include "helpers.h"

/* Initialize statics in cpp at the bequest of the compiler */
int Taskmanager::HRT1List_size = 0;
int Taskmanager::HRT2List_size = 0;
int Taskmanager::HRT3List_size = 0;
int Taskmanager::LRT1List_size = 0;
int Taskmanager::LRT2List_size = 0;
short Taskmanager::todoStackSize = 0;

int Taskmanager::HRT1List[TASK_LIMIT];
int Taskmanager::HRT2List[TASK_LIMIT];
int Taskmanager::HRT3List[TASK_LIMIT];
int Taskmanager::LRT1List[TASK_LIMIT];
int Taskmanager::LRT2List[TASK_LIMIT];
int Taskmanager::todoStack[TASK_STACK_SIZE];
Task* Taskmanager::taskList[TASK_LIMIT];

Taskmanager::Taskmanager()
{
    HRT1_t.setTimer(HRT1_freq); // Hz
    HRT2_t.setTimer(HRT2_freq); // Hz
    HRT3_t.setTimer(HRT3_freq); // Hz
    LRT1_t.setTimer(LRT1_freq); // Hz
    LRT1_t.setTimer(LRT2_freq); // Hz
}

int Taskmanager::run()
{
    if(todoStackSize > 0)
    {
        taskList[todoStack[0]]->update(); // Run task in stack
        for(int i = 0; i < todoStackSize; i++)
        {
            todoStack[i] = todoStack[i+1];
            todoStackSize--;
        }
        
        log_m(std::to_string(todoStackSize).c_str());
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

    /* Perform timer assignment */
    if(t->getRate() > HRT1_freq)
    {
        HRT1List[HRT1List_size] = task_loc;
        HRT1List_size++;
        int div = HRT1_freq/t->getRate() > float(int(HRT1_freq/t->getRate())) ? int(HRT1_freq/t->getRate())+1 : int(HRT1_freq/t->getRate());
        t->setDivisor(div);
    } else if (HRT1_freq > t->getRate() > HRT2_freq)
    {
        HRT2List[HRT2List_size] = task_loc;
        HRT2List_size++;
        int div = HRT2_freq/t->getRate() > float(int(HRT2_freq/t->getRate())) ? int(HRT2_freq/t->getRate())+1 : int(HRT2_freq/t->getRate());
        t->setDivisor(div);
    } else if (HRT3_freq > t->getRate() > HRT3_freq)
    {
        HRT3List[HRT3List_size] = task_loc;
        HRT3List_size++;
        int div = HRT3_freq/t->getRate() > float(int(HRT3_freq/t->getRate())) ? int(HRT3_freq/t->getRate())+1 : int(HRT3_freq/t->getRate());
        t->setDivisor(div);
    } else if (LRT1_freq > t->getRate() > LRT1_freq)
    {
        LRT1List[LRT1List_size] = task_loc;
        LRT1List_size++;
        int div = LRT1_freq/t->getRate() > float(int(LRT1_freq/t->getRate())) ? int(LRT1_freq/t->getRate())+1 : int(LRT1_freq/t->getRate());
        t->setDivisor(div);
    } else if (LRT2_freq > t->getRate())
    {
        LRT1List[LRT1List_size] = task_loc;
        LRT1List_size++;
        int div = LRT2_freq/t->getRate() > float(int(LRT2_freq/t->getRate())) ? int(LRT2_freq/t->getRate())+1 : int(LRT2_freq/t->getRate());
        t->setDivisor(div);
    } // Add an error if none of these options
    

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
            found == true;
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

int Taskmanager::HRT1_callback()
{
    log_m("bizz1");
    for(int i = 0; i < HRT1List_size; i++)
    {
        taskList[HRT1List[i]]->increaseCount(); // Increase timer
        if(taskList[HRT1List[i]]->updateShouldRun(1) && todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
        {
            todoStack[todoStackSize] = HRT1List[i]; // Add current task to todo stack
        }
    }
    todoStackSize++;
    return 1;
}

int Taskmanager::HRT2_callback()
{
    log_m("bizz2");
    for(int i = 0; i < HRT2List_size; i++)
    {
        taskList[HRT2List[i]]->increaseCount(); // Increase timer
        if(taskList[HRT2List[i]]->updateShouldRun(1) && todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
        {
            todoStack[todoStackSize] = HRT2List[i]; // Add current task to todo stack
        }
    }
    todoStackSize++;
    return 1;
}

int Taskmanager::HRT3_callback()
{
    log_m("bizz3");
    for(int i = 0; i < HRT3List_size; i++)
    {
        taskList[HRT3List[i]]->increaseCount(); // Increase timer
        if(taskList[HRT3List[i]]->updateShouldRun(1) && todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
        {
            todoStack[todoStackSize] = HRT3List[i]; // Add current task to todo stack
        }
    }
    todoStackSize++;
    return 1;
}

int Taskmanager::LRT1_callback()
{
    log_m("bizz4");
    for(int i = 0; i < LRT1List_size; i++)
    {
        taskList[LRT1List[i]]->increaseCount(); // Increase timer
        if(taskList[LRT1List[i]]->updateShouldRun(1) && todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
        {
            todoStack[todoStackSize] = LRT1List[i]; // Add current task to todo stack
        }
    }
    todoStackSize++;
    return 1;
}

int Taskmanager::LRT2_callback()
{
    log_m("bizz5");
    for(int i = 0; i < LRT2List_size; i++)
    {
        taskList[LRT2List[i]]->increaseCount(); // Increase timer
        if(taskList[LRT2List[i]]->updateShouldRun(1) && todoStackSize < TASK_STACK_SIZE) // If we should run the task, and we're able to add it to the stack
        {
            todoStack[todoStackSize] = LRT2List[i]; // Add current task to todo stack
        }
    }
    todoStackSize++;
    return 1;
}