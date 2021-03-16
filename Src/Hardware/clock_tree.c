/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Cortex Clock Tree initialisation
 */

#include "clock_tree.h"

static inline void flashLatency(void);
static inline void enable_hsi(void);
static inline void configure_system_clock(void);
static inline void enable_periph_clocks(void);

void init_clock_tree(void)
{
    flashLatency();
    enable_hsi();
    configure_system_clock();
    enable_periph_clocks();
}

static inline void flashLatency(void)
{
    /* Set flash latency to two wait states */
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
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
    /* System clock to be set to 64 MHz HSI with  PLL */
    
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN, RCC_PLLCFGR_PLLN_4); // N = 16
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, RCC_PLLCFGR_PLLM_0); // M = 2
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLP, RCC_PLLCFGR_PLLP_0); // P = 2
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLPEN); // Enable PLLP
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLR, RCC_PLLCFGR_PLLR_0); // R = 2
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLREN); // Enable PLLR
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, RCC_PLLCFGR_PLLSRC_1);
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == 0x0U)
    {
	//Wait until PLL locked
    }
    

    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, 0x0U); //Set AHB prescaler to 1
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, 0x0U); //Set APB prescaler to 1
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_1);   //Set clock source to PLLRCLK
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != 0x10U)
    {
        //Wait here until clock source is confirmed to be PLLRCLK
    }
    SystemInit();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/6400);
}

static inline void enable_periph_clocks(void)
{
    //ToDo
    /* Arm Cortex peripheral clocks need to be enabled to use peripheral */
    SET_BIT(RCC->APBENR2, RCC_APBENR2_SYSCFGEN);    //Enable SYS_CFG peripheral
    SET_BIT(RCC->APBENR1, RCC_APBENR1_PWREN);       //Enable Power peripheral
    
    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);       //Enable GPIOA peripheral
    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);       //Enable GPIOB peripheral
    SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIODEN);       //Enable GPIOD peripheral
    SET_BIT(RCC->APBENR1, RCC_APBENR1_DAC1EN);      //Enable DAC peripheral
    SET_BIT(RCC->APBENR2, RCC_APBENR2_ADCEN);       //Enable ADC peripheral

}
