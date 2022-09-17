#include <Task.h>
#include <helpers.h>

class DummyTask : public Task
{
    public:
    DummyTask(float rate_des);
    int init() override;
    int update() override;
    
};

DummyTask::DummyTask(float rate_des):Task(rate_des){}

int DummyTask::init()
{
    log_m("Hello world!");
    return 1;
}

int DummyTask::update()
{
    log_m("foo");
    return 1;
}

DummyTask dt = DummyTask(0.14f); //initialize at 1hz