#include "stm32g0xx.h"
#include "init.h"
#include "gpio.h"
#include "clock_tree.h"

void init_system(void)
{
    init_clock_tree();
    init_gpio();
    init_adc();
    init_uart();
    init_timers();
    init_dac();
}

void init_adc(void)
{
    //ToDo
}

void init_uart(void)
{
    //ToDo
}

void init_timers(void)
{
    //ToDo
}

void init_dac(void)
{
    //ToDo
}

