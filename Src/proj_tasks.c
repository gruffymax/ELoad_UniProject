#include "proj_tasks.h"

void task_blink1(void *argument)
{
    //Blinky code here
    while(1)
    {
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS2); //Set PA2
        vTaskDelay(500); //Wait 500 ticks
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR2); //Reset PA2
        vTaskDelay(500); //Wait 500 ticks
    }
}

void task_blink2(void *argument)
{
    while(1)
    {
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS4); //Set PA4
        vTaskDelay(200); //Wait 200 ticks
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4); //Reset PA4
        vTaskDelay(200); //Wait 200 ticks
    }
}
