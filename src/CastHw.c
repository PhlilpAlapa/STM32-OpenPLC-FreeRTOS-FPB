#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/timer.h>
#ifdef STM32F1
#include <libopencm3/stm32/dac.h>
#endif

#include "config.h"
#include "CastHw.h"
#include "OpenlibCMConfig.h"

extern uint16_t QW[];
extern uint16_t IW[];
extern uint8_t QX[];
extern uint8_t IX[];

const struct gpios din[] = INPUTS;

const struct gpios dout[] = OUTPUTS;


void update_inputs(void)
{
    for (unsigned i = 0; i < NUM(din); i++)
        IX[i] = (gpio_get(din[i].port, din[i].pin) == 0);

}

void update_outputs(void)
{
    for (unsigned i = 0; i < NUM(dout); i++)
        if (QX[i])
            gpio_set(dout[i].port, dout[i].pin);
        else
            gpio_clear(dout[i].port, dout[i].pin);

}

static void clear_outputs(void)
{
    for (unsigned i = 0; i < NUM(dout); i++)
        gpio_clear(dout[i].port, dout[i].pin);
}