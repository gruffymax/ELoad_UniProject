#include "task_events.h"
#include "FreeRTOS.h"
#include "task.h"
#include "interrupts.h"

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
    while(1)
    {
        check_cw_event();
        check_ccw_event();
        check_button_cc();
        check_button_cv();
        check_button_cr();
        check_button_cp();
        xTaskDelay(10);
    }
}

static void check_cw_event(void)
{
    if (get_event_cw() == SET)
    {
        clear_event_cw();
        /* TODO - Callback */
    }
}

static void check_ccw_event(void)
{
    if (get_event_ccw() == SET)
    {
        clear_event_ccw();
        /* TODO - Callback */
    }
}

static void check_button_encoder(void)
{
    if (get_event_button_encoder() == SET)
    {
        clear_event_button_encoder();
        /* TODO - Callback */
    }
}

static void check_button_start(void)
{
    if (get_event_button_start() == SET)
    {
        clear_event_button_start();
        /* TODO - Callback */
    }
}

static void check_button_cc(void)
{
    if (get_event_button_cc() == SET)
    {
        clear_event_button_cc();
        /* TODO - Callback */
    }
}

static void check_button_cv(void)
{
    if (get_event_button_cv() == SET)
    {
        clear_event_button_cv();
        /* TODO - Callback */
    }
}

static void check_buttin_cr(void)
{
    if (get_event_button_cr() == SET)
    {
        clear_event_button_cr();
        /* TODO - Callback */
    }
}

static void check_button_cp(void)
{
    if (get_event_button_cp() == SET)
    {
        clear_event_button_cp();
        /* TODO - Callback */
    }
}
