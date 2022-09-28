#include <unity.h>
#include "Ardutask.h"
#include <iostream>
#include "native_test_bl.hpp"

#define ITERS_MAX 2000

Taskmanager * taskMan;

NativeTestBl * t1;
bool t1_res;
NativeTestBl * t2;
bool t2_res;
NativeTestBl * t3;
bool t3_res;
NativeTestBl * t4;
bool t4_res;
NativeTestBl * t5;
bool t5_res;
NativeTestBl * t6;
bool t6_res;

void setUp(void) {
    // set stuff up here
    taskMan = new Taskmanager();
    t1 = new NativeTestBl(40.0f, &t1_res); //initialize at 40hz 
    taskMan->addtask(t1);
    t2 = new NativeTestBl(20.1f, &t2_res); //initialize at 20hz
    taskMan->addtask(t2);
    t3 = new NativeTestBl(5.0f, &t3_res); //initialize at 5hz
    taskMan->addtask(t3);
    t4 = new NativeTestBl(1.0f, &t4_res); //initialize at 1hz
    taskMan->addtask(t4);
    t5 = new NativeTestBl(0.1f, &t5_res); //initialize at 0.1hz
    taskMan->addtask(t5);
    t6 = new NativeTestBl(0.05f, &t6_res); //initialize at 0.05hz
    taskMan->addtask(t6);

    for(int i = 0; i<ITERS_MAX; i++)
    {
        taskMan->run();
        runMsgPump();
    }
}

void tearDown(void) {
    // clean stuff up here
    delete taskMan;
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete t6;
}

void test_rate_t1()
{
    std::cout<<t1->runningAvgRate<<std::endl;
    std::cout<<t2->runningAvgRate<<std::endl;
    std::cout<<t3->runningAvgRate<<std::endl;
    std::cout<<t4->runningAvgRate<<std::endl;
    std::cout<<t5->runningAvgRate<<std::endl;
    std::cout<<t6->runningAvgRate<<std::endl;
    TEST_ASSERT_TRUE(t1->tr);
}

void test_rate_t2()
{
    std::cout<<t1->runningAvgRate<<std::endl;
    std::cout<<t2->runningAvgRate<<std::endl;
    std::cout<<t3->runningAvgRate<<std::endl;
    std::cout<<t4->runningAvgRate<<std::endl;
    std::cout<<t5->runningAvgRate<<std::endl;
    std::cout<<t6->runningAvgRate<<std::endl;
    TEST_ASSERT_TRUE(t2->tr);
}

void test_rate_t3()
{
    std::cout<<t1->runningAvgRate<<std::endl;
    std::cout<<t2->runningAvgRate<<std::endl;
    std::cout<<t3->runningAvgRate<<std::endl;
    std::cout<<t4->runningAvgRate<<std::endl;
    std::cout<<t5->runningAvgRate<<std::endl;
    std::cout<<t6->runningAvgRate<<std::endl;
    TEST_ASSERT_TRUE(t3->tr);
}

void test_rate_t4()
{
    std::cout<<t1->runningAvgRate<<std::endl;
    std::cout<<t2->runningAvgRate<<std::endl;
    std::cout<<t3->runningAvgRate<<std::endl;
    std::cout<<t4->runningAvgRate<<std::endl;
    std::cout<<t5->runningAvgRate<<std::endl;
    std::cout<<t6->runningAvgRate<<std::endl;
    TEST_ASSERT_TRUE(t4->tr);
}

void test_rate_t5()
{
    std::cout<<t1->runningAvgRate<<std::endl;
    std::cout<<t2->runningAvgRate<<std::endl;
    std::cout<<t3->runningAvgRate<<std::endl;
    std::cout<<t4->runningAvgRate<<std::endl;
    std::cout<<t5->runningAvgRate<<std::endl;
    std::cout<<t6->runningAvgRate<<std::endl;
    TEST_ASSERT_TRUE(t5->tr);
}

void test_rate_t6()
{
    std::cout<<t1->runningAvgRate<<std::endl;
    std::cout<<t2->runningAvgRate<<std::endl;
    std::cout<<t3->runningAvgRate<<std::endl;
    std::cout<<t4->runningAvgRate<<std::endl;
    std::cout<<t5->runningAvgRate<<std::endl;
    std::cout<<t6->runningAvgRate<<std::endl;
    TEST_ASSERT_TRUE(t6->tr);
}

int main(int argc, char **argv) 
{ 
    UNITY_BEGIN(); 

    RUN_TEST(test_rate_t1); 
    RUN_TEST(test_rate_t2); 
    RUN_TEST(test_rate_t3); 
    RUN_TEST(test_rate_t4); 
    RUN_TEST(test_rate_t5); 
    RUN_TEST(test_rate_t6); 

    UNITY_END(); 

    return 0; 
} 