//*****************************************************************************
//
// interrupt.c - Example demonstrating how to configure the systick interrupt.
//
// Copyright (c) 2010-2015 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// This is part of revision 2.1.1.71 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//*****************************************************************************
//
//! \addtogroup systick_examples_list
//! <h1>Systick Interrupt (systick_int)</h1>
//!
//! This example shows how to configure the SysTick and the SysTick interrupt.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - NONE
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of
//! Systick.
//! - UART0 peripheral
//! - GPIO Port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - SysTickIntHandler
//
//*****************************************************************************

//*****************************************************************************
//
// Counter to count the number of interrupts that have been called.
//
//*****************************************************************************
volatile uint32_t g_ui32Counter = 0;

//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//
// The interrupt handler for the for Systick interrupt.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    //
    // Update the Systick interrupt counter.
    //
    g_ui32Counter++;
}

//*****************************************************************************
//
// Configure the SysTick and SysTick interrupt with a period of 1 second.
//
//*****************************************************************************
int
main(void)
{
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
	defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
	uint32_t ui32SysClock;
#endif

    uint32_t ui32PrevCount = 0;

    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
	defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_OSC), 25000000);
#else
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
#endif

    //
    // Set up the serial console to use for displaying messages.  This is
    // just for this example program and is not needed for Systick operation.
    //
    InitConsole();

    //
    // Display the setup on the console.
    //
    UARTprintf("SysTick Firing Interrupt ->");
    UARTprintf("\n   Rate = 1sec\n\n");

    //
    // Initialize the interrupt counter.
    //
    g_ui32Counter = 0;

    //
    // Set up the period for the SysTick timer.  The SysTick timer period will
    // be equal to the system clock, resulting in a period of 1 second.
    //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
	defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysTickPeriodSet(ui32SysClock);
#else
    SysTickPeriodSet(SysCtlClockGet());
#endif

    //
    // Enable interrupts to the processor.
    //
    IntMasterEnable();

    //
    // Enable the SysTick Interrupt.
    //
    SysTickIntEnable();

    //
    // Enable SysTick.
    //
    SysTickEnable();

    //
    // Loop forever while the SysTick runs.
    //
    while(1)
    {
        //
        // Check to see if systick interrupt count changed, and if so then
        // print a message with the count.
        //
        if(ui32PrevCount != g_ui32Counter)
        {
            //
            // Print the interrupt counter.
            //
            UARTprintf("Number of interrupts: %d\r", g_ui32Counter);
            ui32PrevCount = g_ui32Counter;
        }
    }
}
