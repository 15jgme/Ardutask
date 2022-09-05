#include <MultiTime.h>

MultiTime::MultiTime(int (*fn_cb_s)(), int label_s)
{
    fn_cb = fn_cb_s;
    label = label_s;
}

int MultiTime::timerCallback()
{
    /* Check which type of timer we are, hit the desired callback accordingly */
    fn_cb(); // Run callback function
    return 1;
}