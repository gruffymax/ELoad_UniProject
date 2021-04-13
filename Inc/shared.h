/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * shared.h
 */

#ifndef SHARED_H
#define SHARED_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/******************** User Interface State *******************************************/
enum run_e
{
    stopped,
    running
};

enum mode_e
{
    mode_cc,
    mode_cv,
    mode_cr,
    mode_cp
};

struct UI_State_s
{
    enum mode_e mode;
    enum run_e run_state;
    uint32_t setting_current0;
    uint32_t setting_current1;
    uint32_t setting_voltage;
    uint32_t setting_power;
    uint32_t setting_resistance;
    uint8_t selected_set_point;
    uint8_t cursor_pos;
    uint8_t setting_values[2][5];
    uint8_t voltage_mode_calibration_run;
};
extern struct UI_State_s ui_state; // Global definition


#endif //SHARED_H
