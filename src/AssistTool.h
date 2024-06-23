#ifndef ASSIST_TOOL_H
#define ASSIST_TOOL_H

#include <stdint.h>

void indicate_value_by_led(uint32_t value);
void writesram(uint32_t target,uint32_t value);
uint32_t readsram(uint32_t target);
void delay(int cnt);
void greenlightBlink(int);
void redlightBlink(int);

#endif