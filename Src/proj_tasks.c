#include "proj_tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "dac.h"
#include "display.h"


uint16_t counter = 0;


void task1( *argument)
{
    us_delay(150000);
    lcd_initialise(&lcd_interface);
    send_line1("Hello World");
    send_line2("Line2");
    send_line3("Line3");
    send_line4("Line4")
}
