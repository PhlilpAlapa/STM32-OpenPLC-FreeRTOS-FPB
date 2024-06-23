#ifndef HW_H
#define HW_H

#include <stdint.h>

struct gpios {
    const uint32_t port;
    const uint16_t pin;
};

struct leds {
    const struct gpios gpio;
    const int inv;
};

struct uarts {
    const uint8_t index;
    const uint32_t port;
    const uint16_t rx;
    const uint16_t tx;
    const uint32_t remaps;
    const struct gpios en;
};

void update_inputs(void);
void update_outputs(void);
static void clear_outputs(void);
#endif