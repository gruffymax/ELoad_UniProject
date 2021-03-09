#ifndef TASK_UI_H
#define TASK_UI_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

void task_ui(void *task_lcd_handle);
uint32_t evaluate_ui(TaskHandle_t *task_lcd_handle);

#endif //TASK_UI_H
