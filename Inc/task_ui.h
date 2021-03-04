#ifndef TASK_UI_H
#define TASK_UI_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

void task_ui(void *argument);
uint32_t get_dac_setting(void);

#endif //TASK_UI_H
