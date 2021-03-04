#include "task_dac.h"
#include "dac.h"
#include "ui_state.h"


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
            dac_value = get_dac_setting();
            // End critical section
            xSemaphoreGive(mutex_DAC_value);
        }
    
        write_dac1_value(dac_value);
        vTaskDelay(100);
    }
}
