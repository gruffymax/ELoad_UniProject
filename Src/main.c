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
#include "task_ui.h"
#include "task_dac.h"
#include "task_lcd.h"
#include "task_control.h"

#include <stdint.h>
#include <stddef.h>

BaseType_t create_tasks(void);
static TaskHandle_t task_lcd_handle = NULL;

int main(void)
{
    init_system();
    //init_mutexes();
    
    if (create_tasks() == pdPASS)
    {
        vTaskStartScheduler();
    }
    
    while(1);
}

BaseType_t create_tasks(void)
{
    BaseType_t ret = 0;
    
    ret = xTaskCreate(task_dac, "Task_DAC", 64, NULL, tskIDLE_PRIORITY + 1, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    ret = xTaskCreate(task_lcd, "Task_LCD", 64, NULL, tskIDLE_PRIORITY + 1, &task_lcd_handle);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    ret = xTaskCreate(task_ui, "Task_ui", 128, &task_lcd_handle, tskIDLE_PRIORITY + 1, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    ret = xTaskCreate(task_control, "Task_Control", 128, NULL, tskIDLE_PRIORITY + 1, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    return pdPASS;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    TaskHandle_t bad_task_handle = xTask;     // this seems to give me the crashed task handle
    char *bad_task_name = pcTaskName;     // this seems to give me a pointer to the name of the crashed task
    while(1)
    {
        // Stack overflow
    }
}
