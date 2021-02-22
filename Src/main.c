/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Main
 */

#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "task_ui.h"
#include "task_dac.h"
#include <stdint.h>
#include <stddef.h>

BaseType_t create_tasks(void);


int main(void)
{
    init_system();
    
    /* Create Mutexes */
    mutex_DAC_value = xSemaphoreCreateMutex();
    if (create_tasks() == pdPASS)
    {
        vTaskStartScheduler();
    }
    
    while(1);
}

BaseType_t create_tasks(void)
{
    BaseType_t ret = 0;
    
    ret = xTaskCreate(task_control, "Task_Control", 128, NULL, tskIDLE_PRIORITY + 1, &control_task_handle);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    ret = xTaskCreate(task_lcd, "Task_LCD", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    ret = xTaskCreate(task_events, "Task_Events", 32, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    ret = xTaskCreate(task_dac, "Task_DAC", 32, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    return pdPASS;
}
