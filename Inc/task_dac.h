#ifndef TASK_DAC_H
#define TASK_DAC_H

SemaphoreHandle_t mutex_DAC_value = NULL;

void task_dac(void *arguments);

#endif //TASK_DAC_H
