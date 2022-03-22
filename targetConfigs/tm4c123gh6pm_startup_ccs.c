//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
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
//*****************************************************************************

#include <stdint.h>

// *********************** FUNCTION PROTOTYPES ************************
void Reset_Handler(void);    /* Reset Handler */
void Default_Handler(void);  /* Default empty handler */
void SystemInit(void);       /* CMSIS system initialization */

/**********************************************************************
   WEAK ALIASES FOR EACH EXCEPTION HANDLER TO THE DEFAULT_HANDLER.
   ANY FUNCTION WITH THE SAME NAME WILL OVERRIDE THESE DEFINITIONS.
 *********************************************************************/

// *************** CORTEX-M PROCESSOR FAULT EXCEPTIONS ****************
void NMI_Handler           (void) __attribute__ ((weak));
void HardFault_Handler     (void) __attribute__ ((weak));
void MemManage_Handler     (void) __attribute__ ((weak));
void BusFault_Handler      (void) __attribute__ ((weak));
void UsageFault_Handler    (void) __attribute__ ((weak));

// ************* CORTEX-M PROCESSOR NON-FAULT EXCEPTIONS **************
extern void xPortPendSVHandler(void);
void        DebugMon_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
extern void vPortSVCHandler(void);
extern void xPortSysTickHandler(void);


