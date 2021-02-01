#include "stm32g0xx.h"
#include "init.h"
#include "FreeRTOS.h"
#include "task.h"


void task_blink(void *argument);

int main(void)
{
    BaseType_t retval = 0;
    /* Initialise system */
    init_system();

    /* Configure Tasks and start scheduler */
    retval = xTaskCreate(task_blink, "task_blink", 128, NULL, tskIDLE_PRIORITY + 2, NULL);
    if (retval == pdPASS)
	{
	    vTaskStartScheduler();
	}

    /* While loop to catch if FreeRTOS exits unexpectedly */
    while(1);
}

void task_blink(void *argument)
{
    //Blinky code here
    while(1)
    {
        	    
    }
