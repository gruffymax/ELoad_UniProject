#include "ui_state.h"
#include "interrupts.h"
#include "display.h"
#include <stdio.h>
#include <string.h>

/* Static functions */
static void increase_value(void);
static void decrease_value(void);
static void change_setting_value(uint8_t dec);
static void increment_cursor_pos(void);
static void update_lcd_char(void);


void initialise_display(void)
{
    lcd_init();
    struct displayData_s displayData;
    strcpy(displayData.line1, "Mode-CC   STOPPED");
    strcpy(displayData.line2, "00000mW   00000mV");
    strcpy(displayData.line3, " 0000mA   00000mOhm");
    strcpy(displayData.line4, " 0000mA   0000mA");
    write_display(&displayData);
    set_cursor(0x55);
}

uint32_t evaluate_ui(struct ui_data_t *ui_data)
{
    /* CW event */
    if (get_event_cw())
    {
        clear_event_cw(); // Clear the event flag
        if (run_state == 0)
        {
            increase_value(); // Increase current value digit
            update_lcd_char();
        }
    }
    
    /* CCW event */
    if (get_event_ccw())
    {
        clear_event_ccw(); // Clear the event flag
        if (run_state == 0)
        {
            decrease_value();  // Decrease current value digit
            update_lcd_char();
        }
    }
    
    /* RE Button */
    if (get_event_button_encoder())
    {
        clear_event_button_encoder(); // Clear the event flag
        if (run_state == 0)
        {
            increment_cursor_pos();
            update_lcd_char();
        }
        else
        {
            selected_set_point = !selected_set_point;
        }
    }
    
    /* Start button */
    if (get_event_button_start())
    {
        clear_event_button_start(); // CLear the event flag
        run_state = !run_state; //Toggle run mode_state
        if (run_state)
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1); // Turn on LED
        }
        else
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1); // Turn off LED
        }
    }
    
    if (get_event_button_cc())
    {
        clear_event_button_cc();
        if (run_state == 0 && mode_state == mode_cc)
        {
            selected_set_point = !selected_set_point;
        }
    }
    
    uint32_t dac_value;
    if (selected_set_point == 0)
    {
        dac_value = (setting_values[0][0] * 1000) + (setting_values[0][1] * 100) + (setting_values[0][2] * 10) + setting_values[0][3];
    }
    else
    {
        dac_value = (setting_values[1][0] * 1000) + (setting_values[1][1] * 100) + (setting_values[1][2] * 10) + setting_values[1][3];
    }
    
    if (run_state)
    {
        return dac_value * 2;
    }
    return 0;
}

void generate_display(struct ui_data_t *ui_data)
{
    char buffer[6];
    sprintf(buffer, "%05d", (int)ui_data->src_voltage);
    set_cursor(0x40 + 0x0A);
    for (int i=0; i<5; i++)
    {
        write_char(buffer[i]);
    }
    
    sprintf(buffer, "%04d", (int)ui_data->src_current);
    set_cursor(0x15);
    for (int i=0; i<4; i++)
    {
        write_char(buffer[i]);
    }
}

static void increase_value(void)
{
    if (run_state == 0)
    {
       change_setting_value(0);
    }
}

static void decrease_value(void)
{
    if (run_state == 0)
    {
        change_setting_value(1);
    }
}

static void change_setting_value(uint8_t dec)
{
    if (dec)
    {
        if (setting_values[selected_set_point][cursor_pos] == 0)
        {
            setting_values[selected_set_point][cursor_pos] = 9;
        }
        else
        {
            setting_values[selected_set_point][cursor_pos]--;
        }
    }
    else
    {
        if (setting_values[selected_set_point][cursor_pos] == 9)
        {
            setting_values[selected_set_point][cursor_pos] = 0;
        }
        else
        {
            setting_values[selected_set_point][cursor_pos]++;
        }
    }
}


static void increment_cursor_pos(void)
{
    if (cursor_pos == 3)
    {
        cursor_pos = 0;
    }
    else
    {
        cursor_pos++;
    }
}

static void update_lcd_char(void)
{
    char pos = 0;
    char character = '0';
    
    if (selected_set_point == 0)
    {
        pos = 0x55;
    }
    else
    {
        pos = 0x5E;
    }
    pos = pos + cursor_pos;
    set_cursor(pos); //Set cursor position
    
    character = setting_values[selected_set_point][cursor_pos] + 48;
    write_char(character); // Write the character, cursor will auto increment
    
    set_cursor(pos); // Return the cursor to the current position
}
