/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Main
 */

#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "proj_tasks.h"
#include <stdint.h>
#include <stddef.h>


void SysTick_Handler(void);
void EXTI0_1_IRQHandler(void);
void EXTI4_15_IRQHandler(void);


int main(void)
{

    
    init_system();
;
    
    while(1);
}

void SysTick_Handler(void)
{
    
}

void EXTI0_1_IRQHandler(void)
{
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF0))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF0); //Clear interrupt flag
        //TODO
    }
    if (READ_BIT(EXTI->FPR1, EXTI_FPR1_FPIF0))
    {
        SET_BIT(EXTI->FPR1, EXTI_FPR1_FPIF0); //Clear interrupt flag
        //TODO
    }
}

void EXTI4_15_IRQHandler(void)
{
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF15))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF15); //CLear interrupt flag
        //TODO
    }
}
