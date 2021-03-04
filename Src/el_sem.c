#include "el_sem.h"

SemaphoreHandle_t data_mutex = NULL;

void init_mutexes(void)
{
    data_mutex = xSemaphoreCreateMutex();
    if (data_mutex == NULL)
    {
        while(1); //Error creating semaphore
    }
}

BaseType_t take_data_mutex(void)
{
    if (xSemaphoreTake(data_mutex, (TickType_t) 20) == pdTRUE)
    {
        return pdTRUE;
    }
    else
    {
        return pdFALSE;
    }
}

void give_data_mutex(void)
{
    if (xSemaphoreGive(data_mutex) == pdFALSE)
    {
        while(1); // An error occured during release
    }
}
