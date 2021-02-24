/*!
 * @file st7066u_lcd.c
 * @brief ST7066 LCD Driver
 *
 * @author Gareth Waymark
 */
#include "st7066u_lcd.h"

#include <string.h>

/*!
 * @brief Append a single character to the current LCD display buffer
 * @param[in] letter: The character to apped to the LCD display buffer
 */
static void send_char(char letter);

/*!
 * @brief Check if LCD busy
 * @return 0: Ready. 1: Busy.
 */
static uint8_t check_busy_flag(void);
struct st7066u_iface *p_st7066u_iface1; /**< Pointer to struct of interface functions */

void lcd_initialise(struct st7066u_iface *pt_st7066u_iface)
{
    p_st7066u_iface1 = pt_st7066u_iface;
	/* Function Set ST7066U*/
	set_instruction_wakeup(0x30);
	set_instruction_wakeup(0x30); // 4 bit mode, Two lines, 5x8 format
	set_instruction_wakeup(0x30);
	set_instruction_wakeup(0x20);

	set_instruction(0x28);

	/* Display setup */
	set_instruction(0x0E); // Display ON, Cursor ON, Blink OFF

	/* Display Clear */
	set_instruction(0x01); // Clear display
	set_instruction(0x06); //Entry mode set
}

void set_instruction(uint8_t code)
{
	uint8_t value = code >> 4;
	uint8_t i = 0;

	p_st7066u_iface1->Set_LCD_RW_Pin(0);		//RW=LOW
    p_st7066u_iface1->Set_LCD_RS_Pin(0);		//RS=LOW

	//Set data lines to upper/lower 4 bits of instruction code
	while (i < 2)
	{

        p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
        p_st7066u_iface1->us_delay(5);

		/* Clear all data lines */
        p_st7066u_iface1->Set_LCD_D4_Pin(0);
        p_st7066u_iface1->Set_LCD_D5_Pin(0);
        p_st7066u_iface1->Set_LCD_D6_Pin(0);
        p_st7066u_iface1->Set_LCD_D7_Pin(0);

		if (value & 0x01)
		{
			p_st7066u_iface1->Set_LCD_D4_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
		    p_st7066u_iface1->Set_LCD_D5_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
		    p_st7066u_iface1->Set_LCD_D6_Pin(1);
		}	
		value = value >> 1;
		if (value & 0x01)
		{
		    p_st7066u_iface1->Set_LCD_D7_Pin(1);
		}

		/* Latch 4 bits of instruction code */
		p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
		p_st7066u_iface1->us_delay(50);
		value = code;
		i++;
	}
	while (check_busy_flag())
	{
		/* Wait */
	}
}

void set_instruction_wakeup(uint8_t code)
{
	uint8_t value = code >> 4;
	//uint8_t i = 0;

    p_st7066u_iface1->Set_LCD_RW_Pin(0);		//RW=LOW
    p_st7066u_iface1->Set_LCD_RS_Pin(0);		//RS=LOW

	//Set data lines to upper/lower 4 bits of instruction code

	p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
	p_st7066u_iface1->us_delay(5);

	/* Clear all data lines */
    p_st7066u_iface1->Set_LCD_D4_Pin(0);
    p_st7066u_iface1->Set_LCD_D5_Pin(0);
    p_st7066u_iface1->Set_LCD_D6_Pin(0);
    p_st7066u_iface1->Set_LCD_D7_Pin(0);

	if (value & 0x01)
	{
		p_st7066u_iface1->Set_LCD_D4_Pin(1);
	}
	value = value >> 1;
	if (value & 0x01)
	{
	    p_st7066u_iface1->Set_LCD_D5_Pin(1);
	}
	value = value >> 1;
	if (value & 0x01)
	{
	    p_st7066u_iface1->Set_LCD_D6_Pin(1);
	}
	value = value >> 1;
	if (value & 0x01)
	{
	    p_st7066u_iface1->Set_LCD_D7_Pin(1);
	}

	/* Latch 4 bits of instruction code */
	p_st7066u_iface1->Set_LCD_EN_Pin(0);	    //EN=LOW
	p_st7066u_iface1->us_delay(160);
}

