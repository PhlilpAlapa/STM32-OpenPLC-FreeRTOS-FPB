#include <string.h>
#include <stdint.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/fsmc.h>
// fsmc 是 STM32SRAM配置器
// 大爷的另一个压根不能用
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "AssistTool.h"

void delay(int cnt) //ms
{
	int i = 0;
	for (i = 0; i < cnt*1000; i++) {
		__asm__("nop");
	} 
}

void writesram(uint32_t target,uint32_t value)
{
    // BANK1 base:0x68000000
    // #define FSMC_BANK1_BASE			0x60000000U /* NOR / PSRAM */
    // sdram_command
    // 此处考虑使用SRAM1？
    // 不对，本体就是这个SRAM
    // FLASH的起点是？
    // 0x20000000 RAM起点
    // 0x80000000 ROM起点
    uint32_t target_addr;
    target_addr = target;
    *(uint32_t *)target_addr=value;
}
uint32_t readsram(uint32_t target)
{
    // BANK1 base:0x68000000
    // #define FSMC_BANK1_BASE			0x60000000U /* NOR / PSRAM */
    // sdram_command
    // 此处考虑使用SRAM1？
    // 不对，本体就是这个SRAM
    // FLASH的起点是？
    // 0x20000000 RAM起点
    // 0x80000000 ROM起点
    uint32_t* target_addr;
    target_addr = (uint32_t*)target;
    return *target_addr;
}

void enableLight(void)
{
    rcc_periph_clock_enable(RCC_GPIOF);
    // 批量启用
    // F_9 F_10
    gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    GPIO9);
    gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    GPIO10);
}

void indicate_value_by_led(uint32_t value)
{
    delay(1000);
    int fon=1;
    int son=1;
    int i=0;
    while (1)
    {
        /* code */
        i++;
        if((value & 0x00000001) == 0x00000001)
        {
            fon=gpio_get(GPIOF,GPIO9);
            if(fon)
            {
                gpio_clear(GPIOF,GPIO9);
            }
            else
            {
                gpio_set(GPIOF,GPIO9);
            }
        }
        else
        {   son=gpio_get(GPIOF,GPIO10);
            if(son)
            {
                gpio_clear(GPIOF,GPIO10);
            }
            else
            {
                gpio_set(GPIOF,GPIO10);
            }}
        value=(value << (32 - 1) | (value >> 1));
            // 循环右移
        delay(300);
        if(i==32)return;
    }
    
}

void redlightBlink(int x)
{
    // Address	ram:080001c4
    int son=1;
    int i=0;
    while (1)
    {
        /* code */
        i++;
        {   son=gpio_get(GPIOF,GPIO9);
            if(son)
            {
                gpio_clear(GPIOF,GPIO9);
            }
            else
            {
                gpio_set(GPIOF,GPIO9);
            }
        }
        delay(300);
        if(i==x)return;
    }
}

void greenlightBlink(int x)
{
    // Address	ram:08000200
    int son=1;
    int i=0;
    while (1)
    {
        /* code */
        i++;
        {   son=gpio_get(GPIOF,GPIO10);
            if(son)
            {
                gpio_clear(GPIOF,GPIO10);
            }
            else
            {
                gpio_set(GPIOF,GPIO10);
            }
        }
        delay(300);
        if(i==x)return;
    }
}