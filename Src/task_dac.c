#include "task_dac.h"
#include "task_control.h"
#include "dac.h"


uint32_t dac_value = 0;
SemaphoreHandle_t mutex_DAC_value = NULL;

void task_dac(void *arguments)
{
    while(1)
    {
        /* Get protected DAC value */
        if (xSemaphoreTake(mutex_DAC_value, 10) == pdPASS)
        {
            // Start critical section
            dac_value = ctrl_dac_value;
            // End critical section
            xSemaphoreGive(mutex_DAC_value);
        }
    
        write_dac1_value(dac_value);
        vTaskDelay(100);
    }
}
