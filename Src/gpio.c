#include "gpio.h"

void init_gpio(void)
{
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE4, GPIO_MODER_MODE4_1);
    
}

