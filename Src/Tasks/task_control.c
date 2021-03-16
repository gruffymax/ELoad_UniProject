#include "task_control.h"

static uint32_t control_loop_cc(void);
static uint32_t pid_control_loop(uint16_t v, uint16_t i);

uint32_t dac_setting = 0;

void task_control(void *argument)
{
    uint16_t current_v = 0;
    uint16_t current_i = 0;
    
    while (1)
    {
        /* Get ADC values */
        convert_voltage();
        convert_current();
        current_v = get_voltage();
        current_i = get_current();
        
        if (ui_state.run_state == running)
        {
            if (ui_state.mode == mode_cc)
            {
                dac_setting = control_loop_cc();
            }
            else
            {
                dac_setting = pid_control_loop(current_v, current_i);
            }

            if (dac_setting > 2047)
	    {	
		write_dac1_value(2047 * 2);
	    }
	    else
	    {
		write_dac1_value(dac_setting * 2);
	    }
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
    
static uint32_t pid_control_loop(uint16_t v, uint16_t i1)
{
    const float kc = 0.35;   //Proportional Gain
    const float ki = 5;   //Integral Gain
    const float kd = 0.08; //Derivative Gain
    static float ui = 0;  //Integral Part
    float up = 0;         //Proportional part
    float ud = 0;         //Derivative Part
    float e = 0;          //Error
    static float e_old = 0;      //Previous error
    float is = 0;        //Set point
    float i = (float)i1 / 1000.0;
    switch (ui_state.mode)
    {
        case mode_cp:
            is = (float)ui_state.setting_power / (float)v;
            break;

        case mode_cr:
            is = (float)v / ((float)ui_state.setting_resistance * 1000);
            break;

        case mode_cv:
            is = 0;
	    break;

        default:
            break;
    }

    e = is - i; //Calculate error
    
    up = kc*e;  //Calculate Proportional part
    
    ui = ui + (kc/ki) * e; //Calculate Integral part
    
    //ud = kc * kd * ((e - e_old)); //Calculate Derivative part
    //e_old = e;
    
    return (uint32_t)((is + up + ui)*1000);
    
}
