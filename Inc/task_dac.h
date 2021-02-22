#ifndef TASK_DAC_H
#define TASK_DAC_H
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

extern SemaphoreHandle_t mutex_DAC_value;

void task_dac(void *arguments);

#endif //TASK_DAC_H
