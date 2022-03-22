// Standard Libraries
#include <stdint.h>
#include <string.h>

// TM4C TivaWare Libraries
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "utils/uartstdio.h"

// FreeRTOS
#include "tasks_common.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

// Project Tasks
#include "led_task.h"
#include "switch_task.h"

SemaphoreHandle_t g_printSemaphore;

// Configure the UART and its pins.  This must be called before UARTprintf().
void ConfigureUART(void)
{
    // Enable the GPIO Peripheral used by the UART.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Enable UART0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Configure GPIO Pins for UART mode.
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
}

int main(void)
{
    // Initialize FreeRTOS and start the initial set of tasks.
    // Set the clocking to run at 50 MHz from the PLL.
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    ConfigureUART();

    // Create a mutex to guard the UART.
    g_printSemaphore = xSemaphoreCreateMutex();

    // Create the LED task.
    if (LEDTaskInit() != 0)
    {
        printf("Failed to init LED Task\n");
        while (1)
        {
            // Hang here for debugger
        }
    }
    printf("LED Task initialized\n");

    // Create the switch task.
    if (SwitchTaskInit() != 0)
    {
        printf("Failed to init Switch Task\n");
        while (1)
        {
            // Hang here for debugger
        }
    }
    printf("Switch Task Initialized\n");

    // Start the scheduler.  This should not return.
    printf("Starting FreeRTOS Scheduler\n");
    vTaskStartScheduler();
    // In case the scheduler returns for some reason, print an error and loop forever.
    printf("ERROR! FreeRTOS Scheduler returned!\n");
    while (1)
    {
        // Hang here for debugger
    }

    return 0;
}
