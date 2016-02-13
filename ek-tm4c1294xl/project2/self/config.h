/*------------------------------------------------------------------------------
MAIN.H

Configuration of the serial to Ethernet converter.
------------------------------------------------------------------------------*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

//*****************************************************************************
// During debug, DEBUG_UART may be defined with values 0 or 1 to select which
// of the two UARTs are used to output debug messages.  Debug messages will be
// interleaved with any telnet data also being carried via that UART so great
// care must be exercised when enabling this debug option.  Typically, you
// should use only a single telnet connection when debugging with DEBUG_UART
// set to use the inactive UART.
//*****************************************************************************
#ifdef DEBUG_UART
#define DEBUG_MSG UARTprintf
#else
#define DEBUG_MSG while(0) ((int (*)(char *, ...))0)
#endif

//*****************************************************************************
//! The number of serial to Ethernet ports supported by this module.
//*****************************************************************************
#define MAX_S2E_PORTS           2

#endif // __CONFIG_H__
