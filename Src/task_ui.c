#include "task_ui.h"
#include "ui_state.h"
//#include "el_sem.h"
#include "adc.h"

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
        
        struct ui_data_t ui_data;
        
        /* Start critical section */
        if (1)//take_data_mutex())
        {
            ui_data.src_voltage = convert_voltage();
            ui_data.src_current = convert_current();
            //give_data_mutex(); // Return data mutex
        }
        /* End of critial section */
        
        dac_setting = evaluate_ui(&ui_data);
        generate_display(&ui_data);
        vTaskDelay(100);
    }

}

uint32_t get_dac_setting(void)
{
    return dac_setting;
}
