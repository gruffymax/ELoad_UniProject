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
#include "task_lcd.h"
#include "task_control.h"

#include <stdint.h>
#include <stddef.h>

BaseType_t create_tasks(void);
static TaskHandle_t task_lcd_handle = NULL;

extern struct UI_State_s ui_state;
struct UI_State_s ui_state =
{
    mode_cc,
    stopped,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    {{0},{0}}
};

int main(void)
{
    init_system();
    
    if (create_tasks() == pdPASS)
    {
        vTaskStartScheduler();
    }
    
    while(1);
}

BaseType_t create_tasks(void)
{
    BaseType_t ret = 0;
    
    ret = xTaskCreate(task_lcd, "Task_LCD", 128, NULL, tskIDLE_PRIORITY + 1, &task_lcd_handle);
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
    
    ret = xTaskCreate(task_control, "Task_Control", 512, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        return ret;
    }
    
    return pdPASS;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    //TaskHandle_t bad_task_handle = xTask;     // Crashed task handle
    //char *bad_task_name = pcTaskName;     // Pointer to the name of the crashed task
    while(1)
    {
        // Stack overflow
    }
}
