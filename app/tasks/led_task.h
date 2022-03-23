#ifndef __LED_TASK_H__
#define __LED_TASK_H__

#include "tasks_common.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include <stdint.h>

#if SEMAPHORE_WRAP_PRINTF
extern SemaphoreHandle_t g_printSemaphore;
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    extern xQueueHandle g_pLEDQueue;

    uint32_t LEDTaskInit(void);

#ifdef __cplusplus
}
#endif

#endif // __LED_TASK_H__
