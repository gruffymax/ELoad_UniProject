#ifndef EL_SEMS_H
#define EL_SEMS_H

#include "FreeRTOS.h"
#include "semphr.h"

void init_mutexes(void);
BaseType_t take_data_mutex(void);
void give_data_mutex(void);

#endif //EL_SEMS_H
