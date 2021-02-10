/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * Main
 */

#include "stm32g0xx.h"
#include "init.h"
//#include "FreeRTOS.h"
//#include "task.h"
#include "proj_tasks.h"
#include <stdint.h>
#include <stddef.h>
#include "st7066u_lcd.h"

int main(void)
{
    struct st7066u_iface lcd_interface = {
    set_lcd_rw,
    set_lcd_en,
    set_lcd_rs,
    set_lcd_d4,
    set_lcd_d5,
    set_lcd_d6,
    set_lcd_d7,
    set_d4_mode,
    set_d5_mode,
    set_d6_mode,
    set_d7_mode,
    is_d7_set,
    us_delay};
    
    init_system();
    
    lcd_interface.us_delay(10000);
    lcd_initialise(&lcd_interface);
    send_line1("Hello World");
    
    while(1);
}

void SysTick_Handler(void)
{
    
}
