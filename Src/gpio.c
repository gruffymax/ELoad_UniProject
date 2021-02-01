#include "gpio.h"

void init_gpio(void)
{
   MODIFY_REG(GPIOA->MODER, GPIOA_MODER_MODE4, GPIOA_MODER_MODE4_1);

    
}

