/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * display.c
 */
#include "display.h"

    struct st7066u_iface lcd_interface = {
        set_lcd_rw,
        set_lcd_en,
        set_lcd_rs,
        set_lcd_d4,
        set_lcd_d5,
        set_lcd_d6,
        set_lcd_d7,
        set_d4_mode,
        set_d5_mode,
        set_d6_mode,
        set_d7_mode,
        is_d7_set,
        us_delay
    };


void lcd_init(void)
{
    us_delay(150000);
    lcd_initialise(&lcd_interface);
}

void write_char(char character)
{
    send_char(character);
}

void set_cursor(char pos)
{
    set_instruction(pos | 0x80);
}

void show_cursor(void)
{
    set_instruction(0x0E); // Display ON, Cursor ON, Blink OFF
}
void hide_cursor(void)
{
    set_instruction(0x0C); // Display ON, Cursor OFF, Blink OFF
}

void write_display(struct displayData_s *displayData)
{
    set_instruction(0x0C); // Display ON, Cursor OFF, Blink OFF
    set_instruction(0x01); // Clear display
    send_line1(displayData->line1);
    send_line2(displayData->line2);
    send_line3(displayData->line3);
    send_line4(displayData->line4);
}
void set_lcd_rw(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS4);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR4);
    }
}

void set_lcd_rs(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS5);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR5);
    }
}

void set_lcd_en(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS3);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR3);
    }
}

void set_lcd_d4(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS6);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR6);
    }
}

void set_lcd_d5(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR7);
    }
}

void set_lcd_d6(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS8);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR8);
    }
}

void set_lcd_d7(uint8_t state)
{
    if (state)
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS9);
    }
    else
    {
        SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR9);
    }
}
void set_d4_mode(uint8_t mode)
{
    if (mode)
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6, 0x0);
    }
    else
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6, GPIO_MODER_MODE6_0);
    }
}

void set_d5_mode(uint8_t mode)
{
    if (mode)
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7, 0x0);
    }
    else
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7, GPIO_MODER_MODE7_0);
    }
}

void set_d6_mode(uint8_t mode)
{
    if (mode)
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE8, 0x0);
    }
    else
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE8, GPIO_MODER_MODE8_0);
    }
}

void set_d7_mode(uint8_t mode)
{
    if (mode)
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE9, 0x0);
    }
    else
    {
        MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE9, GPIO_MODER_MODE9_0);
    }
}

uint8_t is_d7_set(void)
{
    return (READ_BIT(GPIOB->IDR, GPIO_IDR_ID9) != 0);
}

void us_delay(uint32_t us)
{
    uint32_t count = 0;
    while (count < us * 3)
    {
        count++;
    }
}
