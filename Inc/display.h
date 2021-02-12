#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "stm32g0xx.h"
#include "st7066u_lcd.h"

struct displayData_s
{
    char line1[20];
    char line2[20];
    char line3[20];
    char line4[20];
};

void lcd_init(void);
void write_display(struct displayData_s *displayData);

void set_lcd_rw(uint8_t state);
void set_lcd_rs(uint8_t state);
void set_lcd_en(uint8_t state);
void set_lcd_d4(uint8_t state);
void set_lcd_d5(uint8_t state);
void set_lcd_d6(uint8_t state);
void set_lcd_d7(uint8_t state);
void set_d4_mode(uint8_t mode);
void set_d5_mode(uint8_t mode);
void set_d6_mode(uint8_t mode);
void set_d7_mode(uint8_t mode);
uint8_t is_d7_set(void);
void us_delay(uint32_t us);

#endif //DISPLAY_H
