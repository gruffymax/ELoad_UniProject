#include "task_control.h"

uint32_t ctrl_dac_value = 0;

void task_control(void *arguments)
{
    uint32_t event_flags = 0;
    while(1)
    {
        /* TODO
         * Get notification value
         * Set Mode
         * Respond to RE button
         * Respond to Start button
         */
        event_flags = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        
    }
}
