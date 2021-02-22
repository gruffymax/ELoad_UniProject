#include "task_events.h"
#include "interrupts.h"

TaskHandle_t control_task_handle = NULL;

/* Static Variables */
static uint32_t event_flags = 0; // 32 bit notification value

/* Static functions */
static void check_cw_event(void);
static void check_ccw_event(void);
static void check_button_encoder(void);
static void check_button_start(void);
static void check_button_cc(void);
static void check_button_cv(void);
static void check_button_cr(void);
static void check_button_cp(void);


void task_events(void * argument)
{
    /* Notification bitfield
     * BIT 7: Button CP
     * BIT 6: Button CR
     * BIT 5: Button CV
     * BIT 4: Button CC
     * BIT 3: Button Start
     * BIT 2: RE_Button
     * BIT 1: CCW event
     * BIT 0: CW event
     */
    
    while(1)
    {
        check_cw_event();
        check_ccw_event();
        check_button_encoder();
        check_button_start();
        check_button_cc();
        check_button_cv();
        check_button_cr();
        check_button_cp();
        xTaskNotify(control_task_handle, event_flags, eSetValueWithOverwrite);
        vTaskDelay(25);
    }
}

static void check_cw_event(void)
{
    if (get_event_cw() == SET)
    {
        clear_event_cw();
        event_flags = event_flags | CW_EVENT_MASK; // Set Flag
    }
    else
    {
        event_flags = event_flags & !CW_EVENT_MASK; // Clear Flag
    }
}

static void check_ccw_event(void)
{
    if (get_event_ccw() == SET)
    {
        clear_event_ccw();
        event_flags = event_flags | CCW_EVENT_MASK;
    }
    else
    {
        event_flags = event_flags & !CCW_EVENT_MASK;
    }
}

static void check_button_encoder(void)
{
    if (get_event_button_encoder() == SET)
    {
        clear_event_button_encoder();
        event_flags = event_flags | RE_BUTTON_MASK;
    }
    else
    {
        event_flags = event_flags & !RE_BUTTON_MASK;
    }
}

static void check_button_start(void)
{
    if (get_event_button_start() == SET)
    {
        clear_event_button_start();
        event_flags = event_flags | BUTTON_START_MASK;
    }
    else
    {
        event_flags = event_flags & !BUTTON_START_MASK;
    }
}

static void check_button_cc(void)
{
    if (get_event_button_cc() == SET)
    {
        clear_event_button_cc();
        event_flags = event_flags | BUTTON_CC_MASK;
    }
    else
    {
        event_flags = event_flags & !BUTTON_CC_MASK;
    }
}

static void check_button_cv(void)
{
    if (get_event_button_cv() == SET)
    {
        clear_event_button_cv();
        event_flags = event_flags | BUTTON_CV_MASK;
    }
    else
    {
        event_flags = event_flags & !BUTTON_CV_MASK;
    }
}

static void check_button_cr(void)
{
    if (get_event_button_cr() == SET)
    {
        clear_event_button_cr();
        event_flags = event_flags | BUTTON_CR_MASK;
    }
    else
    {
        event_flags = event_flags & !BUTTON_CR_MASK;
    }
}

static void check_button_cp(void)
{
    if (get_event_button_cp() == SET)
    {
        clear_event_button_cp();
        event_flags = event_flags | BUTTON_CP_MASK;
    }
    else
    {
        event_flags = event_flags & !BUTTON_CP_MASK;
    }
}
