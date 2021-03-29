#include "task_control.h"
#include "adc.h"

/* Static Functions */
static uint32_t control_loop_cc(void);
static uint32_t pi_control_loop(uint16_t v, uint16_t i);
static float p_voltage_control_loop(uint16_t v);

/* Variables */
uint32_t dac_setting = 0;
uint32_t current_dac_setting = 0;


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
        /* If power is greater than 11W, stop the device */
        if (current_v * current_i > 11000000)
        {
            ui_state.run_state = stopped;
        }

        if (ui_state.run_state == running)
        {
            if (ui_state.mode == mode_cc)
            {
                dac_setting = control_loop_cc();
            }
            else if (ui_state.mode == mode_cv)
            {
              dac_setting = current_dac_setting + p_voltage_control_loop(current_v);
              current_dac_setting = dac_setting;
            }
            else
            {
                dac_setting = pi_control_loop(current_v, current_i);
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
        vTaskDelay(10);
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
    
static uint32_t pi_control_loop(uint16_t v, uint16_t i1)
{
    const float kc = 0.35;//Proportional Gain
    float up = 0;         //Proportional part
    const float ki = 5;   //Integral Gain
    static float ui = 0;  //Integral Part
    float e = 0;          //Error
    float is = 0;         //Set point
    float i = (float)i1 / 1000.0;
    switch (ui_state.mode)
    {
        case mode_cp:
            is = (float)ui_state.setting_power / (float)v;
            break;

        case mode_cr:
            is = (float)v / ((float)ui_state.setting_resistance * 1000);
            break;
        default:
            break;
    }
    
    if (ui > 1 || ui < -1)
    {
        ui = 0;
    }
    
    e = is - i; //Calculate error
    up = kc*e;  //Calculate Proportional part
    ui = ui + (kc/ki) * e; //Calculate Integral part
    
    return (uint32_t)((is + up + ui)*1000);
    
}

static float p_voltage_control_loop(uint16_t v)
{
  int total = 0;
  static float avg;
  static int pos = 0;
  static uint16_t v_buffer[3] = {0};
  static int count = 0;
  v_buffer[pos] = v;
  
  if (pos == 3)
  {
    pos = 0;
  }
  else
  {
    pos++;
  }

  if (count < 3)
  {
    count++;
  }

  if (count >= 3)
  {
    for (int i=0; i<3; i++)
    {
      total = total + v_buffer[i];
    }
    
    if (ui_state.setting_voltage < (total / 3))
    {
      return 1;
    }
    else if (ui_state.setting_voltage == (total/3))
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }
}
