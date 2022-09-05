#ifndef TASK_H
#define TASK_H

/*

This is the base class defining the required implementations of a given task. The Taskmanager 
uses this information to run a given set of tasks.

*/

class Task
{
    /* TO BE FILLED BY DERIVED CLASSES */
    int task_ID; // This value defines a given process type and must be unique!
    float rate_hz; // Target run rate of the process 

    /* AUTOMATICALLY POPULATED */
    int inst; // This value defines the instance of a given process, this is autofilled
    int counter = 0; // This is the counter used to determine if the process should be ran
    int divisor = 1; // This is assigned by task manager depending on timer assignment, it represents the amount of timer callbacks before the task is added to the stack 
public:
    Task(){} // Note: Maybe populate inst here?
    void setDivisor(int i){divisor = i;}
    int getID(){return task_ID;}
    int getInst(){return inst;}
    int getRate(){return rate;}
    int increaseCount(){counter++; return 1;}
    bool updateShouldRun(int dynamicDivisor);
    void setInst(int i){inst = i;}
    virtual int init();
    virtual int update();
    ~Task(){}
};

#endif