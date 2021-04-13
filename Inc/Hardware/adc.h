/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * adc.h
 */
#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "stm32g0xx.h"

void init_adc(void);
void convert_voltage(void);
void convert_current(void);
uint16_t get_voltage(void);
uint16_t get_current(void);

#endif //ADC_H
