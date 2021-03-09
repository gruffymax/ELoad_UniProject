#include "task_lcd.h"
#include "display.h"

void task_lcd(void* argument)
{
    lcd_init();
    
    while(1)
    {
        if (ui_state.run_state == 1)
        {
            //TODO Active display mode
        }
        else
        {
            // Static display mode
            
        }
        vTaskDelay(50);
    }
}
