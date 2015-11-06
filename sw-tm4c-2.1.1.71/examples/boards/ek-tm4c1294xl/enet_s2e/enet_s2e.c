//*****************************************************************************
//
// enet_s2e.c - Serial to Ethernet Application using lwIP.
//
// Copyright (c) 2014-2015 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/flash.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "utils/swupdate.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "config.h"
#include "lwip_task.h"
#include "serial_task.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>S2E application with lwIP and FreeRTOS (enet_s2e)</h1>
//!
//! The S2E application implements a serial-to-Ethernet module that provides a
//! means to access the UART port on a TM4C129x device via an Ethernet link.
//! The UART can be connected to the UART on a non-networked device.  This can
//! be useful to overcome limitations such as adding multiple serial devices to
//! a shared network and inability to access the device from long distances
//! without modifying the serial device.  Telnet protocol is used to transfer
//! the serial data over Ethernet.  Two Serial-to-Telnet ports are implemented.
//!
//! The application uses lwIP Stack to manage TCP/IP layers.  DHCP or Static IP
//! configuration can be used to obtain an IP address.  If DHCP configuration
//! is used, and it times out without obtaining an address, AutoIP will be used
//! to obtain a link-local address.
//!
//! FreeRTOS is used to perform a variety of tasks in a concurrent fashion.
//! The following tasks are created:
//! * An Ethernet task to manage the Ethernet interface and its interrupt.
//! * A TCP/IP task to run the lwIP stack and manage all the TCP/IP packets.
//!   This task works very closely with the Ethernet task to server web pages,
//!   handle Telnet packets and Locator app packets.  Ethernet and TCP/IP tasks
//!   are managed by lwIP.
//! * A serial task to manage the serial peripherals and their interrupts.
//! * An idle task (automatically created by FreeRTOS) that manages changes to
//!   the IP address and sends this information to the user via Debug UART.
//!
//! To build this application, install TivaWare for C Series v2.1.0.12573 or
//! higher and copy the "enet_s2e" application folder into the EK-TM4C1294XL
//! board's folder at <TivaWare_Install_Folder>/examples/boards/ek-tm4c1294xl.
//!
//! The IP address and other debug messages are displayed on the Debug UART.
//! UART0, connected to the ICDI virtual COM port, is used as the Debug UART.
//! 115,200 baud with 8-N-1 settings is used to display debug messages from
//! this application.
//!
//! The finder application (in ../../../../tools/bin/) can also be used to
//! discover the IP address of the board.  The finder application will search
//! the network for all boards that respond to its requests and display
//! information about them.
//!
//! A configuration webserver is hosted to provide a convenient interface to
//! manage the various configuration options.  To access the webserver, enter
//! the IP address of the S2E module in a web browser.  The following command
//! can be used to re-build any file system files that change.
//!
//!   ../../../../tools/bin/makefsfile -i fs -o enet_fsdata.h -r -h -q
//!
//! For additional details on FreeRTOS, refer to the FreeRTOS web page at:
//! http://www.freertos.org/
//!
//! For additional details on lwIP, refer to the lwIP web page at:
//! http://savannah.nongnu.org/projects/lwip/
//
//*****************************************************************************

//*****************************************************************************
//
// Define for the DK-TM4C129X board.  By default this application works with
// the EK-TM4C1294XL board.  To work with the DK-TM4C129X board:
// 1) Copy the enet_s2e folder into the DK-TM4C129X boards folder
// (../../dk_tm4c129x).
// 2) In project settings, replace PART_TM4C1294NCPDT and TARGET_IS_TM4C129_RA1
//    with PART_TM4C129XNCZAD and TARGET_IS_TM4C129_RA0.
// 3) Uncomment the following line.
//
//*****************************************************************************
// #define DK-TM4C129X

//*****************************************************************************
//
// The current IP address.
//
//*****************************************************************************
uint32_t g_ui32IPAddress;

//*****************************************************************************
//
// The system clock frequency.
//
//*****************************************************************************
uint32_t g_ui32SysClock;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// The main entry function which configures the clock and hardware peripherals
// needed by the S2E application before calling the FreeRTOS scheduler.
//
//*****************************************************************************
int
main(void)
{
    //
    // Run from the PLL at configCPU_CLOCK_HZ MHz.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480),
                                            configCPU_CLOCK_HZ);

    //
    // Configure the device pins based on the selected board.
    //
#ifndef DK_TM4C129X
    PinoutSet(true, false);
#else
    PinoutSet();
#endif

    //
    // Configure Debug UART.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);

    //
    // Clear the terminal and print banner.
    //
    UARTprintf("\033[2J\033[H");
    UARTprintf("Serial to Ethernet Example\n\n");

    //
    // Tell the user what we are doing now.
    //
    UARTprintf("Waiting for IP.\n");

    //
    // Initialize the configuration parameter module.
    //
    ConfigInit();

    //
    // Initialize the Ethernet peripheral and create the lwIP tasks.
    //
    if(lwIPTaskInit() != 0)
    {
        UARTprintf("Failed to create lwIP tasks!\n");
        while(1)
        {
        }
    }

    //
    // Initialize the serial peripherals and create the Serial task.
    //
    if(SerialTaskInit() != 0)
    {
        UARTprintf("Failed to create Serial task!\n");
        while(1)
        {
        }
    }

    //
    // Start the scheduler.  This should not return.
    //
    vTaskStartScheduler();

    //
    // In case the scheduler returns for some reason, print an error and loop
    // forever.
    //
    UARTprintf("\nScheduler returned unexpectedly!\n");
    while(1)
    {
    }
}