// *********************** EXTERNAL INTERRUPTS ************************
void GPIOPortA_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortB_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortC_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortD_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortE_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PWMFault_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PWMGen0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void PWMGen1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void PWMGen2_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void QEI0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCSeq0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCSeq1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCSeq2_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void ADCSeq3_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Watchdog_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer0A_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer0B_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer1A_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer1B_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer2A_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer2B_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Comp0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void Comp1_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void Comp2_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SysCtrl_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void FlashCtrl_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortF_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortG_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortH_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void UART2_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer3A_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer3B_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void QEI1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void Hibernate_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void USB0_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PWMGen3_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void uDMAST_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void uDMAError_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq0_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq2_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq3_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortJ_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortK_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortL_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UART3_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART6_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART7_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer4A_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer4B_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer5A_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void Timer5B_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer0A_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer0B_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer1A_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer1B_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer2A_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer2B_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer3A_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer3B_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer4A_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer4B_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer5A_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WideTimer5B_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C4_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C5_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortM_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortN_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void QEI2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP6_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortP7_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ6_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortQ7_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortR_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOPortS_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1Gen0_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1Gen1_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1Gen2_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1Gen3_IRQHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1Fault_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
                                            // The initial stack pointer
    Reset_Handler,          /* Reset Handler                   */
    NMI_Handler,            /* NMI Handler                     */
    HardFault_Handler,      /* Hard Fault Handler              */
    MemManage_Handler,      /* The MPU fault handler           */
    BusFault_Handler,       /* The bus fault handler           */
    UsageFault_Handler,     /* The usage fault handler         */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    vPortSVCHandler,            /* SVCall handler                  */
    DebugMon_Handler,       /* Debug monitor handler           */
    0,                            /* Reserved                        */
    xPortPendSVHandler,         /* The PendSV handler              */
    xPortSysTickHandler,        /* The SysTick handler             */

    /*IRQ handlers... */
    GPIOPortA_IRQHandler,   /* GPIO Port A                     */
    GPIOPortB_IRQHandler,   /* GPIO Port B                     */
    GPIOPortC_IRQHandler,   /* GPIO Port C                     */
    GPIOPortD_IRQHandler,   /* GPIO Port D                     */
    GPIOPortE_IRQHandler,   /* GPIO Port E                     */
    UART0_IRQHandler,       /* UART0 Rx and Tx                 */
    UART1_IRQHandler,       /* UART1 Rx and Tx                 */
    SSI0_IRQHandler,        /* SSI0 Rx and Tx                  */
    I2C0_IRQHandler,        /* I2C0 Master and Slave           */
    PWMFault_IRQHandler,    /* PWM Fault                       */
    PWMGen0_IRQHandler,     /* PWM Generator 0                 */
    PWMGen1_IRQHandler,     /* PWM Generator 1                 */
    PWMGen2_IRQHandler,     /* PWM Generator 2                 */
    QEI0_IRQHandler,        /* Quadrature Encoder 0            */
    ADCSeq0_IRQHandler,     /* ADC Sequence 0                  */
    ADCSeq1_IRQHandler,     /* ADC Sequence 1                  */
    ADCSeq2_IRQHandler,     /* ADC Sequence 2                  */
    ADCSeq3_IRQHandler,     /* ADC Sequence 3                  */
    Watchdog_IRQHandler,    /* Watchdog timer                  */
    Timer0A_IRQHandler,     /* Timer 0 subtimer A              */
    Timer0B_IRQHandler,     /* Timer 0 subtimer B              */
    Timer1A_IRQHandler,     /* Timer 1 subtimer A              */
    Timer1B_IRQHandler,     /* Timer 1 subtimer B              */
    Timer2A_IRQHandler,     /* Timer 2 subtimer A              */
    Timer2B_IRQHandler,     /* Timer 2 subtimer B              */
    Comp0_IRQHandler,       /* Analog Comparator 0             */
    Comp1_IRQHandler,       /* Analog Comparator 1             */
    Comp2_IRQHandler,       /* Analog Comparator 2             */
    SysCtrl_IRQHandler,     /* System Control (PLL, OSC, BO)   */
    FlashCtrl_IRQHandler,   /* FLASH Control                   */
    GPIOPortF_IRQHandler,   /* GPIO Port F                     */
    GPIOPortG_IRQHandler,   /* GPIO Port G                     */
    GPIOPortH_IRQHandler,   /* GPIO Port H                     */
    UART2_IRQHandler,       /* UART2 Rx and Tx                 */
    SSI1_IRQHandler,        /* SSI1 Rx and Tx                  */
    Timer3A_IRQHandler,     /* Timer 3 subtimer A              */
    Timer3B_IRQHandler,     /* Timer 3 subtimer B              */
    I2C1_IRQHandler,        /* I2C1 Master and Slave           */
    QEI1_IRQHandler,        /* Quadrature Encoder 1            */
    CAN0_IRQHandler,        /* CAN0                            */
    CAN1_IRQHandler,        /* CAN1                            */
    CAN2_IRQHandler,        /* CAN2                            */
    0,                            /* Reserved                        */
    Hibernate_IRQHandler,   /* Hibernate                       */
    USB0_IRQHandler,        /* USB0                            */
    PWMGen3_IRQHandler,     /* PWM Generator 3                 */
    uDMAST_IRQHandler,      /* uDMA Software Transfer          */
    uDMAError_IRQHandler,   /* uDMA Error                      */
    ADC1Seq0_IRQHandler,    /* ADC1 Sequence 0                 */
    ADC1Seq1_IRQHandler,    /* ADC1 Sequence 1                 */
    ADC1Seq2_IRQHandler,    /* ADC1 Sequence 2                 */
    ADC1Seq3_IRQHandler,    /* ADC1 Sequence 3                 */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    GPIOPortJ_IRQHandler,   /* GPIO Port J                     */
    GPIOPortK_IRQHandler,   /* GPIO Port K                     */
    GPIOPortL_IRQHandler,   /* GPIO Port L                     */
    SSI2_IRQHandler,        /* SSI2 Rx and Tx                  */
    SSI3_IRQHandler,        /* SSI3 Rx and Tx                  */
    UART3_IRQHandler,       /* UART3 Rx and Tx                 */
    UART4_IRQHandler,       /* UART4 Rx and Tx                 */
    UART5_IRQHandler,       /* UART5 Rx and Tx                 */
    UART6_IRQHandler,       /* UART6 Rx and Tx                 */
    UART7_IRQHandler,       /* UART7 Rx and Tx                 */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    I2C2_IRQHandler,        /* I2C2 Master and Slave           */
    I2C3_IRQHandler,        /* I2C3 Master and Slave           */
    Timer4A_IRQHandler,     /* Timer 4 subtimer A              */
    Timer4B_IRQHandler,     /* Timer 4 subtimer B              */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    Timer5A_IRQHandler,     /* Timer 5 subtimer A              */
    Timer5B_IRQHandler,     /* Timer 5 subtimer B              */
    WideTimer0A_IRQHandler, /* Wide Timer 0 subtimer A         */
    WideTimer0B_IRQHandler, /* Wide Timer 0 subtimer B         */
    WideTimer1A_IRQHandler, /* Wide Timer 1 subtimer A         */
    WideTimer1B_IRQHandler, /* Wide Timer 1 subtimer B         */
    WideTimer2A_IRQHandler, /* Wide Timer 2 subtimer A         */
    WideTimer2B_IRQHandler, /* Wide Timer 2 subtimer B         */
    WideTimer3A_IRQHandler, /* Wide Timer 3 subtimer A         */
    WideTimer3B_IRQHandler, /* Wide Timer 3 subtimer B         */
    WideTimer4A_IRQHandler, /* Wide Timer 4 subtimer A         */
    WideTimer4B_IRQHandler, /* Wide Timer 4 subtimer B         */
    WideTimer5A_IRQHandler, /* Wide Timer 5 subtimer A         */
    WideTimer5B_IRQHandler, /* Wide Timer 5 subtimer B         */
    FPU_IRQHandler,         /* FPU                             */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    I2C4_IRQHandler,        /* I2C4 Master and Slave           */
    I2C5_IRQHandler,        /* I2C5 Master and Slave           */
    GPIOPortM_IRQHandler,   /* GPIO Port M                     */
    GPIOPortN_IRQHandler,   /* GPIO Port N                     */
    QEI2_IRQHandler,        /* Quadrature Encoder 2            */
    0,                            /* Reserved                        */
    0,                            /* Reserved                        */
    GPIOPortP0_IRQHandler,  /* GPIO Port P (Summary or P0)     */
    GPIOPortP1_IRQHandler,  /* GPIO Port P1                    */
    GPIOPortP2_IRQHandler,  /* GPIO Port P2                    */
    GPIOPortP3_IRQHandler,  /* GPIO Port P3                    */
    GPIOPortP4_IRQHandler,  /* GPIO Port P4                    */
    GPIOPortP5_IRQHandler,  /* GPIO Port P5                    */
    GPIOPortP6_IRQHandler,  /* GPIO Port P6                    */
    GPIOPortP7_IRQHandler,  /* GPIO Port P7                    */
    GPIOPortQ0_IRQHandler,  /* GPIO Port Q (Summary or Q0)     */
    GPIOPortQ1_IRQHandler,  /* GPIO Port Q1                    */
    GPIOPortQ2_IRQHandler,  /* GPIO Port Q2                    */
    GPIOPortQ3_IRQHandler,  /* GPIO Port Q3                    */
    GPIOPortQ4_IRQHandler,  /* GPIO Port Q4                    */
    GPIOPortQ5_IRQHandler,  /* GPIO Port Q5                    */
    GPIOPortQ6_IRQHandler,  /* GPIO Port Q6                    */
    GPIOPortQ7_IRQHandler,  /* GPIO Port Q7                    */
    GPIOPortR_IRQHandler,   /* GPIO Port R                     */
    GPIOPortS_IRQHandler,   /* GPIO Port S                     */
    PWM1Gen0_IRQHandler,    /* PWM 1 Generator 0               */
    PWM1Gen1_IRQHandler,    /* PWM 1 Generator 1               */
    PWM1Gen2_IRQHandler,    /* PWM 1 Generator 2               */
    PWM1Gen3_IRQHandler,    /* PWM 1 Generator 3               */
    PWM1Fault_IRQHandler,   /* PWM 1 Fault                     */
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void Reset_Handler(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void NMI_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void HardFault_Handler(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void Default_Handler(void)
{

    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
