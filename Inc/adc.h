#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "stm32g0xx.h"

void init_adc(void);
uint16_t convert_voltage(void);
uint16_t convert_current(void);

#endif //ADC_H
