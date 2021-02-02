//
// Created by Gareth on 29/12/2020.
//

#ifndef PROJ_TASKS_H
#define PROJ_TASKS_H

#include <stdint.h>

void set_lcd_rw(uint8_t state);
void set_lcd_rs(uint8_t state);
void set_lcd_en(uint8_t state);
void set_lcd_d4(uint8_t state);
void set_lcd_d5(uint8_t state);
void set_lcd_d6(uint8_t state);
void set_lcd_d7(uint8_t state);
void set_d4_mode(uint8_t mode);
void set_d5_mode(uint8_t mode);
void set_d6_mode(uint8_t mode);
void set_d7_mode(uint8_t mode);
uint8_t is_d7_set(void);
void us_delay(uint16_t ms);

/* Task 1
 * Blinks an LED at 2 Hz
 */
void task1(void *argument);

/* Task 2
 * Counter 1 Hz
 */
void task2(void *argument);

/* Task 3
 * LCD Display
 */
void task3(void *arguments);

#endif //PROJ_TASKS_H
