#ifndef DAC_H
#define DAC_H

#include "stm32g0xx.h"
#include <stdint.h>

void init_dac(void);

void write_dac1_value(uint32_t value);

#endif // DAC_H
