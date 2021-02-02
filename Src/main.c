#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"
#include "proj_tasks.h"
#include <stdint.h>
#include <stddef.h>


uint32_t milliseconds = 0;

void delay(uint32_t);

int main(void)
{
    BaseType_t retval = 0;
    /* Initialise system */
    init_system();
    //task_blink(NULL);
    
    /* Configure Tasks and start scheduler */
    retval = xTaskCreate(task_blink1, "task_blink1", 15, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (retval != pdPASS)
	{
        while(1); //Error Occured
	}
	
	retval = xTaskCreate(task_blink2, "task_blink2", 15, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (retval != pdPASS)
	{
        while(1); //Error Occured
	}
	
    vTaskStartScheduler();
}
