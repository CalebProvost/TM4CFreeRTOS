#include "stats_task.h"

#include <stdint.h>

#define ARRAY_SIZE_OFFSET 5 // Increase this if print_real_time_stats returns -2

#if STAT_TASK_USES_NOTIFY
TaskHandle_t g_statTaskHandle = NULL;
#endif

static SemaphoreHandle_t sync_stats_task;

/**
 * @brief   Function to print the CPU usage of tasks over a given duration.
 *
 * This function will measure and print the CPU usage of tasks over a specified
 * number of ticks (i.e. real time stats). This is implemented by simply calling
 * uxTaskGetSystemState() twice separated by a delay, then calculating the
 * differences of task run times before and after the delay.
 *
 * @note    If any tasks are added or removed during the delay, the stats of
 *          those tasks will not be printed.
 * @note    This function should be called from a high priority task to minimize
 *          inaccuracies with delays.
 * @note    When running in dual core mode, each core will correspond to 50% of
 *          the run time.
 *
 * @param   xTicksToWait    Period of stats measurement
 *
 * @return 0 for success, -1 for memory error, -2 for invalid size, -3 for invalid state
 */
static int print_real_time_stats(TickType_t xTicksToWait)
{
    TaskStatus_t *start_array = NULL, *end_array = NULL;
    UBaseType_t start_array_size, end_array_size;
    uint32_t start_run_time, end_run_time;
    int ret;

    // Allocate array to store current task states
    start_array_size = uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET;
    start_array = malloc(sizeof(TaskStatus_t) * start_array_size);
    if (start_array == NULL)
    {
        ret = -1;
        goto exit;
    }
    // Get current task states
    start_array_size = uxTaskGetSystemState(start_array, start_array_size, &start_run_time);
    if (start_array_size == 0)
    {
        ret = -2;
        goto exit;
    }

    vTaskDelay(xTicksToWait);

    // Allocate array to store tasks states post delay
    end_array_size = uxTaskGetNumberOfTasks() + ARRAY_SIZE_OFFSET;
    end_array = malloc(sizeof(TaskStatus_t) * end_array_size);
    if (end_array == NULL)
    {
        ret = -1;
        goto exit;
    }

    // Get post delay task states
    end_array_size = uxTaskGetSystemState(end_array, end_array_size, &end_run_time);
    if (end_array_size == 0)
    {
        ret = -2;
        goto exit;
    }

    // Calculate total_elapsed_time in units of run time stats clock period.
    uint32_t total_elapsed_time = (end_run_time - start_run_time);
    if (total_elapsed_time == 0)
    {
        ret = -3;
        goto exit;
    }

    printf("\r\n%s| %10s | %15s | %8s | %8s | %3s | %10s | %s\r\n", "\033[0;92m", "Task *", "Task Name",
           "Priority (now)", "Run Time", "%%", "Watermark", "State");

    // Match each task in start_array to those in the end_array
    for (int i = 0; i < start_array_size; i++)
    {
        int k = -1;
        for (int j = 0; j < end_array_size; j++)
        {
            if (start_array[i].xHandle == end_array[j].xHandle)
            {
                k = j;
                // Mark the task as matched by overwriting their stack bases
                start_array[i].pxStackBase = NULL;
                end_array[j].pxStackBase = NULL;
                break;
            }
        }
        // Check if matching task found
        if (k >= 0)
        {
            uint32_t task_elapsed_time = end_array[k].ulRunTimeCounter - start_array[i].ulRunTimeCounter;
            uint32_t percentage_time = (task_elapsed_time * 100UL) / total_elapsed_time;
            const char* state;
            switch (start_array[i].eCurrentState)
            {
            case eReady:
                state = "Ready";
                break;
            case eRunning:
                state = "Running";
                break;
            case eBlocked:
                state = "Blocked";
                break;
            case eSuspended:
                state = "Suspended";
                break;
            case eDeleted:
                state = "Deleted";
                break;
            case eInvalid:
                state = "Invalid";
                break;
            }
            printf("%s| %10p | %15s |  %6d  (%2d)  | %8d | %2d%% | %10d | %s\r\n", "\033[0;92m", start_array[i].xHandle,
                   start_array[i].pcTaskName, start_array[i].uxBasePriority, start_array[i].uxCurrentPriority,
                   task_elapsed_time, percentage_time, start_array[i].usStackHighWaterMark, state);
        }
    }

    // Print unmatched tasks
    for (int i = 0; i < start_array_size; i++)
    {
        if (start_array[i].pxStackBase != NULL)
        {
            printf("%s| %10p | %15s |  %6d  (%2d)  | %8d | %2d%% | %10d | %s\r\n", "\033[0;92m", start_array[i].xHandle,
                   start_array[i].pcTaskName, start_array[i].uxBasePriority, start_array[i].uxCurrentPriority,
                   start_array[i].ulRunTimeCounter, start_array[i].ulRunTimeCounter / (start_run_time / 100),
                   start_array[i].usStackHighWaterMark, "Deleted");
        }
    }
    for (int i = 0; i < end_array_size; i++)
    {
        if (end_array[i].pxStackBase != NULL)
        {
            printf("%s| %10p | %15s |  %6d  (%2d)  | %8d | %2d%% | %10d | %s\r\n", "\033[0;92m", end_array[i].xHandle,
                   end_array[i].pcTaskName, end_array[i].uxBasePriority, end_array[i].uxCurrentPriority,
                   end_array[i].ulRunTimeCounter, end_array[i].ulRunTimeCounter / (start_run_time / 100),
                   end_array[i].usStackHighWaterMark, "Created");
        }
    }
    ret = 0;

exit: // Common return path
    free(start_array);
    free(end_array);
    return ret;
}

static void stats_task(void* arg)
{
    taskStats_t* p = (taskStats_t*)arg;
    TickType_t wait = 0, period = 0;
    if (p->wait == 0)
    {
        printf("%s: Cannot init printing interval with value %d. Defaulting to 900 ms\r\n", __FUNCTION__, p->wait);
        wait = pdMS_TO_TICKS(900);
    }
    else
    {
        wait = pdMS_TO_TICKS(p->wait);
    }

    if ((p->period == 0) || p->period == 0xffffffffUL)
    {
        printf("%s: Cannot init sampling rate with value %d. Defaulting to 100 ms\r\n", __FUNCTION__, p->period);
        period = pdMS_TO_TICKS(100);
    }
    else
    {
        period = pdMS_TO_TICKS(p->period);
    }

    xSemaphoreTake(sync_stats_task, portMAX_DELAY);

    // Print real time stats periodically
    while (1)
    {
        int ret = print_real_time_stats(period);
        if (ret)
        {
            printf("Error getting real time stats (%d)\r\n", ret);
        }
#if STAT_TASK_USES_NOTIFY
        ulTaskNotifyTake(pdTRUE, wait);
#else
        vTaskDelay(wait);
#endif
    }
}

void start_stats(uint32_t msWait, uint32_t samplePeriod)
{
    taskStats_t* arg = (taskStats_t*)malloc(sizeof(taskStats_t));
    arg->wait = msWait;
    arg->period = samplePeriod;
    
    // Create and start stats task
    sync_stats_task = xSemaphoreCreateBinary();
    // 2048 is not enough
#if STAT_TASK_USES_NOTIFY
    xTaskCreate(stats_task, "stats", tskStackSz_Stats, arg, tskPriority_Stats, &g_statTaskHandle);
#else
    xTaskCreate(stats_task, "stats", tskStackSz_Stats, arg, tskPriority_Stats, NULL);
#endif
    xSemaphoreGive(sync_stats_task);
}
