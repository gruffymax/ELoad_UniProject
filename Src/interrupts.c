#include "interrupts.h"

/* Static functions */
static void check_encoder_ch_B(uint8_t state_of_A);

/* Static variables */
static event_flag_t event_cw = UNSET;
static event_flag_t event_ccw = UNSET;
static event_flag_t event_button_encoder = UNSET;
static event_flag_t event_button_start = UNSET;
static event_flag_t event_button_cc = UNSET;
static event_flag_t event_button_cv = UNSET;
static event_flag_t event_button_cr = UNSET;
static event_flag_t event_button_cp = UNSET;

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

void EXTI0_1_IRQHandler(void)
{
    /* Rotary encoder channel A rising edge interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF0))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF0); //Clear interrupt flag
        check_encoder_ch_B(1);
    }
}

void EXTI4_15_IRQHandler(void)
{
    /* Start button interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF10))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF10); //Clear interrupt flag
        event_button_start = SET;
    }
    
    /* CC button interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF11))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF11); //Clear interrupt flag
        event_button_cc = SET;
    }
    
    /* CV button interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF12))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF12); //Clear interrupt flag
        event_button_cv = SET;
    }
    
    /* CR button interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF13))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF13); //Clear interrupt flag
        event_button_cr = SET;
    }
    
    /* CP button interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF14))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF14); //Clear interrupt flag
        event_button_cp = SET;
    }

    /* Rotary encoder button interrupt */
    if (READ_BIT(EXTI->RPR1, EXTI_RPR1_RPIF15))
    {
        SET_BIT(EXTI->RPR1, EXTI_RPR1_RPIF15); //Clear interrupt flag
        event_button_encoder = SET;
    }
}

static void check_encoder_ch_B(uint8_t state_of_A)
{
    /* If both channels are in the same state, trigger a CCW event,
     * else trigger a CW event */
    uint32_t read_pd1 = READ_BIT(GPIOD->IDR, GPIO_IDR_ID1) >> 1;
    if (read_pd1 == state_of_A)
    {
        /* CCW event */
        event_ccw = SET;
    }
    else
    {
        /* CW event */
        event_cw = SET;
    }
}

event_flag_t get_event_cw(void)
{
    return event_cw;
}

event_flag_t get_event_ccw(void)
{
    return event_ccw;
}

event_flag_t get_event_button_encoder(void)
{
    return event_button_encoder;
}

event_flag_t get_event_button_start(void)
{
    return event_button_start;
}

event_flag_t get_event_button_cc(void)
{
    return event_button_cc;
}

event_flag_t get_event_button_cv(void)
{
    return event_button_cv;
}

event_flag_t get_event_button_cr(void)
{
    return event_button_cr;
}

event_flag_t get_event_button_cp(void)
{
    return event_button_cp;
}

void clear_event_cw(void)
{
    event_cw = UNSET;
}

void clear_event_ccw(void)
{
    event_ccw = UNSET;
}

void clear_event_button_encoder(void)
{
    event_button_encoder = UNSET;
}

void clear_event_button_start(void)
{
    event_button_start = UNSET;
}

void clear_event_button_cc(void)
{
    event_button_cc = UNSET;
}

void clear_event_button_cv(void)
{
    event_button_cv = UNSET;
}

void clear_event_button_cr(void)
{
    event_button_cr = UNSET;
}

void clear_event_button_cp(void)
{
    event_button_cp = UNSET;
}

void NMI_Handler(void)
{

}


void HardFault_Handler(void)
{

  while (1)
  {

  }
}

