/* Electronic Load Project 
 * Gareth Waymark up762102
 * 
 * GPIO configuration functions
 */

#include "gpio.h"
static void configureGPIOA(void);
static void configureGPIOB(void);
static void configureGPIOD(void);

    
void init_gpio(void)
{
    configureGPIOA();
    configureGPIOB();
    configureGPIOD();
}

static void configureGPIOA(void)
{
    /* Configure GPIOA pins */
    /* Configure DAC pin */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE4, GPIO_MODER_MODE4_0 | GPIO_MODER_MODE4_1); // Analog pin
    
    /* Configure ADC inputs */
    /* ADC_IN0 */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE0, GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1); // Analog pin
    
    /* ADC_IN1 */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE1, GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1); // Analog pin
    
    /* Configure USART pins */
    /* USART1_TX */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE9, GPIO_MODER_MODE9_1); // Alternate mode
    MODIFY_REG(GPIOA->AFR[1], GPIO_AFRH_AFSEL9, GPIO_AFRH_AFSEL9_0); // AF1
    
    /* USART_RX */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE10, GPIO_MODER_MODE10_1); // Alternate mode AF1
    MODIFY_REG(GPIOA->AFR[1], GPIO_AFRH_AFSEL10, GPIO_AFRH_AFSEL10_0); // AF1
    
    /* Configure Rotary encoder */
    /* Push switch */
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE15, 0x0); // Input mode
    
    
}

static void configureGPIOB(void)
{
    /* Configure LED control pins */
    /* RED_LED */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE1, GPIO_MODER_MODE1_0); // Output pin
    
    /* GREEN LED */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE2, GPIO_MODER_MODE2_0); // Output pin
    
    /* Start Button */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE10, 0x0); // Input pin
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD10, GPIO_PUPDR_PUPD10_1); //Activate pull down
    
    /* Constant Current Mode */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE11, 0x0); // Input pin
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD11, GPIO_PUPDR_PUPD11_1); //Activate pull down
    
    /* Constant Voltage Mode */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE12, 0x0); // Input pin
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD12, GPIO_PUPDR_PUPD12_1); //Activate pull down
    
    /* Constant Resistance Mode */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE13, 0x0); // Input pin
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD13, GPIO_PUPDR_PUPD13_1); //Activate pull down
    
    /* Constant Power Mode */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE14, 0x0); // Input pin
    MODIFY_REG(GPIOB->PUPDR, GPIO_PUPDR_PUPD14, GPIO_PUPDR_PUPD14_1); //Activate pull down
    
    /* Configure LCD control pins. Open drain, 5V tolerent */
    /* EN */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE3, GPIO_MODER_MODE3_0);
    SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT3); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED3, GPIO_OSPEEDR_OSPEED3_0);
    
    /* RW */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE4, 0x0);
    //SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT4); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED4, GPIO_OSPEEDR_OSPEED4_0);
    MODIFY_REG(GPIOD->MODER, GPIO_MODER_MODE3, GPIO_MODER_MODE3_0);
    SET_BIT(GPIOD->OTYPER, GPIO_OTYPER_OT3); // Open Drain
    
    /* RS */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE5, GPIO_MODER_MODE5_0);
    SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT5); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED5, GPIO_OSPEEDR_OSPEED5_0);
    
    /* D4 */
    /* TODO Set to PB10 as PB6 seems damaged*/
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE10, GPIO_MODER_MODE10_0);
    SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT10); // Open Drain
    //MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6, GPIO_MODER_MODE6_0);
    //SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT6); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED6, GPIO_OSPEEDR_OSPEED6_0);
    
    /* D5 */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7, GPIO_MODER_MODE7_0);
    SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT7); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED7, GPIO_OSPEEDR_OSPEED7_0);
    
    /* D6 */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE8, GPIO_MODER_MODE8_0);
    SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT8); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED8, GPIO_OSPEEDR_OSPEED8_0);
    
    /* D7 */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE9, GPIO_MODER_MODE9_0);
    SET_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT9); // Open Drain
    //MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED9, GPIO_OSPEEDR_OSPEED9_0);
    
    
}

static void configureGPIOD(void)
{
    /* Configure Rotary Encoder */
    /* Channel A */
    MODIFY_REG(GPIOD->MODER, GPIO_MODER_MODE0, 0x0); // Input mode

}
