//*****************************************************************************
//
// idle_task.c - enet_s2e idle task monitors and manages changes to IP address.
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
#include "utils/lwiplib.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "lwip/stats.h"
#include "config.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//*****************************************************************************
//
// The current IP address.
//
//*****************************************************************************
static uint32_t g_ui32IPAddress;

//*****************************************************************************
//
// Displays the IP address in a human-readable format.
//
//*****************************************************************************
static void
DisplayIP(uint32_t ui32IP)
{
    char pcBuf[16];

    //
    // Has IP address been acquired?
    //
    if(ui32IP == 0)
    {
        //
        // If there is no IP address, indicate that one is being acquired.
        //
        UARTprintf("Acquiring IP Address...\n");
        return;
    }
    else if(ui32IP == 0xffffffff)
    {
        //
        // If link is inactive, indicate that.
        //
        UARTprintf("Waiting for link.\n");
        return;
    }

    //
    // Convert the IP Address into a string.
    //
    usprintf(pcBuf, "%d.%d.%d.%d", ui32IP & 0xff, (ui32IP >> 8) & 0xff,
             (ui32IP >> 16) & 0xff, (ui32IP >> 24) & 0xff);

    //
    // Display the string on Debug UART.
    //
    UARTprintf("IP Address: ");
    UARTprintf(pcBuf);
    UARTprintf("\nOpen a browser and enter the IP address to access the "
               "web server.\n");
}

//*****************************************************************************
//
// This hook is called by the FreeRTOS idle task when no other tasks are
// runnable.
//
//*****************************************************************************
void
vApplicationIdleHook(void)
{
    uint32_t ui32Temp;
    portTickType ui32CurrentTick, ui32InitialTick;
    bool bFirst = true;

    //
    // Get the current IP address.
    //
    ui32Temp = lwIPLocalIPAddrGet();

    //
    // See if the IP address has changed.
    //
    if(ui32Temp != g_ui32IPAddress)
    {
        //
        // Save the current IP address.
        //
        g_ui32IPAddress = ui32Temp;

        //
        // Update the display of the IP address.
        //
        DisplayIP(ui32Temp);
    }

    //
    // Check for an IP update request.
    //
    if(g_ui8UpdateRequired)
    {
        //
        // Check if "ui32InitialTick" is to be initialized.
        //
        if(bFirst)
        {
            //
            // Get the initial tick count.  This is used to calculate a two
            // second delay to allow the response page to get back to the
            // browser before the IP address is changed.
            //
            ui32InitialTick = xTaskGetTickCount();

            //
            // Reset 'bFirst' so that 'ui32InitialTick' is not re-initialized.
            //
            bFirst = false;
        }

        //
        // Get the current Tick count.
        //
        ui32CurrentTick = xTaskGetTickCount();

        //
        // Check if 2 seconds have lapsed.
        //
        if((ui32CurrentTick - ui32InitialTick) > 2000 / portTICK_RATE_MS)
        {
            //
            // Are we updating only the IP address?
            //
            if(g_ui8UpdateRequired & UPDATE_IP_ADDR)
            {
                //
                // Actually update the IP address.
                //
                g_ui8UpdateRequired &= ~UPDATE_IP_ADDR;
                ConfigUpdateIPAddress();
            }

            //
            // Are we updating all parameters (including the IP address?)
            //
            if(g_ui8UpdateRequired & UPDATE_ALL)
            {
                //
                // Update everything.
                //
                g_ui8UpdateRequired &= ~UPDATE_ALL;
                ConfigUpdateAllParameters(true);
            }

            //
            // Set 'bFirst' to initialize 'ui32InitialTick'.
            //
            bFirst = true;
        }
    }
}
