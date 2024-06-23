#include "SecondBlinkTask.h"
#include "AssistTool.h"
#include "fpb_util.h"

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <string.h>


#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>

#include <iotpatch.h>
#include <patch_service.h>


void second_blink_task(void *params)
{

    // Init State
    // gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
    //                 GPIO10);
    int tid=0;
    for(;;)
    {
        tid ++ ;
        delay(10);

        if(tid==1000)
        {
            patch_desc newdesk;
            
            // notify_new_patch();
            fpb_setup_example(0x08000248, 0x00bf,0);
            fpb_setup_example(0x0800024a, 0x00bf,1);
            // 
            // add_ebpf_patch()
            // HEX:-54
            // fff7d4ff
        }
        // Loop State
        taskYIELD();
    }
}