#include "ui_state.h"
#include "interrupts.h"

/* Static functions */
static void increase_value(void);
static void increment_value_0_thou(void);

enum mode_e{mode_cc, mode_cv, mode_cr, mode_cp};
static enum mode_e mode_state = mode_cc;

static uint8_t run_state = 0;
static uint16_t setting_current = 0;
static uint16_t setting_voltage = 0;
static uint16_t setting_power = 0;
static uint16_t setting_resistance = 0;

static uint8_t current_value = 0;
static uint8_t value_0_cursor_pos = 0;
static uint8_t value_1_cursor_pos = 0;

static uint8_t value_0_thousands = 0;
static uint8_t value_0_hundreds  = 0;
static uint8_t value_0_tens      = 0;
static uint8_t value_0_units     = 0;

static uint8_t value_1_thousands = 0;
static uint8_t value_1_hundreds  = 0;
static uint8_t value_1_tens      = 0;
static uint8_t value_1_units     = 0;

uint32_t evaluate_ui(struct ui_data_t *ui_data)
{
    /* CW event */
    if (get_event_cw())
    {
        clear_event_cw(); // Clear the event flag
        increase_value(); // Increase current value digit
    }
}

static void increase_value(void)
{
    if (run_state == 0 && current_value == 0)
    {
        switch (value_0_cursor_pos)
        {
            case 0:
                increment_value_0_thou();
                break;
                
            case 1:
                
    }
}

static void increment_value_0_thou(void)
{
    if (value_0_thousands == 9)
    {
        value_0_thousands = 0;
    }
    else
    {
        value_0_thousands++;
    }
}
