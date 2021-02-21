#include "task_dac.h"
#include "FreeRTOS.h"
#include "task.h"
#include "task_control.h"
#include "dac.h"

static uint32_t dac_value = 0;

void task_dac(void *arguments)
{
    while(1)
    {
        /* Get protected DAC value */
        if (xSemaphoreTake(mutex_DAV_value, 10) == pdPASS)
        {
            // Start critical section
            dac_value = ctrl_dac_value;
            // End critical section
            xSemaphoreGive(mutex_DAV_value);
        }
    
        write_dac1_value(dac_value);
        vTaskDelay(100);
    }
}
