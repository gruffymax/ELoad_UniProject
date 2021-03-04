#include "dac.h"

void init_dac(void)
{
    SET_BIT(DAC->CR, DAC_CR_EN1); // Enable DAC channel 1
    CLEAR_BIT(DAC->CR, DAC_CR_TEN1); // Enable software triggering
    write_dac1_value(0x00000000); // Set DAC output to 1V;
}

void write_dac1_value(uint32_t value)
{
    WRITE_REG(DAC->DHR12R1, value);
    SET_BIT(DAC->SWTRIGR, DAC_SWTRIGR_SWTRIG1); //Trigger DAC to set new value
}
