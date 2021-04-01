#include "task_control.h"
#include "adc.h"
#include "pi.h"

/* Static Functions */
static uint32_t control_loop_cc(void);
static float calculate_resistance(void);

/* Variables */
uint32_t dac_setting = 0;
uint32_t current_dac_setting = 0;
static float voltage_in = 0.0;

void task_control(void *argument)
{
    uint16_t current_v = 0;
    uint16_t current_i = 0;
    float r = 1000.0;
    
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
            switch (ui_state.mode)
            {
              case mode_cc:
                dac_setting = control_loop_cc();
                break;
              case mode_cp:
                dac_setting = pi_loop(calc_input_from_power(current_v), (float)current_i/1000);
                break;
              case mode_cr:
                dac_setting = pi_loop(calc_input_from_resistance(current_v), (float)current_i/1000);
                break;
              case mode_cv:
                if (!ui_state.voltage_mode_calibration_run)
                {
                  r = calculate_resistance();
                }
                float v = voltage_in - ((float)ui_state.setting_voltage / 1000.0);
                dac_setting = pi_loop(v / r, (float)current_i/1000);
                break;
              default:
                break;
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
          voltage_in = (float)get_voltage() / 1000;
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

static float calculate_resistance(void)
{
  write_dac1_value(0);
  vTaskDelay(100);
  convert_voltage();
  float v = (float)get_voltage() / 1000;

  write_dac1_value(4095);
  vTaskDelay(100);
  convert_current();
  write_dac1_value(0);
  float i = (float)get_current() / 1000.0;
 
  float r = 0;
  r = v / i;
  
  ui_state.voltage_mode_calibration_run = 1;
  return r;
}

