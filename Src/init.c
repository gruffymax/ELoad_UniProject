/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Initialisation functions
 */

#include "stm32g0xx.h"
#include "init.h"
#include "gpio.h"
#include "clock_tree.h"

void init_system(void)
{
    init_clock_tree();
    init_gpio();
    //init_adc();
    //init_uart();
    //init_timers();
    //init_dac();
}



