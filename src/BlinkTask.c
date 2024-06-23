#include "BlinkTask.h"
#include "AssistTool.h"
#include "fpb_util.h"
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>



void blink_task(void *params)
{
    // Init State
    // 批量启用
    // F_9 F_10
    // gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
    //                 GPIO9);
    // int counter = 0;
    // uint32_t FBPMvalue = 0xFFFFFFFF;
    bool debug_mode = 0;
    if (debug_mode)
    {
        uint32_t target_addr = 0x20000100;
        writesram(target_addr, 0xFFFF0000);
        for (;;)
        {
            uint32_t this_value = readsram(target_addr);
            indicate_value_by_led(this_value);
            taskYIELD();
        }
    }
    // uint32_t displayed_value[10] = {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF
    // ,0xFFFFFFFF,0x00000000,0xFFFFFFFF,0xFFFFFFFF};
    // writesram(0x20000100,0x00000000);
    greenlightBlink(8);
    // int i = 0; 
    for (;;)
    {
        redlightBlink(8);
        greenlightBlink(8);
        // RAM:08000254
        // i = (i+1)%10;
        // indicate_value_by_led(displayed_value[i]);
        // // Loop State
        // counter+=1;
        // // 这一行是需要修改的东西
        // if (counter == 1)
        // {
        //     indicate_value_by_led(0x00000000);
        //     fpb_setup_example(0x08000254, 0x00000000);
        //     continue;
        // }
        // if (counter % 2 == 1)
        // {
        //     indicate_value_by_led(0x00000000);
        // }
        // else
        // {
        //     indicate_value_by_led(0xFFFFFFFF);
        // }
        taskYIELD();
    }
}