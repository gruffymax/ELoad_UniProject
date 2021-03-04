#include "ui_state.h"
#include "interrupts.h"
#include "display.h"
#include <string.h>

/* Static functions */
static void increase_value(void);
static void decrease_value(void);
static void change_setting_value(uint8_t dec);
static void increment_cursor_pos(void);
static void update_lcd_char(void);

/* Static Variables */
enum mode_e{mode_cc, mode_cv, mode_cr, mode_cp};
static enum mode_e mode_state = mode_cc;

static uint8_t run_state = 0;
static uint16_t setting_current = 0;
static uint16_t setting_voltage = 0;
static uint16_t setting_power = 0;
static uint16_t setting_resistance = 0;

static uint8_t current_value = 0;
static uint8_t cursor_pos = 0;

static uint8_t setting_values[2][4] = {0}; 

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
        increase_value(); // Increase current value digit
        update_lcd_char();
    }
    
    /* CCW event */
    if (get_event_ccw())
    {
        clear_event_ccw(); // Clear the event flag
        decrease_value();  // Decrease current value digit
        update_lcd_char();
    }
    
    /* RE Button */
    if (get_event_button_encoder())
    {
        clear_event_button_encoder(); // Clear the event flag
        increment_cursor_pos();
        update_lcd_char();
    }
    
    uint32_t dac_value = (setting_values[0][0] * 1000) + (setting_values[0][1] * 100) + (setting_values[0][2] * 10) + setting_values[0][3];
    return dac_value * 2; //TODO
}

void generate_display(void)
{
    
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
        if (setting_values[current_value][cursor_pos] == 0)
        {
            setting_values[current_value][cursor_pos] = 9;
        }
        else
        {
            setting_values[current_value][cursor_pos]--;
        }
    }
    else
    {
        if (setting_values[current_value][cursor_pos] == 9)
        {
            setting_values[current_value][cursor_pos] = 0;
        }
        else
        {
            setting_values[current_value][cursor_pos]++;
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
    
    if (current_value == 0)
    {
        pos = 0x55;
    }
    else
    {
        pos = 0x5E;
    }
    pos = pos + cursor_pos;
    set_cursor(pos); //Set cursor position
    
    character = setting_values[current_value][cursor_pos] + 48;
    write_char(character); // Write the character, cursor will auto increment
    
    set_cursor(pos); // Return the cursor to the current position
}
