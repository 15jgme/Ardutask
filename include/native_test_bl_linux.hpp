/* This is a testing class used to measure if taskManager is meeting frequency requirements */

#include <Task.h>
#include <helpers.h>
#include <sys/time.h>

#define TEST_TOLERANCE_PERCENT 60.0f

class NativeTestBl : public Task
{
    public:
    NativeTestBl(float rate_des, bool * tp);
    int init() override;
    int update() override;
    struct timeval tp;
    
    long int tlast = 0;
    long iters = 1; // Number of iterations (used for averaging)
    bool * testPass;
    float runningAvgRate;
    double rateSum = 0; // Variable to hold sum for computation of running average
    bool tr = false;
};

NativeTestBl::NativeTestBl(float rate_des, bool * tp):Task(rate_des){testPass = tp;}

int NativeTestBl::init()
{
    gettimeofday(&tp, NULL);
    tlast = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return 1;
}

int NativeTestBl::update()
{
    gettimeofday(&tp, NULL);
    long int tcurr = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    float currentPeriod = float(tcurr-tlast);
    if(currentPeriod > 0)
    {
        float currentRate = 1000.0f/currentPeriod;
        rateSum += double(currentRate);
        runningAvgRate = float(rateSum) / float(iters);
        tr = (runningAvgRate < (1.0f + TEST_TOLERANCE_PERCENT/100.0f)*getRate()) && (runningAvgRate > (1.0f - TEST_TOLERANCE_PERCENT/100.0f)*getRate());
        gettimeofday(&tp, NULL);
        tlast = tp.tv_sec * 1000 + tp.tv_usec / 1000;
        iters++;
    }
    return 1;
}