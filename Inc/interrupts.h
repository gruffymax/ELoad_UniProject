#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "stm32g0xx.h"
#include <stdint.h>

#define SET 1
#define UNSET 0
typedef char event_flag_t;

void EXTI0_1_IRQHandler(void);
void EXTI4_15_IRQHandler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void init_interrupts(void);

event_flag_t get_event_cw(void);
event_flag_t get_event_ccw(void);
event_flag_t get_event_button_encoder(void);
event_flag_t get_event_button_start(void);
event_flag_t get_event_button_cc(void);
event_flag_t get_event_button_cv(void);
event_flag_t get_event_button_cr(void);
event_flag_t get_event_button_cp(void);

void clear_event_cw(void);
void clear_event_ccw(void);
void clear_event_button_encoder(void);
void clear_event_button_start(void);
void clear_event_button_cc(void);
void clear_event_button_cv(void);
void clear_event_button_cr(void);
void clear_event_button_cp(void);

#endif //INTERRUPTS_H
