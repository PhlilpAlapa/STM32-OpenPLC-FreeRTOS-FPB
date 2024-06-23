#ifndef TASK_PARAMS_H
#define TASK_PARAMS_H

#include <FreeRTOS.h>
#include <stdint.h>
#include <semphr.h>

struct task_parameters {
    SemaphoreHandle_t mutex;
    uint8_t uip_notify_flag;
};

#endif