/*------------------------------------------------------------------------------
telnet_include.h


------------------------------------------------------------------------------*/

#ifndef __TELNET_INCLUDE_H__
#define __TELNET_INCLUDE_H__


//*****************************************************************************
//! The possible states of the TCP session.
//*****************************************************************************
typedef enum
{
    //! The TCP session is idle.  No connection has been attempted, nor has it been configured to listen on any port.
    STATE_TCP_IDLE = 0,

    //! The TCP session is listening (server mode).
    STATE_TCP_LISTEN = 1,

    //! The TCP session is connecting (client mode).
    STATE_TCP_CONNECTING = 2,

    //! The TCP session is connected.
    STATE_TCP_CONNECTED = 3,
}
tTCPState;


//*****************************************************************************
//! This structure is used holding the state of a given telnet session.
//*****************************************************************************
typedef struct
{
    //! This value holds the pointer to the TCP PCB associated with this connected telnet session.
    struct tcp_pcb *pConnectPCB;

    //! This value holds the pointer to the TCP PCB associated with this listening telnet session.
    struct tcp_pcb *pListenPCB;

    //! The current state of the TCP session.
    tTCPState eTCPState;

    //! The listen port for the telnet server.
    uint16_t usTelnetLocalPort;

    //! The remote port that the telnet client connects to.
    uint16_t usTelnetRemotePort;

    //! The remote address that the telnet client connects to.
    uint32_t ulTelnetRemoteIP;

    //! A counter for the TCP connection timeout.
    uint32_t ulConnectionTimeout;

    //! The max time for TCP connection timeout counter.
    uint32_t ulMaxTimeout;

    //! This value holds the UART Port Number for this telnet session.
    uint8_t ucSerialPort;

    //! This value holds an array of pbufs.
    struct pbuf *pBufQ[PBUF_POOL_SIZE];

    //! This value holds the read index for the pbuf queue.
    int iBufQRead;

    //! This value holds the write index for the pbuf queue.
    int iBufQWrite;

    //! This value holds the head of the pbuf that is currently being processed (that has been popped from the queue).
    struct pbuf *pBufHead;

    //! This value holds the actual pbuf that is being processed within the pbuf chain pointed to by the pbuf head.
    struct pbuf *pBufCurrent;

    //! This value holds the offset into the payload section of the current pbuf.
    uint32_t ulBufIndex;

    //! The amount of time passed since rx byte count has changed.
    uint32_t ulLastTCPSendTime;

    //! The indication that link layer has been lost.
    bool bLinkLost;

    //! Debug and diagnostic counters.
    uint8_t ucErrorCount;
    uint8_t ucReconnectCount;
    uint8_t ucConnectCount;
}
tState;


#endif
