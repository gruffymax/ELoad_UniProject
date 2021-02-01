/*! @file st7066u_lcd.h */
/*!
 * @mainpage ST7066U LCD Driver
 * A simple driver for the ST7066U LCD controller using 4-bit mode. Currently only set to one 
 * configuration (No cursor, L to R, no blink).
 *
 */

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*!
 * @brief A structure for holding the interface function pointers
 */
struct st7066u_iface
{
    void(*Set_LCD_RW_Pin)(uint8_t state); /*!< @brief Pointer to RW pin Set/Reset function 
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_LCD_EN_Pin)(uint8_t state); /**< @brief Pointer to EN pin Set/Reset function 
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_LCD_RS_Pin)(uint8_t state); /**< @brief Pointer to RS pin Set/Reset function
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_LCD_D4_Pin)(uint8_t state); /**< @brief Pointer to D4 pin Set/Reset function
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_LCD_D5_Pin)(uint8_t state); /**< @brief Pointer to D5 pin Set/Reset function
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_LCD_D6_Pin)(uint8_t state); /**< @brief Pointer to D6 pin Set/Reset function
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_LCD_D7_Pin)(uint8_t state); /**< @brief Pointer to D7 pin Set/Reset function
                                         @param[in] state: 0=LOW, 1=HIGH*/

    void(*Set_D4_PinMode)(uint8_t mode); /**< @brief Pointer to D4 pin mode selector function
                                         @param[in] mode: 0=OUTPUT, 1=INPUT*/

    void(*Set_D5_PinMode)(uint8_t mode); /**< @brief Pointer to D5 pin mode selector function
                                         @param[in] mode: 0=OUTPUT, 1=INPUT*/

    void(*Set_D6_PinMode)(uint8_t mode); /**< @brief Pointer to D6 pin mode selector function
                                              @param[in] mode: 0=OUTPUT, 1=INPUT*/

    void(*Set_D7_PinMode)(uint8_t mode); /**< @brief Pointer to D7 pin mode selector function
                                              @param[in] mode: 0=OUTPUT, 1=INPUT*/

    uint8_t(*is_D7_Set)(void); /**< @brief Pointer to D7 pin state read function
                                    @return State of pin D7. 0=LOW, 1=HIGH*/

    void(*us_delay)(uint16_t delay); /**< @brief Pointer to microsecond delay function
                                    @param[in] delay: Required delay in microseconds */

};

/**
 * Initialise the LCD display
 * @param[in] p_st7066u_iface: Pointer to a st7066u_iface struct holding the interface functions.
 */
void lcd_initialise(struct st7066u_iface *pt_st7066u_iface);

/*!
 * @brief Send an instruction to the LCD
 * @param[in] code: 8 bit instruction to send to LCD
 */
void set_instruction(uint8_t code);

/*!
 * @brief Send an instruction to the LCD during wakeup
 * @param[in] code: 8 bit instruction to send to LCD
 */
void set_instruction_wakeup(uint8_t code);

/*!
 * @brief Send string of characters to the line 1 buffer of the LCD
 * @param[in] line1: String of characters to send to LCD line 1
 */
void send_line1(char * line1);

/*!
 * @brief Send string of characters to the line 2 buffer of the LCD
 * @param[in] line1: String of characters to send to LCD line 2
 */
void send_line2(char * line1);

#ifdef __cplusplus
}
#endif

#endif //LCD_H
