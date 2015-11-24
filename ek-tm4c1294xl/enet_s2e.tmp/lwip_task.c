//*****************************************************************************
//
// lwip_task.c - Tasks to serve web pages and TCP/IP packets over Ethernet
//               using lwIP.
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

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "utils/lwiplib.h"
#include "utils/locator.h"
#include "utils/ustdlib.h"
#include "httpserver_raw/httpd.h"
#include "lwip/inet.h"
#include "config.h"
#include "lwip_task.h"
#include "priorities.h"
#include "telnet.h"

//*****************************************************************************
//
// External References.
//
//*****************************************************************************
extern uint32_t g_ui32SysClock;

//*****************************************************************************
//
// Keeps track of elapsed time in milliseconds.
//
//*****************************************************************************
uint32_t g_ui32SystemTimeMS = 0;

//*****************************************************************************
//
// A flag indicating the current link status.
//
//*****************************************************************************
volatile bool g_bLinkStatusUp = false;

//*****************************************************************************
//
// Required by lwIP library to support any host-related timer functions.  This
// function is called periodically, from the lwIP (TCP/IP) timer task context,
// every "HOST_TMR_INTERVAL" ms (defined in lwipopts.h file).
//
//*****************************************************************************
void
lwIPHostTimerHandler(void)
{
    bool bLinkStatusUp;

    //
    // Get the current link status and see if it has changed.
    //
    bLinkStatusUp = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) ? true : false;
    if(bLinkStatusUp != g_bLinkStatusUp)
    {
        //
        // Save the new link status.
        //
        g_bLinkStatusUp = bLinkStatusUp;

        //
        // Notify the Telnet module that the link status has changed.
        //
        TelnetNotifyLinkStatus(g_bLinkStatusUp);
    }

    //
    // Service the Telnet handler which transfers data between the UART and the
    // Telnet sockets.
    //
    TelnetHandler();
}

//*****************************************************************************
//
// Setup lwIP raw API services that are provided by the application.  The
// services provided in this application are - http server, locator service
// and Telnet server/client.
//
//*****************************************************************************
void
SetupServices(void *pvArg)
{
    uint8_t pui8MAC[6];
    uint32_t ui32Loop;

    //
    // Setup the device locator service.
    //
    LocatorInit();
    lwIPLocalMACGet(pui8MAC);
    LocatorMACAddrSet(pui8MAC);
    LocatorAppTitleSet("EK-TM4C1294XL enet_s2e");

    //
    // Initialize the telnet module.
    //
    TelnetInit();

    //
    // Initialize the telnet session(s).
    //
    for(ui32Loop = 0; ui32Loop < MAX_S2E_PORTS; ui32Loop++)
    {
        //
        // Are we to operate as a telnet server?
        //
        if((g_sParameters.sPort[ui32Loop].ui8Flags & PORT_FLAG_TELNET_MODE) ==
           PORT_TELNET_SERVER)
        {
            //
            // Yes - start listening on the required port.
            //
            TelnetListen(g_sParameters.sPort[ui32Loop].ui16TelnetLocalPort,
                         ui32Loop);
        }
        else
        {
            //
            // No - we are a client so initiate a connection to the desired
            // IP address using the configured ports.
            //
            TelnetOpen(g_sParameters.sPort[ui32Loop].ui32TelnetIPAddr,
                       g_sParameters.sPort[ui32Loop].ui16TelnetRemotePort,
                       g_sParameters.sPort[ui32Loop].ui16TelnetLocalPort,
                       ui32Loop);
        }
    }

    //
    // Initialize the sample httpd server.
    //
    httpd_init();

    //
    // Configure SSI and CGI processing for our configuration web forms.
    //
    ConfigWebInit();
}

//*****************************************************************************
//
// Initializes the lwIP tasks.
//
//*****************************************************************************
uint32_t
lwIPTaskInit(void)
{
    uint32_t ui32User0, ui32User1;
    uint8_t pui8MAC[6];

    //
    // Get the MAC address from the user registers.
    //
    MAP_FlashUserGet(&ui32User0, &ui32User1);
    if((ui32User0 == 0xffffffff) || (ui32User1 == 0xffffffff))
    {
        return(1);
    }

    //
    // Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC
    // address needed to program the hardware registers, then program the MAC
    // address into the Ethernet Controller registers.
    //
    pui8MAC[0] = ((ui32User0 >>  0) & 0xff);
    pui8MAC[1] = ((ui32User0 >>  8) & 0xff);
    pui8MAC[2] = ((ui32User0 >> 16) & 0xff);
    pui8MAC[3] = ((ui32User1 >>  0) & 0xff);
    pui8MAC[4] = ((ui32User1 >>  8) & 0xff);
    pui8MAC[5] = ((ui32User1 >> 16) & 0xff);

    //
    // Lower the priority of the Ethernet interrupt handler to less than
    // configMAX_SYSCALL_INTERRUPT_PRIORITY.  This is required so that the
    // interrupt handler can safely call the interrupt-safe FreeRTOS functions
    // if any.
    //
    MAP_IntPrioritySet(INT_EMAC0, ETHERNET_INT_PRIORITY);

    //
    // Set the link status based on the LED0 signal (which defaults to link
    // status in the PHY).
    //
    g_bLinkStatusUp = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3) ? false : true;

    //
    // Initialize lwIP.
    //
    lwIPInit(g_ui32SysClock, pui8MAC, inet_addr("100.1.168.192"), inet_addr("0.255.255.255"), inet_addr("1.1.168.192"), IPADDR_USE_STATIC);

    //
    // Setup the remaining services inside the TCP/IP thread's context.
    //
    tcpip_callback(SetupServices, 0);

    //
    // Success.
    //
    return(0);
}
