#ifndef CONTROL_H
#define CONTROL_H
#include "FreeRTOS.h"
#include "task.h"
#include "shared.h"
#include "dac.h"
#include "adc.h"



void task_control(void *argument);

#endif //CONTROL_H
