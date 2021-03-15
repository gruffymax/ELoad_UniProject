#include "task_control.h"

void task_control(void *argument)
{
    SemaphoreHandle_t uistate_access_semphr;
    struct UI_State_s local_ui_State;
    
    while (1)
    {
        /* ---Start Critial Section--- */
        while (xSemaphoreTake(uistate_access_semphr, 0) != pdPASS)
        {
            // Wait until semaphore taken
        }
        local_ui_State = ui_state;
        xSemaphoreGive(uistate_access_semphr);
        /* ---End Critial Section--- */
        
        
        vTaskDelay(50);
    }
}
