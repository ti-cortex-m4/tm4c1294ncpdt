/*------------------------------------------------------------------------------
MAIN,H

Configuration of the serial to Ethernet converter.
------------------------------------------------------------------------------*/

#ifndef __CONFIG_H__
#define __CONFIG_H__


void UdpPrintF(const char *sz, ...);


#define DEBUG_UART 0


//*****************************************************************************
// During debug, DEBUG_UART may be defined with values 0 or 1 to select which
// of the two UARTs are used to output debug messages.  Debug messages will be
// interleaved with any telnet data also being carried via that UART so great
// care must be exercised when enabling this debug option.  Typically, you
// should use only a single telnet connection when debugging with DEBUG_UART
// set to use the inactive UART.
//*****************************************************************************
#ifdef DEBUG_UART
#define CONSOLE UdpPrintF
//#define CONSOLE UARTprintf
#else
#define CONSOLE while(0) ((int (*)(char *, ...))0)
#endif


//*****************************************************************************
//! The number of serial to Ethernet ports supported by this module.
//*****************************************************************************
#define UART_COUNT              3


//*****************************************************************************
//! Bit 0 of field ucFlags in tPortParameters is used to indicate whether to
//! operate as a telnet server or a telnet client.
//*****************************************************************************
#define PORT_FLAG_TELNET_MODE   0x01

//*****************************************************************************
// Helpful labels used to determine if we are operating as a telnet client or
// server (based on the state of the PORT_FLAG_TELNET_MODE bit in the ucFlags
// field of tPortParameters).
//*****************************************************************************
#define PORT_TELNET_SERVER      0x00
#define PORT_TELNET_CLIENT      PORT_FLAG_TELNET_MODE

//*****************************************************************************
//! Bit 1 of field ucFlags in tPortParameters is used to indicate whether to
//! bypass the telnet protocol (raw data mode).
//*****************************************************************************
#define PORT_FLAG_PROTOCOL      0x02

//*****************************************************************************
// Helpful labels used to determine if we are operating in raw data mode, or
// in telnet protocol mode.
//*****************************************************************************
#define PORT_PROTOCOL_TELNET    0x00
#define PORT_PROTOCOL_RAW       PORT_FLAG_PROTOCOL


//*****************************************************************************
//! The size of the ring buffers used for interface between the UART and
//! telnet session (RX).
//*****************************************************************************
#define RX_RING_BUF_SIZE        (256 * 2)

//*****************************************************************************
//! The size of the ring buffers used for interface between the UART and
//! telnet session (TX).
//*****************************************************************************
#define TX_RING_BUF_SIZE        (256 * 6)


#endif // __CONFIG_H__
