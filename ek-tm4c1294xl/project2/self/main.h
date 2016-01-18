/*------------------------------------------------------------------------------
MAIN.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_H__
#define __MAIN_H__


#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "lwip/tcp.h"
#include "driverlib/debug.h"


typedef uint8_t         uchar;
typedef uint16_t        uint;
typedef uint32_t        ulong;


typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
} combo32;


#define NAME_SIZE       (8+1)


#define UART_COUNT      1


typedef struct
{
//    //
//    //! This value holds the pointer to the TCP PCB associated with this
//    //! connected telnet session.
//    //
//    struct tcp_pcb *pConnectPCB;
//
//    //
//    //! This value holds the pointer to the TCP PCB associated with this
//    //! listening telnet session.
//    //
//    struct tcp_pcb *pListenPCB;
//
//    //
//    //! The current state of the TCP session.
//    //
//    tTCPState eTCPState;
//
//    //
//    //! The current state of the telnet option parser.
//    //
//    tTelnetState eTelnetState;
//
//    //
//    //! The listen port for the telnet server or the local port for the telnet
//    //! client.
//    //
//    uint16_t usTelnetLocalPort;
//
//    //
//    //! The remote port that the telnet client connects to.
//    //
//    uint16_t usTelnetRemotePort;
//
//    //
//    //! The remote address that the telnet client connects to.
//    //
//    uint32_t ulTelnetRemoteIP;
//
//    //
//    //! Flags for various options associated with the telnet session.
//    //
//    uint8_t ucFlags;
//
//    //
//    //! A counter for the TCP connection timeout.
//    //
//    uint32_t ulConnectionTimeout;
//
//    //
//    //! The max time for TCP connection timeout counter.
//    //
//    uint32_t ulMaxTimeout;
//
//    //
//    //! This value holds the UART Port Number for this telnet session.
//    //
//    uint32_t ulSerialPort;
//
//    //
//    //! This value holds an array of pbufs.
//    //
//    struct pbuf *pBufQ[PBUF_POOL_SIZE];
//
//    //
//    //! This value holds the read index for the pbuf queue.
//    //
//    int iBufQRead;
//
//    //
//    //! This value holds the write index for the pbuf queue.
//    //
//    int iBufQWrite;
//
//    //
//    //! This value holds the head of the pbuf that is currently being
//    //! processed (that has been popped from the queue).
//    //
//    struct pbuf *pBufHead;
//
//    //
//    //! This value holds the actual pbuf that is being processed within the
//    //! pbuf chain pointed to by the pbuf head.
//    //
//    struct pbuf *pBufCurrent;
//
//    //
//    //! This value holds the offset into the payload section of the current
//    //! pbuf.
//    //
//    uint32_t ulBufIndex;
//
//    //
//    //! The amount of time passed since rx byte count has changed.
//    //
//    uint32_t ulLastTCPSendTime;
//
//    //
//    //! The indication that link layer has been lost.
//    //
//    bool bLinkLost;

  // Debug and diagnostic counters.
  uint8_t ucErrorCount;
  uint8_t ucReconnectCount;
  uint8_t ucConnectCount;

  // The last error reported by lwIP while attempting to make a connection.
  err_t eLastErr;
} tState;


#endif
