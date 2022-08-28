#ifndef TASK_H
#define TASK_H

/*

This is the base class defining the required implimentations of a given task. The Taskmanager 
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
public:
    Task(){} // Note: Maybe populate inst here?
    int getID(){return task_ID;}
    int getInst(){return inst;}
    int increaseCount(){counter++; return 1;}
    bool shouldRun(int trigger);
    void setInst(int i){inst = i;}
    virtual int init();
    virtual int update();
    ~Task(){}
};

#endif