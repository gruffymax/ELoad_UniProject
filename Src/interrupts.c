#include "interrupts.h"

void init_interrupts(void)
{
    /* Enable global interrupts */
    __enable_irq();
    NVIC_EnableIRQ(5); //Enable EXTI0_1 interrupt
    NVIC_EnableIRQ(7); //Enable EXTI4_15 interrupt service routine
    
    /* Enable interrupt for Rotary encoder switch */
    MODIFY_REG(EXTI->EXTICR[3], EXTI_EXTICR4_EXTI15, 0x0); //Set EXTI to PA15 pin
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT15); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM15); //Unmask interrupt
    
    
    /* Enable interrupt for Rotary encoder Channel A */
    MODIFY_REG(EXTI->EXTICR[0], EXTI_EXTICR1_EXTI0, EXTI_EXTICR1_EXTI0_0 | EXTI_EXTICR1_EXTI0_1 ); //Set to Pin PD0
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT0); //Enable rising edge detection
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT0); //Enable falling edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM0); //Unmask interrupt
    
    /* Enable interrupt for Start Button */
    MODIFY_REG(EXTI->EXTICR[2], EXTI_EXTICR3_EXTI10, EXTI_EXTICR3_EXTI10_0); //Set to Pin PB10
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT10); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM10); //Unmask interrupt
    
    /* Enable interrupt for CC Button */
    MODIFY_REG(EXTI->EXTICR[2], EXTI_EXTICR3_EXTI11, EXTI_EXTICR3_EXTI11_0); //Set to Pin PB11
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT11); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM11); //Unmask interrupt
    
    /* Enable interrupt for CV Button */
    MODIFY_REG(EXTI->EXTICR[3], EXTI_EXTICR4_EXTI12, EXTI_EXTICR4_EXTI12_0); //Set to Pin PB12
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT12); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM12); //Unmask interrupt
    
    /* Enable interrupt for CR Button */
    MODIFY_REG(EXTI->EXTICR[3], EXTI_EXTICR4_EXTI13, EXTI_EXTICR4_EXTI13_0); //Set to Pin PB13
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT13); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM13); //Unmask interrupt
    
    /* Enable interrupt for CP Button */
    MODIFY_REG(EXTI->EXTICR[3], EXTI_EXTICR4_EXTI14, EXTI_EXTICR4_EXTI14_0); //Set to Pin PB14
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT14); //Enable rising edge detection
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM14); //Unmask interrupt
}
