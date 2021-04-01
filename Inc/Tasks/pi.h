#ifndef PI_H
#define PI_H

uint16_t pi_loop(float input, float output);
float calc_input_from_power(uint16_t measured_voltage);
float calc_input_from_resistance(uint16_t measured_voltage);

#endif //PI_H
