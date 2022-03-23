#ifndef __STATS_TASK_H__
#define __STATS_TASK_H__

#define STAT_TASK_USES_NOTIFY 1

#include "tasks_common.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "portmacro.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include <stdint.h>

#if SEMAPHORE_WRAP_PRINTF
extern SemaphoreHandle_t g_printSemaphore;
#endif

#if STAT_TASK_USES_NOTIFY
extern TaskHandle_t g_statTaskHandle;
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct {
        uint32_t wait;
        uint32_t period;
    } taskStats_t;
    void start_stats(uint32_t msWait, uint32_t samplePeriod);

#ifdef __cplusplus
}
#endif
#endif // __STATS_TASK_H__
