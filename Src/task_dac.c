#include "task_dac.h"
#include "dac.h"
#include "task_ui.h"


uint32_t dac_value = 0; 

void task_dac(void *arguments)
{
    while(1)
    {
        dac_value = get_dac_setting();
        write_dac1_value(dac_value);
        vTaskDelay(100);
    }
}
