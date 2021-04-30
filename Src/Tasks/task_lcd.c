/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * task_lcd.c
 */
#include "task_lcd.h"
#include "display.h"
#include <string.h>
#include <stdio.h>
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"

static void update_static_display(void);
static void generate_static_display(void);
static void generate_static_line1(void);
static void generate_static_line2(void);
static void generate_static_line3(void);
static void generate_static_line4(void);

static void update_active_display(void);
static void generate_active_display(void);
static void generate_active_line1(void);
static void generate_active_line2(void);
static void generate_active_line3(void);
static void generate_active_line4(void);

struct displayData_s displayData = {
    {0x20},
    {0x20},
    {0x20},
    {0x20}
};

void task_lcd(void* argument)
{
    lcd_init();
    TickType_t LastWakeTime = xTaskGetTickCount();

    while(1)
    {
        if (ui_state.run_state == 1)
        {
            /* Active display mode
             * ----------------------
             * Update the display regularly (200ms)
             */
            update_active_display();
            vTaskDelayUntil(&LastWakeTime, 200);
        }
        else
        {
            /* Static display mode 
             * -------------------
             * Only updates display in response to a user input event.
             * LCD task is suspended until an event occurs.
             */
            update_static_display();
            vTaskDelayUntil(&LastWakeTime, 200);
        }
    }
}

static void update_static_display(void)
{
    generate_static_display();
    write_display(&displayData);
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

static void generate_static_display(void)
{
    generate_static_line1();
    generate_static_line2();
    generate_static_line3();
    generate_static_line4();
}

static void generate_static_line1(void)
{
    switch (ui_state.mode)
    {
        case mode_cc:
            strcpy(displayData.line1, "CC mode      STOPPED");
            break;
            
        case mode_cv:
            strcpy(displayData.line1, "CV mode      STOPPED");
            break;
            
        case mode_cp:
            strcpy(displayData.line1, "CP mode      STOPPED");
            break;
            
        case mode_cr:
            strcpy(displayData.line1, "CR mode      STOPPED");
            break;
            
        default:
            break;
    }
}

static void generate_static_line2(void)
{
    uint8_t i;
    for (i=0; i<20; i++)
    {
        displayData.line2[i] = 0x20;
    }
    displayData.line2[20] = 0x00;
}

static void generate_static_line3(void)
{
    switch (ui_state.mode)
    {
        case mode_cc:
            strcpy(displayData.line3, " Set 1      Set 2   ");
            break;
            
        case mode_cv:
            strcpy(displayData.line3, " Set 1              ");
            break;
            
        case mode_cp:
            strcpy(displayData.line3, " Set 1              ");
            break;
            
        case mode_cr:
            strcpy(displayData.line3, " Set 1              ");
            break;
            
        default:
            break;
    }
}

static void generate_static_line4(void)
{
    switch (ui_state.mode)
    {
        case mode_cc:
            sprintf(displayData.line4, "%05d mA  %05d mA", (int)ui_state.setting_current0, (int)ui_state.setting_current1);
            break;
            
        case mode_cv:
            sprintf(displayData.line4, "%05d mV", (int)ui_state.setting_voltage);
            break;
            
        case mode_cp:
            sprintf(displayData.line4, "%05d mW", (int)ui_state.setting_power);
            break;
            
        case mode_cr:
            sprintf(displayData.line4, "%05d Ohms", (int)ui_state.setting_resistance);
            break;
            
        default:
            break;
    }
}

void update_active_display(void)
{
    generate_active_display();
    write_display(&displayData);
}

void generate_active_display(void)
{
    
    generate_active_line1();
    generate_active_line2();
    generate_active_line3();
    generate_active_line4();
}

static void generate_active_line1(void)
{
    switch (ui_state.mode)
    {
        case mode_cc:
            strcpy(displayData.line1, "CC mode      RUNNING");
            break;
            
        case mode_cv:
            strcpy(displayData.line1, "CV mode      RUNNING");
            break;
            
        case mode_cp:
            strcpy(displayData.line1, "CP mode      RUNNING");
            break;
            
        case mode_cr:
            strcpy(displayData.line1, "CR mode      RUNNING");
            break;
            
        default:
            break;
    }
}

static void generate_active_line2(void)
{
    strcpy(displayData.line2, "                    ");
}

static void generate_active_line3(void)
{
    sprintf(displayData.line3, "%04d mA   %05d mV", (int)get_current(), (int)get_voltage());
}

static void generate_active_line4(void)
{
    uint16_t power = (get_voltage() * get_current())/1000;
    uint16_t resistance = get_voltage() / get_current();
    sprintf(displayData.line4, "%05d Ohms  %05d mW", resistance, power); 
}
