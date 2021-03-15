#include "task_control.h"

static uint32_t control_loop_cc(void);
static uint32_t control_loop_cp(uint16_t v, uint16_t i);

uint32_t dac_setting = 0;


void task_control(void *argument)
{
    SemaphoreHandle_t uistate_access_semphr;
    struct UI_State_s local_ui_State;
    uint16_t current_v = 0;
    uint16_t current_i = 0;
    
    while (1)
    {
        /* ---Start Critial Section--- */
        //while (xSemaphoreTake(uistate_access_semphr, 0) != pdPASS)
        //{
            // Wait until semaphore taken
        //}
        local_ui_State = ui_state;
        //xSemaphoreGive(uistate_access_semphr);
        /* ---End Critial Section--- */
        
        /* Get ADC values */
        convert_voltage();
        convert_current();
        current_v = get_voltage();
        current_i = get_current();
        
        if (ui_state.run_state == running)
        {
            switch (ui_state.mode)
            {
                case mode_cc:
                    dac_setting = control_loop_cc();
                    break;
                    
                case mode_cp:
                    dac_setting = control_loop_cp(current_v, current_i);
                    break;
                    
                default:
                    break;
            }
            write_dac1_value(dac_setting * 2);
        }
        else
        {
            write_dac1_value(0);
        }
        
        
        vTaskDelay(25);
    }
}
static uint32_t control_loop_cc(void)
{
    if (ui_state.selected_set_point == 0)
    {
        return ui_state.setting_current0;
    }
    else
    {
        return ui_state.setting_current1;
    }
}
    
static uint32_t control_loop_cp(uint16_t v, uint16_t i1)
{
    const float kc = 1;   //Proportional Gain
    const float ki = 5;   //Integral Gain
    const float kd = 0.1;   //Derivative Gain
    static float ui_old = 0; //ui(k-1) 
    const float dt = 1;
    float is = 0;        //Set point
    float e = 0;          //Error
    static float e_old = 0;      //Previous error
    float up = 0;         //Proportional part
    float ui = 0;         //Integral Part
    float ud = 0;         //Derivative Part
    float i = (float)i1 / 1000.0;
    is = (float)ui_state.setting_power / v;
    e = is - i; //Calculate error
    
    up = kc*e;  //Calculate Proportional part
    
    ui = ui_old + (kc/ki) * e * dt; //Calculate Integral part
    ui_old = ui;
    
    ud = kc * kd * ((e - e_old) / dt); //Calculate Derivative part
    e_old = e;
    
    return (uint32_t)((is + up + ui + ud)*1000);
    
}
