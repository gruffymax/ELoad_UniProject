#include "task_ui.h"
#include "ui_state.h"

void task_ui(void *argument)
{
    while(1)
    {
        // TODO 
        // Get event notification
        // Get Settings (Mutex)
        // Get Data (Mutex)
        // Set system state
        // Set DAC setting
        // Generate display output
        // Update LCD
        // Task delay 100
        
        struct ui_data_t ui_data;
        ui_data.src_voltage = 0;  //TODO
        ui_data.src_current = 0;  //TODO
        
    }

}
