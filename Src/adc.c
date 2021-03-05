#include "adc.h"

void init_adc(void)
{
   /* Enable the ADC Vreg */
   SET_BIT(ADC->CR, ADC_CR_ADVREGEN);

   /* Create a 20us delay */
   uint16 i = 0;
   for (i=0; i<320; i++)
   {
       // Simple delay
   }

   /* Calibration & Startup */
   if (READ_BIT(ADC->CR, ADC_CR_ADEN) == 0)
   {
       SET_BIT(ADC->CR, ADC_CR_ADCAL); //Start calibration
       while (READ_BIT(ADC->CR, ADC_CR_ADCAL) != 0)
       {
	   // Wait for calibration to complete
       }
       
       SET_BIT(ADC->ISR, ADC_ISR_ADRDY); //Clear the ADRDY flag
       SET_BIT(ADC->CR, ADC_CR_ADEN); //Enable the ADC
       while (READ_BIT(ADC->ISR, ADC_ISR_ADRDY) == 0)
       {
	   //Wait for ADC to become ready
       }
   }

}

uint16_t convert_voltage(void)
{
   SET_BIT(ADC->CHSELR, ADC_CHSELR_CHSEL0); //Select ADC channel 0
   SET_BIT(ADC->ISR, ADC_ISR_EOC); //Clear the EOC flag
   SET_BIT(ADC->CR, ADC_CR_ADSTART); //Start the conversion
   while (READ_BIT(ADC->ISR, ADC_ISR_EOC) == 0)
   {
       //Wait for conversion to finish
   }
   return READ_REG(ADC->DR);
}

uint16_t convert_current(void)
{
   SET_BIT(ADC->CHSELR, ADC_CHSELR_CHSEL1); //Select ADC Channel 1
   SET_BIT(ADC->ISR, ADC_ISR_EOC); //Clear the EOC flag
   SET_BIT(ADC->CR, ADC_CR_ADSTART); //Start the conversion
   while (READ_BIT(ADC->ISR, ADC_ISR_EOC) == 0)
   {
       //Wait for conversion to finish
   }
   return READ_REG(ADC->DR);
}
