/* Electronic Load Project
 * Gareth Waymark 762102
 *
 * adc.c
 */
#include "adc.h"

static uint16_t voltage = 0;
static uint16_t current = 0;

void init_adc(void)
{
   /* Enable the ADC Vreg */
   SET_BIT(ADC1->CR, ADC_CR_ADVREGEN);
   MODIFY_REG(ADC1_COMMON->CCR, ADC_CCR_PRESC, ADC_CCR_PRESC_1); // Prescale 4
   /* Create a 20us delay */
   uint16_t i = 0;
   for (i=0; i<360; i++)
   {
       // Simple delay
   }

   /* Calibration & Startup */
   if (READ_BIT(ADC1->CR, ADC_CR_ADEN) == 0)
   {
       SET_BIT(ADC1->CR, ADC_CR_ADCAL); //Start calibration
       while (READ_BIT(ADC1->CR, ADC_CR_ADCAL) != 0)
       {
	   // Wait for calibration to complete
       }
       
       SET_BIT(ADC1->ISR, ADC_ISR_ADRDY); //Clear the ADRDY flag
       SET_BIT(ADC1->CR, ADC_CR_ADEN); //Enable the ADC
       while (READ_BIT(ADC1->ISR, ADC_ISR_ADRDY) == 0)
       {
	   //Wait for ADC to become ready
       }
   }

}

void convert_voltage(void)
{
   CLEAR_REG(ADC1->CHSELR);
   MODIFY_REG(ADC1->CFGR2, ADC_CFGR2_OVSR, ADC_CFGR2_OVSR_1);// Oversampling 8x
   MODIFY_REG(ADC1->CFGR2, ADC_CFGR2_OVSS, ADC_CFGR2_OVSS_1); // Oversampling /2
   SET_BIT(ADC1->CFGR2, ADC_CFGR2_OVSE); // enable oversampling
   SET_BIT(ADC1->CHSELR, ADC_CHSELR_CHSEL0); //Select ADC channel 0
   SET_BIT(ADC1->ISR, ADC_ISR_EOC); //Clear the EOC flag
   SET_BIT(ADC1->CR, ADC_CR_ADSTART); //Start the conversion
   while (READ_BIT(ADC1->ISR, ADC_ISR_EOC) == 0)
   {
       //Wait for conversion to finish
   }
   float res = (float)READ_REG(ADC1->DR) / 4;
   voltage =  (uint16_t)(res * 10);
}

void convert_current(void)
{
   CLEAR_REG(ADC1->CHSELR);
   SET_BIT(ADC1->CHSELR, ADC_CHSELR_CHSEL1); //Select ADC Channel 1
   MODIFY_REG(ADC1->CFGR2, ADC_CFGR2_OVSR, ADC_CFGR2_OVSR_2);// Oversampling 32x
   MODIFY_REG(ADC1->CFGR2, ADC_CFGR2_OVSS, ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_0); // Oversampling /32
   SET_BIT(ADC1->CFGR2, ADC_CFGR2_OVSE); // Enable oversampling
   SET_BIT(ADC1->ISR, ADC_ISR_EOC); //Clear the EOC flag
   SET_BIT(ADC1->CR, ADC_CR_ADSTART); //Start the conversion
   while (READ_BIT(ADC1->ISR, ADC_ISR_EOC) == 0)
   {
       //Wait for conversion to finish
   }
   uint16_t res = READ_REG(ADC1->DR);
   current =  (res / 2);
}

uint16_t get_voltage(void)
{
    return voltage;
}

uint16_t get_current(void)
{
    return current;
}
