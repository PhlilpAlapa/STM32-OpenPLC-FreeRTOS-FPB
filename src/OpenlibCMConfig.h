#ifndef OPENLIBCMCONFIG_h
#define OPENLIBCMCONFIG_h

#include <stdint.h>
#include <libopencm3/stm32/gpio.h>

#define RUN_LED                 {{ GPIOF, GPIO9}, 1}
#define ERR_LED                 {{ GPIOF, GPIO10}, 1}
// P45的接口介绍

// 半个随机分配吧
#define INPUTS                  { \
                                  { GPIOB,  GPIO9}, /* X0.0 */ \
                                  { GPIOB,  GPIO8}, /* X0.1 */ \
                                  { GPIOB,  GPIO7}, /* X0.2 */ \
                                  { GPIOB,  GPIO6}, /* X0.3 */ \
                                  { GPIOB,  GPIO5}, /* X0.4 */ \
                                  { GPIOB,  GPIO4}, /* X0.5 */ \
                                  { GPIOE,  GPIO4}, /* KEY 0 */ \
                                  { GPIOA,  GPIO1}, /* Power on */ \
                                }

#define OUTPUTS                 { \
                                  { GPIOG, GPIO15}, /* Y0.0 */ \
                                  { GPIOG, GPIO14}, /* Y0.1 */ \
                                  { GPIOG, GPIO13}, /* Y0.2 */ \
                                  { GPIOG, GPIO12}, /* Y0.3 */ \
                                  { GPIOG, GPIO11}, /* Y0.4 */ \
                                }
//  P4 块上努力找了

#define UART_1                  { \
                                  0, \
                                  GPIOA, \
                                  GPIO10,           /* rx    */ \
                                  GPIO9 ,           /* tx    */ \
                                  0,                /* no remap */ \
                                  { 0, 0 },      /* no en */ \
                                }
                                // 参考P36，真是这个

#endif