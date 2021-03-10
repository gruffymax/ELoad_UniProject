#include "task_dac.h"
#include "dac.h"
#include "shared.h"
#include "semphr.h"


static uint32_t local_dac_value = 0; 
SemaphoreHandle_t dac_access_semphr = NULL;

void task_dac(void *arguments)
{
    dac_access_semphr = xSemaphoreCreateMutex();
    uint32_t dac_setting = 0x7D0;
    
    while(1)
    {
        /* Critial block */
        while(xSemaphoreTake(dac_access_semphr, 0) != pdTRUE)
        {
            //Wait until semaphore free
        }
        local_dac_value = dac_setting;
        xSemaphoreGive(dac_access_semphr);
        
        if (ui_state.run_state == 1)
        {
            write_dac1_value(local_dac_value);
        }
        else
        {
            write_dac1_value(0);
        }
        
        vTaskDelay(100);
    }
}
