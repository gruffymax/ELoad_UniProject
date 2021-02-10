#include "interrupts.h"

void init_interrupts(void)
{
    __enable_irq();
        
    MODIFY_REG(EXTI->EXTICR[3], EXTI_EXTICR4_EXTI15, 0x0); //Set EXTI to PA15 pin
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT15); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM15); //Unmask interrupt
    NVIC_EnableIRQ(7); //Enable EXTI4_15 interrupt service routine
    
    MODIFY_REG(EXTI->EXTICR[0], EXTI_EXTICR1_EXTI0, EXTI_EXTICR1_EXTI0_0 | EXTI_EXTICR1_EXTI0_1 ); //Set to Pin PD0
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT0); //Enable rising edge detection
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT0); //Enable falling edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM0);
    NVIC_EnableIRQ(5); //Enable EXTI0_1 interrupt
}
