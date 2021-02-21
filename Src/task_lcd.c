#include "task_lcd.h"
#include <string.h>

void task_lcd(void *argument)
{
    struct displayData_s displayData;
    strcpy(displayData.line1, "Hello World");
    strcpy(displayData.line2, "  Gareth");
    strcpy(displayData.line3, "    is  ");
    strcpy(displayData.line4, "   COOL ");
    
    us_delay(150000);
    lcd_init();
    while(1)
    {
        SEGGER_SYSVIEW_PrintfHost("Writing Display\n");
        write_display(&displayData);
        vTaskDelay(250);
    }

}
