#ifndef HITACHI_LCD_H
#define HITACHI_LCD_H

#include <stdint.h>

#define STDWAIT 750 //us
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

    void(*us_delay)(uint32_t delay); /**< @brief Pointer to microsecond delay function
                                    @param[in] delay: Required delay in microseconds */

};

void lcd_initialise(struct st7066u_iface *pt_st7066u_iface);
void set_instruction(uint8_t, uint16_t);
void send_char(char, uint16_t);
void send_line1(char *);
void send_line2(char *);
uint8_t check_busy_flag(void);

#endif //HITACHI_LCD_H
