/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Main
 */

#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "proj_tasks.h"
#include <stdint.h>
#include <stddef.h>

int main(void)
{
    /* Initialise system */
    init_system();
    
    /* Configure Tasks and start scheduler */
    BaseType_t retval = 0;
    retval = xTaskCreate(task1, "task1", 15, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (retval != pdPASS)
	{
        while(1); //Error Occured
	}
	
	retval = xTaskCreate(task2, "task2", 15, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (retval != pdPASS)
	{
        while(1); //Error Occured
	}
	
	retval = xTaskCreate(task3, "task3", 50, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (retval != pdPASS)
	{
        while(1); //Error Occured
	}
	
    vTaskStartScheduler();
}