static void send_char(char letter)
{
    char value = letter >> 4;
    uint8_t i = 0;
    p_st7066u_iface1->Set_LCD_RW_Pin(0); 	//RW=LOW
    p_st7066u_iface1->Set_LCD_RS_Pin(1);	    //RS=HIGH



	while (i < 2)
	{

		//Clear all data lines
        p_st7066u_iface1->Set_LCD_D4_Pin(0);
        p_st7066u_iface1->Set_LCD_D5_Pin(0);
        p_st7066u_iface1->Set_LCD_D6_Pin(0);
        p_st7066u_iface1->Set_LCD_D7_Pin(0);

        p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
        p_st7066u_iface1->us_delay(5);

		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D4_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D5_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D6_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D7_Pin(1);
		}

		// Latch 4 bits of instruction code
        p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
        p_st7066u_iface1->us_delay(50);

		value = letter;
		i++;
	}
	while (check_busy_flag())
	{
		//wait until ready
	}
}

void send_char_pos(char letter, char pos)
{
    char value = letter >> 4;
    uint8_t i = 0;
    
    set_instruction(pos);
    
    p_st7066u_iface1->Set_LCD_RW_Pin(0); 	//RW=LOW
    p_st7066u_iface1->Set_LCD_RS_Pin(1);	    //RS=HIGH


	while (i < 2)
	{

		//Clear all data lines
        p_st7066u_iface1->Set_LCD_D4_Pin(0);
        p_st7066u_iface1->Set_LCD_D5_Pin(0);
        p_st7066u_iface1->Set_LCD_D6_Pin(0);
        p_st7066u_iface1->Set_LCD_D7_Pin(0);

        p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
        p_st7066u_iface1->us_delay(5);

		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D4_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D5_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D6_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01)
		{
            p_st7066u_iface1->Set_LCD_D7_Pin(1);
		}

		// Latch 4 bits of instruction code
        p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
        p_st7066u_iface1->us_delay(50);

		value = letter;
		i++;
	}
	while (check_busy_flag())
	{
		//wait until ready
	}
	
	set_instruction(pos);
}

void send_line1(char *line1)
{
	uint8_t msg_len = strlen(line1);
	uint8_t i = 0;

	set_instruction(0x80); //Set DDRAM ADDRESS 0x00 Line 1

	for (i=0; i<msg_len; i++) {
		send_char(line1[i]);
	}
}

void send_line2(char *line2)
{
	uint8_t msg_len = strlen(line2);
	uint8_t i = 0;

	set_instruction(0xC0); //Set DDRAM Address 0x40 Line 2

	for (i=0; i<msg_len; i++) {
			send_char(line2[i]);
	}
}

void send_line3(char *line3)
{
	uint8_t msg_len = strlen(line3);
	uint8_t i = 0;

	set_instruction(0x94); //Set DDRAM Address 0x14 Line 3

	for (i=0; i<msg_len; i++) {
			send_char(line3[i]);
	}
}

void send_line4(char *line4)
{
	uint8_t msg_len = strlen(line4);
	uint8_t i = 0;

	set_instruction(0xD4); //Set DDRAM Address 0x54 Line 4

	for (i=0; i<msg_len; i++) {
			send_char(line4[i]);
	}
}

static uint8_t check_busy_flag(void)
{
	uint8_t busy_flag = 1;
    p_st7066u_iface1->Set_LCD_EN_Pin(0);	    //EN=LOW

    p_st7066u_iface1->Set_D4_PinMode(1);
    p_st7066u_iface1->Set_D5_PinMode(1);
    p_st7066u_iface1->Set_D6_PinMode(1);
    p_st7066u_iface1->Set_D7_PinMode(1);

    p_st7066u_iface1->Set_LCD_RS_Pin(0);	    //RS=LOW
    p_st7066u_iface1->Set_LCD_RW_Pin(1);		//RW=HIGH
    p_st7066u_iface1->Set_LCD_EN_Pin(1);  	//EN=HIGH
    p_st7066u_iface1->us_delay(5);

	//Read Data pin
	busy_flag = p_st7066u_iface1->is_D7_Set();

    p_st7066u_iface1->Set_LCD_EN_Pin(0);	    //EN=LOW
    p_st7066u_iface1->us_delay(50);
    p_st7066u_iface1->Set_LCD_EN_Pin(1);     //EN=HIGH
    p_st7066u_iface1->us_delay(5);
    p_st7066u_iface1->Set_LCD_EN_Pin(0);	    //EN=LOW
    p_st7066u_iface1->Set_LCD_RW_Pin(0);		//RW=LOW

    p_st7066u_iface1->Set_D4_PinMode(0);
    p_st7066u_iface1->Set_D5_PinMode(0);
    p_st7066u_iface1->Set_D6_PinMode(0);
    p_st7066u_iface1->Set_D7_PinMode(0);

	return busy_flag;
}
