#include "task_lcd.h"
#include "display.h"
#include <string.h>
#include <stdio.h>

static void update_input_line(void);
static void generate_input_line(char *buffer);

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
            /* Static display mode 
             * -------------------
             * Only updates display in response to a user input event.
             * LCD task is suspended until an event occurs.
             */
            update_input_line();
            vTaskSuspend(NULL);
        }
    }
}

static void update_input_line(void)
{
    char buffer[21] = {0};
    generate_input_line(buffer);
    clear_line4();
    uint8_t i;
    for (i=0; i<strlen(buffer); i++)
    {
        write_char(buffer[i]);
    }
    if (ui_state.selected_set_point == 0)
    {
        set_cursor(LINE4 + ui_state.cursor_pos);
    }
    else
    {
        set_cursor(LINE4 + ui_state.cursor_pos + 10);
    }
    show_cursor();
}


static void generate_input_line(char *buffer)
{
    switch (ui_state.mode)
    {
        case mode_cc:
            sprintf(buffer, "%05dmA   %05dmA", ui_state.setting_current0, ui_state.setting_current1);
            break;
            
        case mode_cv:
            sprintf(buffer, "%05dmV", ui_state.setting_voltage);
            break;
            
        case mode_cp:
            sprintf(buffer, "%05dmW", ui_state.setting_power);
            break;
            
        case mode_cr:
            sprintf(buffer, "%05dOhms", ui_state.setting_resistance);
            break;
            
        default:
            break;
    }
}
