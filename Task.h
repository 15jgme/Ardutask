#pragma once
/*

This is the base class defining the required implementations of a given task. The Taskmanager 
uses this information to run a given set of tasks.

*/

class Task
{
    /* TO BE FILLED BY DERIVED CLASSES */
    float rate_hz; // Target run rate of the process 

    /* AUTOMATICALLY POPULATED */
    int task_ID = 0; // This value defines a given process type and must be unique!
    int inst = 0; // This value defines the instance of a given process, this is autofilled
    int counter = 0; // This is the counter used to determine if the process should be ran
    int divisor = 1; // This is assigned by task manager depending on timer assignment, it represents the amount of timer callbacks before the task is added to the stack 
public:
    Task(float rate_des); // Normal constructor
    Task(){rate_hz = 1.0f;} //Dummy constructor
    int getID(){return task_ID;}
    int getInst(){return inst;}
    float getRate(){return rate_hz;}
    int increaseCount(){counter++; return 1;}
    bool updateShouldRun(int dynamicDivisor);
    void setInst(int i){inst = i;}
    void setDivisor(int i){divisor = i;}
    virtual int init(){return 0;}
    virtual int update(){return 0;}
    ~Task(){}
};
