#include "gpio.h"
static void configureGPIOA(void);

void init_gpio(void)
{
    configureGPIOA();
}

static void configureGPIOA(void)
{
    /* Configure GPIOA pins */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE4, GPIO_MODER_MODE4_0); // PA4 OUTPUT
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE2, GPIO_MODER_MODE2_0); // PA2 OUTPUT
}
