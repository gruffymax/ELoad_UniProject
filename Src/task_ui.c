#include "task_ui.h"
#include "ui_state.h"

static uint32_t dac_setting = 0;
void task_ui(void *argument)
{
    initialise_display();
    while(1)
    {
        // TODO 
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
        dac_setting = evaluate_ui(&ui_data);
        generate_display();
        vTaskDelay(100);
        
    }

}

uint32_t get_dac_setting(void)
{
    return dac_setting;
}
