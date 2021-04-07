/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * pi.c
 */
#include <stdint.h>
#include "pi.h"
#include "shared.h"

static float proportional_term(float e);
static float integral_term(float e);

float kc = (float)0.35;    // Proportional Gain
float ki = (float)5.0;       // Integral Gain

uint16_t pi_loop(float input, float output)
{
   float e = (float)input - (float) output;
   float feedback = proportional_term(e) + integral_term(e);
   
   return (uint16_t)((input + feedback) * 1000.0);
}

static float proportional_term(float e)
{
  return e*kc;
}

static float integral_term(float e)
{
  static float ui = 0.0;
  
  ui = ui + (kc/ki) * e;
  return ui;
}

float calc_input_from_power(uint16_t measured_voltage)
{
  float p = (float)ui_state.setting_power / 1000.0;
  float v = (float)measured_voltage / 1000.0;

  return p/v;
}

float calc_input_from_resistance(uint16_t measured_voltage)
{
  float r = (float)ui_state.setting_resistance;
  float v = (float)measured_voltage / 1000.0;

  return v/r;
}

