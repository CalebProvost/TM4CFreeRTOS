//*****************************************************************************
//
// switch_task.c - A simple switch task to process the buttons.
//
// Copyright (c) 2012-2015 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.1.71 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************
#include "switch_task.h"

// Standard Libraries
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// TivaWare Libraries
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "drivers/buttons.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "utils/uartstdio.h"

// Tasks
#include "led_task.h"

//*****************************************************************************
//
// This task reads the buttons' state and passes this information to LEDTask.
//
//*****************************************************************************
static void SwitchTask(void* pvParameters)
{
    portTickType ui16LastTime;
    uint8_t ui8CurButtonState, ui8PrevButtonState;
    uint8_t ui8Message;

    ui8CurButtonState = ui8PrevButtonState = 0;

    //
    // Get the current tick count.
    //
    ui16LastTime = xTaskGetTickCount();

    //
    // Loop forever.
    //
    while (1)
    {
        //
        // Poll the debounced state of the buttons.
        //
        ui8CurButtonState = ButtonsPoll(0, 0);
        // NOTE: can remote debug and still press the switch in the debugger;
        // Change ui8CurButtonState to integer "254" for left button or "239" for right

        //
        // Check if previous debounced state is equal to the current state.
        //
        if (ui8CurButtonState != ui8PrevButtonState)
        {
            ui8PrevButtonState = ui8CurButtonState;

            //
            // Check to make sure the change in state is due to button press
            // and not due to button release.
            //
            if ((ui8CurButtonState & ALL_BUTTONS) != 0)
            {
                if ((ui8CurButtonState & ALL_BUTTONS) == LEFT_BUTTON)
                {
                    ui8Message = LEFT_BUTTON;

                    //
                    // Guard UART from concurrent access.
                    //
                    SEM_WRAP(printf("Left Button is pressed.\n"));
                }
                else if ((ui8CurButtonState & ALL_BUTTONS) == RIGHT_BUTTON)
                {
                    ui8Message = RIGHT_BUTTON;

                    //
                    // Guard UART from concurrent access.
                    //
                    SEM_WRAP(printf("Right Button is pressed.\n"));
                }

                //
                // Pass the value of the button pressed to LEDTask.
                //
                if (xQueueSend(g_pLEDQueue, &ui8Message, portMAX_DELAY) != pdPASS)
                {
                    //
                    // Error. The queue should never be full. If so print the
                    // error message on UART and wait for ever.
                    //
                    SEM_WRAP(printf("LEDQueue full. This should never happen.\n"));
                    while (1)
                    {
                    }
                }
            }
        }

        //
        // Wait for the required amount of time to check back.
        //
        vTaskDelayUntil(&ui16LastTime, pdMS_TO_TICKS(25));
    }
}

//*****************************************************************************
//
// Initializes the switch task.
//
//*****************************************************************************
uint32_t SwitchTaskInit(void)
{
    BaseType_t ret = pdTRUE;

    //
    // Unlock the GPIO LOCK register for Right button to work.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0xFF;

    //
    // Initialize the buttons
    //
    ButtonsInit();

    //
    // Create the switch task.
    //
    ret = xTaskCreate(SwitchTask, "Switch", tskStackSz_Switch, NULL, tskPriority_Switch, NULL);

    return (ret != pdTRUE) ? 1 : 0;
}
