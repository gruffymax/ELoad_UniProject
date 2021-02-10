/*
 * ST7066 LCD Driver
 *
 *
 *      Author: Gareth Waymark
 */
#include "hitachi_lcd.h"
#include <string.h>
#include "main.h"

struct st7066u_iface *p_st7066u_iface1; /**< Pointer to struct of interface functions */

void lcd_initialise(struct st7066u_iface *pt_st7066u_iface) {
    p_st7066u_iface1 = pt_st7066u_iface;
    
	/* Function Set Hitachi Compatible */
	set_instruction(0x03, 5000);
	set_instruction(0x03, STDWAIT);
	set_instruction(0x03, STDWAIT);
	set_instruction(0x02, STDWAIT);

	/* Display setup */
	//check_busy_flag();
	set_instruction(0x0C, STDWAIT); // Display ON, Cursor OFF, Blink OFF

	/* Display Clear */
	//check_busy_flag();
	set_instruction(0x01, 5000); // Clear display, requires longer wait time.

	//check_busy_flag();
	set_instruction(0x06, STDWAIT); //Entry mode set

}

void set_instruction(uint8_t code, uint16_t wait) {
	uint8_t value = code >> 4;
	uint8_t i = 0;

    p_st7066u_iface1->Set_LCD_RW_Pin(0);		//RW=LOW
    p_st7066u_iface1->Set_LCD_RS_Pin(0);		//RS=LOW
    p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH

	//Set data lines to upper/lower 4 bits of instruction code
	while (i < 2) {
		//Clear all data lines
        p_st7066u_iface1->Set_LCD_D4_Pin(0);
        p_st7066u_iface1->Set_LCD_D5_Pin(0);
        p_st7066u_iface1->Set_LCD_D6_Pin(0);
        p_st7066u_iface1->Set_LCD_D7_Pin(0);

		if (value & 0x01) {
			p_st7066u_iface1->Set_LCD_D4_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01) {
				p_st7066u_iface1->Set_LCD_D5_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01) {
				p_st7066u_iface1->Set_LCD_D6_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01) {
				p_st7066u_iface1->Set_LCD_D7_Pin(1);
		}

		// Latch 4 bits of instruction code
		p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
		p_st7066u_iface1->us_delay(wait);
		p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
		p_st7066u_iface1->us_delay(wait);
		value = code;
		i++;
	}
}

void send_char(char letter,  uint16_t wait) {
    char value = letter >> 4;
    uint8_t i = 0;
    p_st7066u_iface1->Set_LCD_RW_Pin(0); 	//RW=LOW
    p_st7066u_iface1->Set_LCD_RS_Pin(1);	    //RS=HIGH



	while (i < 2) {
		//Clear all data lines
        p_st7066u_iface1->Set_LCD_D4_Pin(0);
        p_st7066u_iface1->Set_LCD_D5_Pin(0);
        p_st7066u_iface1->Set_LCD_D6_Pin(0);
        p_st7066u_iface1->Set_LCD_D7_Pin(0);

		if (value & 0x01) {
			p_st7066u_iface1->Set_LCD_D4_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01) {
            p_st7066u_iface1->Set_LCD_D5_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01) {
            p_st7066u_iface1->Set_LCD_D6_Pin(1);
		}
		value = value >> 1;
		if (value & 0x01) {
            p_st7066u_iface1->Set_LCD_D7_Pin(1);
		}

		// Latch 4 bits of instruction code
        p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
		p_st7066u_iface1->us_delay(wait);
		p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
		p_st7066u_iface1->us_delay(wait);
		value = letter;
		i++;
	}
}

void send_line1(char *line1) {
	uint8_t msg_len = strlen(line1);
	uint8_t i = 0;

	set_instruction(0x01, STDWAIT);

	for (i=0; i<msg_len; i++) {
		send_char(line1[i], STDWAIT);
	}
}

void send_line2(char *line2) {
	uint8_t msg_len = strlen(line2);
	uint8_t i = 0;

	set_instruction(0xC0, STDWAIT);

	for (i=0; i<msg_len; i++) {
			send_char(line2[i], STDWAIT);
	}
}

uint8_t check_busy_flag() {
	uint8_t busy_flag = 1;
    p_st7066u_iface1->Set_LCD_EN_Pin(0);	    //EN=LOW

    p_st7066u_iface1->Set_D4_PinMode(1);
    p_st7066u_iface1->Set_D5_PinMode(1);
    p_st7066u_iface1->Set_D6_PinMode(1);
    p_st7066u_iface1->Set_D7_PinMode(1);

    p_st7066u_iface1->Set_LCD_RS_Pin(0);	    //RS=LOW
    p_st7066u_iface1->Set_LCD_RW_Pin(1);		//RW=HIGH
    p_st7066u_iface1->Set_LCD_EN_Pin(1);  	//EN=HIGH

	//Read Data pin
	busy_flag = p_st7066u_iface1->is_D7_Set();

	p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
	p_st7066u_iface1->us_delay(1000);
	p_st7066u_iface1->Set_LCD_EN_Pin(1);	//EN=HIGH
	p_st7066u_iface1->us_delay(1000);
	p_st7066u_iface1->Set_LCD_EN_Pin(0);	//EN=LOW
	p_st7066u_iface1->Set_LCD_RW_Pin(0);		//RW=LOW

    p_st7066u_iface1->Set_D4_PinMode(0);
    p_st7066u_iface1->Set_D5_PinMode(0);
    p_st7066u_iface1->Set_D6_PinMode(0);
    p_st7066u_iface1->Set_D7_PinMode(0);

	return busy_flag;
}
