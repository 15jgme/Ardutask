#include <Task.h>
#include <helpers.h>
#include <windows.h>

#define TEST_TOLERANCE_PERCENT 60.0f

class NativeTestBl : public Task
{
    public:
    NativeTestBl(float rate_des, bool * tp);
    int init() override;
    int update() override;
    DWORD tlast = GetTickCount();
    long iters = 1; // Number of iterations (used for averaging)
    bool * testPass;
    float runningAvgRate;
    double rateSum = 0; // Variable to hold sum for computation of running average
    bool tr = false;
};

NativeTestBl::NativeTestBl(float rate_des, bool * tp):Task(rate_des){testPass = tp;}

int NativeTestBl::init()
{
    tlast = GetTickCount();
    return 1;
}

int NativeTestBl::update()
{
    float currentPeriod = float(GetTickCount()-tlast);
    if(currentPeriod > 0)
    {
        float currentRate = 1000.0f/currentPeriod;
        rateSum += double(currentRate);
        runningAvgRate = float(rateSum) / float(iters);
        tr = (runningAvgRate < (1.0f + TEST_TOLERANCE_PERCENT/100.0f)*getRate()) && (runningAvgRate > (1.0f - TEST_TOLERANCE_PERCENT/100.0f)*getRate());
        tlast = GetTickCount();
        iters++;
    }
    return 1;
}