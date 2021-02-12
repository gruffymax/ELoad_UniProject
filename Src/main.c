/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Main
 */

#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "task_lcd.h"
#include <stdint.h>
#include <stddef.h>

int main(void)
{
    BaseType_t ret = 0;
    
    init_system();
    
    ret = xTaskCreate(task_lcd, "Task_LCD", 32, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (ret != pdPASS)
    {
        /* Task not created successfully */
        while(1);
    }
    
    vTaskStartScheduler();
    
    while(1);
}

