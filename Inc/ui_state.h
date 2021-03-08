#ifndef UI_STATE_H
#define UI_STATE_H

#include <stdint.h>
#include "stm32g0xx.h"

#define VALUE0_POS 0x00
#define VALUE1_POS 0x40

struct ui_data_t
{
    uint32_t src_voltage;
    uint32_t src_current;
};

void initialise_display(void);
uint32_t evaluate_ui(struct ui_data_t *ui_data);
void generate_display(struct ui_data_t *ui_data);

#endif //UI_STATE_H
