/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Main
 */

#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "el_sem.h"
#include "task_ui.h"
#include "task_dac.h"
#include <stdint.h>
#include <stddef.h>

BaseType_t create_tasks(void);


int main(void)
{
    init_system();
    init_mutexes();
    
    if (create_tasks() == pdPASS)
    {
        vTaskStartScheduler();
    }
    
    while(1);
}

BaseType_t create_tasks(void)
{
    BaseType_t ret = 0;
    
    ret = xTaskCreate(task_ui, "Task_ui", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    
    ret = xTaskCreate(task_dac, "Task_DAC", 32, NULL, tskIDLE_PRIORITY + 1, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    return pdPASS;
}
