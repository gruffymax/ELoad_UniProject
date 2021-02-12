#include "proj_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "dac.h"
#include "display.h"


uint16_t counter = 0;


void task1( *argument)
{
    struct displayData_s displayData;
    displayData->line1 = "Hello World";
    
    
    us_delay(150000);
    lcd_init();
    while(1)
    {
        
        write_display
    }

}
