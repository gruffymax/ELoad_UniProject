/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * task_ui.c
 */
#include "task_ui.h"
#include "shared.h"
#include "interrupts.h"
#include "stm32g0xx.h"
#include "FreeRTOS.h"
#include "task.h"

/* Static functions */
static void increase_value(void);
static void decrease_value(void);
static void change_setting_value(uint8_t dec);
static void increment_cursor_pos(void);
static uint8_t min_cursor_pos(void);
static void reset_setting_values(void);
static uint32_t evaluate_ui(TaskHandle_t *task_lcd_handle);
static uint8_t sanity_check(uint32_t setting, enum mode_e mode);
uint8_t calculate_setting_value(void);

void task_ui(void *task_lcd_handle)
{
    TickType_t LastWakeTime = xTaskGetTickCount();

    while(1)
    {
        evaluate_ui(task_lcd_handle);
        vTaskDelayUntil(&LastWakeTime, 100);
    }
}

static uint32_t evaluate_ui(TaskHandle_t *task_lcd_handle)
{
    uint8_t previous_digit = 0; 
    /* CW event */
    if (get_event_cw())
    {
        clear_event_cw(); // Clear the event flag
        if (ui_state.run_state == 0)
        {
            // Save current digit so we can revert if sanity check fails
            previous_digit = ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos];  
            increase_value(); // Increase current value digit
            if (calculate_setting_value())
            {
                ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos] = previous_digit;
            }
        }
    }
    
    /* CCW event */
    if (get_event_ccw())
    {
        clear_event_ccw(); // Clear the event flag
        if (ui_state.run_state == 0)
        {
            // Save current digit so we can revert if sanity check fails
            previous_digit = ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos];  
            decrease_value();  // Decrease current value digit
            if (calculate_setting_value())
            {
                ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos] = previous_digit;
            }
        }
    }
    
    /* RE Button */
    if (get_event_button_encoder())
    {
        clear_event_button_encoder(); // Clear the event flag
        if (ui_state.run_state == 0)
        {
            increment_cursor_pos();
        }
        else
        {
            ui_state.selected_set_point = !ui_state.selected_set_point;
        }
    }
    
    /* Start button */
    if (get_event_button_start())
    {
        clear_event_button_start(); // CLear the event flag
        ui_state.run_state = !ui_state.run_state; //Toggle run mode_state
        if (ui_state.run_state)
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1); // Turn on LED
        }
        else
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1); // Turn off LED
            ui_state.voltage_mode_calibration_run = 0; // Reset calibration
        }
    }
    
    /* CC button */
    if (get_event_button_cc())
    {
        clear_event_button_cc();
        if (ui_state.run_state == 0 && ui_state.mode == mode_cc)
        {
            ui_state.selected_set_point = !ui_state.selected_set_point;
            ui_state.cursor_pos = 1;
        }
        else if (ui_state.run_state == 0 && ui_state.mode != mode_cc)
        {
            ui_state.mode = mode_cc;
            ui_state.cursor_pos = 1;
            ui_state.selected_set_point = 0;
            reset_setting_values();
        }
        
    }
    
    /* CV button */
    if (get_event_button_cv())
    {
        clear_event_button_cv();
        if (ui_state.run_state == 0 && ui_state.mode != mode_cv)
        {
            ui_state.mode = mode_cv;
            ui_state.cursor_pos = 0;
            ui_state.selected_set_point = 0;
        }
    }
    
    /* CP button */
    if (get_event_button_cp())
    {
        clear_event_button_cp();
        if (ui_state.run_state == 0 && ui_state.mode != mode_cp)
        {
            ui_state.mode = mode_cp;
            ui_state.cursor_pos = 0;
            ui_state.selected_set_point = 0;
            reset_setting_values();
        }
    }
    
    /* CR button */
    if (get_event_button_cr())
    {
        clear_event_button_cr();
        if (ui_state.run_state == 0 && ui_state.mode != mode_cr)
        {
            ui_state.mode = mode_cr;
            ui_state.cursor_pos = 0;
            ui_state.selected_set_point = 0;
            reset_setting_values();
        }
    }
    return 0;
}

static void increase_value(void)
{
    if (ui_state.run_state == 0)
    {
       change_setting_value(0);
    }
}

static void decrease_value(void)
{
    if (ui_state.run_state == 0)
    {
        change_setting_value(1);
    }
}

static void change_setting_value(uint8_t dec)
{
    if (dec)
    {
        if (ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos] == 0)
        {
            ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos] = 9;
        }
        else
        {
            ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos]--;
        }
    }
    else
    {
        if (ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos] == 9)
        {
            ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos] = 0;
        }
        else
        {
            ui_state.setting_values[ui_state.selected_set_point][ui_state.cursor_pos]++;
        }
    }
}


static void increment_cursor_pos(void)
{
    uint8_t min = min_cursor_pos();
    if (ui_state.cursor_pos >= 4)
    {
        ui_state.cursor_pos = min;
    }
    else
    {
        ui_state.cursor_pos++;
    }
}

static uint8_t min_cursor_pos(void)
{
    if (ui_state.mode == mode_cc)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void reset_setting_values(void)
{
    uint8_t i=0, j=0;
    for (i=0; i<2; i++)
    {
        for (j=0; j<5; j++)
        {
            ui_state.setting_values[i][j] = 0;
        }
    }
}

uint8_t calculate_setting_value(void)
{
    uint32_t setting0 = (ui_state.setting_values[0][0] * 10000) + (ui_state.setting_values[0][1] * 1000) + (ui_state.setting_values[0][2] * 100) + (ui_state.setting_values[0][3] * 10) + ui_state.setting_values[0][4];
    uint32_t setting1 = (ui_state.setting_values[1][0] * 10000) + (ui_state.setting_values[1][1] * 1000) + (ui_state.setting_values[1][2] * 100) + (ui_state.setting_values[1][3] * 10) + ui_state.setting_values[1][4];
    switch (ui_state.mode)
    {
        case mode_cc:
            if (sanity_check(setting0, mode_cc))
            {
                return 1;
            }
            if (sanity_check(setting1, mode_cc))
            {
                return 1;
            }
            ui_state.setting_current0 = setting0;
            ui_state.setting_current1 = setting1;
            break;
            
        case mode_cv:
            if (sanity_check(setting0, mode_cv))
            {
                return 1;
            }
            ui_state.setting_voltage = setting0;
            break;
            
        case mode_cp:
            if (sanity_check(setting0, mode_cp))
            {
                return 1;
            }
            ui_state.setting_power = setting0;
            break;
            
        case mode_cr:
            if (sanity_check(setting0, mode_cr))
            {
                return 1;
            }
            ui_state.setting_resistance = setting0;
            break;
            
        default:
            break;
    }
    return 0;
}

uint8_t sanity_check(uint32_t setting, enum mode_e mode)
{
    switch(mode)
    {
        case mode_cc:
            if (setting > 2047)
            {
                return 1;
            }
            break;
        case mode_cv:
            if (setting > 20000)
            {
                return 1;
            }
            break;
        case mode_cp:
            if (setting > 10000)
            {
                return 1;
            }
            break;
        case mode_cr:
            if (setting > 10000)
            {
                return 1;
            }
            break;
        default:
            return 1;
    }
    return 0;
}
