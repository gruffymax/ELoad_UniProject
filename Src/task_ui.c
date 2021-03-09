#include "task_ui.h"
#include "shared.h"
#include "semphr.h"
#include "interrupts.h"
#include "stm32g0xx.h"

/* Static functions */
static void increase_value(void);
static void decrease_value(void);
static void change_setting_value(uint8_t dec);
static void increment_cursor_pos(void);


SemaphoreHandle_t uistate_access_semphr = NULL;
struct UI_State_s ui_state =
{
    mode_cc,
    stopped,
    0,
    0,
    0,
    0,
    0,
    0,
    {{0},{0}}
};

void task_ui(void *argument)
{
    //initialise_display();
    uistate_access_semphr = xSemaphoreCreateMutex();
    
    while(1)
    {
        // TODO 
        // Get Settings (Mutex)
        // Get Data (Mutex)
        // Set system state
        // Set DAC setting
        // Generate display output
        // Update LCD

        /* Start critical section */
        while(xSemaphoreTake(uistate_access_semphr, 0) != pdTRUE)
        {
            evaluate_ui();
        }
        xSemaphoreGive(uistate_access_semphr); // Return semaphore
        vTaskDelay(100);
    }

}

uint32_t evaluate_ui(void)
{
    /* CW event */
    if (get_event_cw())
    {
        clear_event_cw(); // Clear the event flag
        if (ui_state.run_state == 0)
        {
            increase_value(); // Increase current value digit
        }
    }
    
    /* CCW event */
    if (get_event_ccw())
    {
        clear_event_ccw(); // Clear the event flag
        if (ui_state.run_state == 0)
        {
            decrease_value();  // Decrease current value digit
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
        }
    }
    
    if (get_event_button_cc())
    {
        clear_event_button_cc();
        if (ui_state.run_state == 0 && ui_state.mode == mode_cc)
        {
            ui_state.selected_set_point = !ui_state.selected_set_point;
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
    if (ui_state.cursor_pos == 3)
    {
        ui_state.cursor_pos = 0;
    }
    else
    {
        ui_state.cursor_pos++;
    }
}
