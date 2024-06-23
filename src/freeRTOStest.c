#include "BlinkTask.h"
#include "SecondBlinkTask.h"
#include "AssistTool.h"
#include "InitialTool.h"
#include "TaskParams.h"
#include "PLCTask.h"
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <string.h>


#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>

static struct task_parameters task_params;


int main(void)
{
    // tester();
    initClock();

    task_params.mutex = xSemaphoreCreateMutex();

    xTaskCreate(blink_task, "Blink", configMINIMAL_STACK_SIZE*20, NULL,
                tskIDLE_PRIORITY + 1, NULL);

    xTaskCreate(second_blink_task, "SecondBlink", configMINIMAL_STACK_SIZE, NULL,
                tskIDLE_PRIORITY + 1, NULL);
                
    xTaskCreate(plc_task, "PLCRun", configMINIMAL_STACK_SIZE*20, &task_params,
                tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    return -1;
}