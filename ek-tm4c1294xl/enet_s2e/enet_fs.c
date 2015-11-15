//*****************************************************************************
//
// enet_fs.c - File System Processing for lwIP Web Server Apps.
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
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/ssi.h"
#include "utils/lwiplib.h"
#include "utils/ustdlib.h"
#include "httpserver_raw/httpd.h"
#include "httpserver_raw/fs.h"
#include "httpserver_raw/fsdata.h"

//*****************************************************************************
//
// Include the file system data for this application.  This file is generated
// by the makefsfile utility, using the following command:
//
//     ../../../../tools/bin/makefsfile -i fs -o enet_fsdata.h -r -h -q
//
// If any changes are made to the static content of the web pages served by the
// application, this command must be used to regenerate enet_fsdata.h in order
// for those changes to be picked up by the web server.
//
//*****************************************************************************
#include "enet_fsdata.h"

//*****************************************************************************
//
// The number of milliseconds that has passed since the last disk_timerproc()
// call.
//
//*****************************************************************************
static uint32_t ui32TickCounter = 0;

//*****************************************************************************
//
// Initialize the file system.
//
//*****************************************************************************
void
fs_init(void)
{
}

//*****************************************************************************
//
// File System tick handler.
//
//*****************************************************************************
void
fs_tick(uint32_t ui32TickMS)
{
    //
    // Increment the tick counter.
    //
    ui32TickCounter += ui32TickMS;
}

//*****************************************************************************
//
// Open a file and return a handle to the file, if found.  Otherwise,
// return NULL.
//
//*****************************************************************************
struct fs_file *
fs_open(const char *pcName)
{
    const struct fsdata_file *psTree;
    struct fs_file *psFile = NULL;

    //
    // Allocate memory for the file system structure.
    //
    psFile = mem_malloc(sizeof(struct fs_file));
    if(psFile == NULL)
    {
        return(NULL);
    }

    //
    // Initialize the file system tree pointer to the root of the linked list.
    //
    psTree = FS_ROOT;

    //
    // Begin processing the linked list, looking for the requested file name.
    //
    while(NULL != psTree)
    {
        //
        // Compare the requested file "name" to the file name in the
        // current node.
        //
        if(ustrncmp(pcName, (char *)psTree->name, psTree->len) == 0)
        {
            //
            // Fill in the data pointer and length values from the
            // linked list node.
            //
            psFile->data = (char *)psTree->data;
            psFile->len = psTree->len;

            //
            // For now, we setup the read index to the end of the file,
            // indicating that all data has been read.
            //
            psFile->index = psTree->len;

            //
            // We are not using any file system extensions in this
            // application, so set the pointer to NULL.
            //
            psFile->pextension = NULL;

            //
            // Exit the loop and return the file system pointer.
            //
            break;
        }

        //
        // If we get here, we did not find the file at this node of the linked
        // list.  Get the next element in the list.
        //
        psTree = psTree->next;
    }

    //
    // If we didn't find the file, ptTee will be NULL.  Make sure we
    // return a NULL pointer if this happens.
    //
    if(psTree == NULL)
    {
        mem_free(psFile);
        psFile = NULL;
    }

    //
    // Return the file system pointer.
    //
    return(psFile);
}

//*****************************************************************************
//
// Close an opened file designated by the handle.
//
//*****************************************************************************
void
fs_close(struct fs_file *psFile)
{
    //
    // Free the main file system object.
    //
    mem_free(psFile);
}

//*****************************************************************************
//
// Read the next chunck of data from the file.  Return the count of data
// that was read.  Return 0 if no data is currently available.  Return
// a -1 if at the end of file.
//
//*****************************************************************************
int
fs_read(struct fs_file *psFile, char *pcBuffer, int iCount)
{
    int iAvailable;

    //
    // Check to see if more data is available.
    //
    if(psFile->index == psFile->len)
    {
        //
        // There is no remaining data.  Return a -1 for EOF indication.
        //
        return(-1);
    }

    //
    // Determine how much data we can copy.  The minimum of the 'iCount'
    // parameter or the available data in the file system buffer.
    //
    iAvailable = psFile->len - psFile->index;
    if(iAvailable > iCount)
    {
        iAvailable = iCount;
    }

    //
    // Copy the data.
    //
    memcpy(pcBuffer, psFile->data + iAvailable, iAvailable);
    psFile->index += iAvailable;

    //
    // Return the count of data that we copied.
    //
    return(iAvailable);
}

//*****************************************************************************
//
// Determine the number of bytes left to read from the file.
//
//*****************************************************************************
int
fs_bytes_left(struct fs_file *psFile)
{
    //
    // Return the number of bytes left to be read from this file.
    //
    return(psFile->len - psFile->index);
}
