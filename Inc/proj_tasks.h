//
// Created by Gareth on 29/12/2020.
//

#ifndef PROJ_TASKS_H
#define PROJ_TASKS_H

#include "stm32g0xx.h"

/* Task 1
 * Blinks an LED at 2 Hz
 */
void task_blink1(void *argument);

/* Task 2
 * Blinks an LED at 5 Hz
 */
void task_blink2(void *argument);

#endif //PROJ_TASKS_H
