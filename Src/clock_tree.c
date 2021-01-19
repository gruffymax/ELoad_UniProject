//
// Created by gareth on 29/12/2020.
//

#include "clock_tree.h"

static inline void enable_hsi(void);
static inline void configure_system_clock(void);
static inline void enable_periph_clocks(void);

void init_clock_tree(void)
{
    enable_hsi();
    configure_system_clock();
    enable_periph_clocks();
}

static inline void enable_hsi(void)
{
    //Enable HSI (High Speed Internal oscillator)
    SET_BIT(RCC->CR, RCC_CR_HSION);
    while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (0))
    {
        //Wait until HSI is enabled
    }
}

static inline void configure_system_clock(void)
{
    /* System clock to be set to 16 MHz HSI with no PLL */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, 0x0U); //Set AHB prescaler to 1
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, 0x0U); //Set APB prescaler to 1
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, 0x0U);   //Set clock source to HSISYS
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != 0x0U)
    {
        //Wait here until clock source is confirmed to be HSISYS
    }
}

static inline void enable_periph_clocks(void)
{
    //ToDo
    /* Arm Cortex peripheral clocks need to be enabled to use peripheral */
    SET_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN);    //Enable SYS_CFG peripheral
    SET_BIT(RCC->APBENR1, RCC_APBENR1_PWREN);       //Enable Power peripheral
    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);       //Enable GPIOA peripheral
    SET_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN);      //Enable DAC peripheral
    SET_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN);       //Enable ADC peripheral

}