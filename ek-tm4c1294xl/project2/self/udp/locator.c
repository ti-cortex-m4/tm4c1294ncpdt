#include "self/main.h"
#include "self/settings.h"
#include "../delay.h"
#include <stdint.h>
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "driverlib/sysctl.h"
#include "lwip/udp.h"
#include "reset.h"
#include "udp_output.h"

//*****************************************************************************
//
//! \addtogroup locator_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// These defines are used to describe the device locator protocol.
//
//*****************************************************************************
#define TAG_CMD                 0xff
#define TAG_STATUS              0xfe
#define CMD_DISCOVER_TARGET     0x02

//*****************************************************************************
//
// An array that contains the device locator response data.  The format of the
// data is as follows:
//
//     Byte        Description
//     --------    ------------------------
//      0          TAG_STATUS
//      1          packet length
//      2          CMD_DISCOVER_TARGET
//      3          board type
//      4          board ID
//      5..8       client IP address
//      9..14      MAC address
//     15..18      firmware version
//     19..82      application title
//     83          checksum
//
//*****************************************************************************
/*static*/ uint8_t g_pui8LocatorData[84];


void GetAll(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    p = pbuf_alloc(PBUF_TRANSPORT, 1+4+4+4, PBUF_RAM);
    if (p == NULL) return;

    uint8_t *pui8Data = p->payload;

    u8_t j=0;
    combo32 cb;

    pui8Data[j++] = 'E';

    cb.dwBuff = dwIP;

    pui8Data[j++] = cb.mpbBuff[0];
    pui8Data[j++] = cb.mpbBuff[1];
    pui8Data[j++] = cb.mpbBuff[2];
    pui8Data[j++] = cb.mpbBuff[3];

    cb.dwBuff = dwGateway;

    pui8Data[j++] = cb.mpbBuff[0];
    pui8Data[j++] = cb.mpbBuff[1];
    pui8Data[j++] = cb.mpbBuff[2];
    pui8Data[j++] = cb.mpbBuff[3];

    cb.dwBuff = dwNetmask;

    pui8Data[j++] = cb.mpbBuff[0];
    pui8Data[j++] = cb.mpbBuff[1];
    pui8Data[j++] = cb.mpbBuff[2];
    pui8Data[j++] = cb.mpbBuff[3];

    udp_sendto(pcb, p, addr, port);
    pbuf_free(p);
}

void SetAll(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    uint8_t *pui8Data = p->payload;

    combo32 cb;
    u8_t j=1;

    cb.mpbBuff[0] = pui8Data[j++];
    cb.mpbBuff[1] = pui8Data[j++];
    cb.mpbBuff[2] = pui8Data[j++];
    cb.mpbBuff[3] = pui8Data[j++];

    dwIP = cb.dwBuff;

    cb.mpbBuff[0] = pui8Data[j++];
    cb.mpbBuff[1] = pui8Data[j++];
    cb.mpbBuff[2] = pui8Data[j++];
    cb.mpbBuff[3] = pui8Data[j++];

    dwGateway = cb.dwBuff;

    cb.mpbBuff[0] = pui8Data[j++];
    cb.mpbBuff[1] = pui8Data[j++];
    cb.mpbBuff[2] = pui8Data[j++];
    cb.mpbBuff[3] = pui8Data[j++];

    dwNetmask = cb.dwBuff;

    SaveSettings();

    p = pbuf_alloc(PBUF_TRANSPORT, 1+4+4+4, PBUF_RAM);
    if (p == NULL) return;

    pui8Data = p->payload;

    j=0;
    pui8Data[j++] = 'G';

    cb.dwBuff = dwIP;
    pui8Data[j++] = cb.mpbBuff[0];
    pui8Data[j++] = cb.mpbBuff[1];
    pui8Data[j++] = cb.mpbBuff[2];
    pui8Data[j++] = cb.mpbBuff[3];

    cb.dwBuff = dwGateway;
    pui8Data[j++] = cb.mpbBuff[0];
    pui8Data[j++] = cb.mpbBuff[1];
    pui8Data[j++] = cb.mpbBuff[2];
    pui8Data[j++] = cb.mpbBuff[3];

    cb.dwBuff = dwNetmask;
    pui8Data[j++] = cb.mpbBuff[0];
    pui8Data[j++] = cb.mpbBuff[1];
    pui8Data[j++] = cb.mpbBuff[2];
    pui8Data[j++] = cb.mpbBuff[3];

    udp_sendto(pcb, p, addr, port);
    pbuf_free(p);

    Delay(1000);
    SysCtlReset();
}


//*****************************************************************************
//
// This function is called by the lwIP TCP/IP stack when it receives a UDP
// packet from the discovery port.  It produces the response packet, which is
// sent back to the querying client.
//
//*****************************************************************************
static void
LocatorReceive(void *arg, struct udp_pcb *pcb, struct pbuf *p,
               struct ip_addr *addr, u16_t port)
{
    uint8_t *pui8Data;
//    uint32_t ui32Idx;

    //
    // Validate the contents of the datagram.
    //
    pui8Data = p->payload;
/*
    if((p->len != 4) || (pui8Data[0] != TAG_CMD) || (pui8Data[1] != 4) ||
       (pui8Data[2] != CMD_DISCOVER_TARGET) ||
       (pui8Data[3] != ((0 - TAG_CMD - 4 - CMD_DISCOVER_TARGET) & 0xff)))
    {
        pbuf_free(p);
        return;
    }
*/
    //
    // The incoming pbuf is no longer needed, so free it.
    //
    pbuf_free(p);

    if (pui8Data[0] == 'M') {
      UDPOutput_MAC(pcb, p, addr, port);
    } else if (pui8Data[0] == 'G') {
      if ((pui8Data[1] == 'I') && (pui8Data[2] == 'P')) {
        UDPOutput_GetLong(pcb, p, addr, port, dwIP);
      } else if ((pui8Data[1] == 'G') && (pui8Data[2] == 'W')) {
        UDPOutput_GetLong(pcb, p, addr, port, dwGateway);
      } else if ((pui8Data[1] == 'N') && (pui8Data[2] == 'M')) {
        UDPOutput_GetLong(pcb, p, addr, port, dwNetmask);
      } else {
        UDPOutput_Unknown(pcb,p,addr,port);
      }
    } else if (pui8Data[0] == 'S') {
      if ((pui8Data[1] == 'N') && (pui8Data[2] == 'W')) {
        UDPOutput_Set3Long(pcb, p, addr, port, &dwIP, &dwGateway, &dwNetmask);
        SaveSettings();
        Reset();
      } else {
        UDPOutput_Unknown(pcb,p,addr,port);
      }
    } else if (pui8Data[0] == 'B') {
      UDPOutput_Begin(pcb,p,addr,port);
    } else if (pui8Data[0] == 'E') {
      UDPOutput_End(pcb,p,addr,port);
    } else {
      UDPOutput_Unknown(pcb,p,addr,port);
    }
}

//*****************************************************************************
//
//! Initializes the locator service.
//!
//! This function prepares the locator service to handle device discovery
//! requests.  A UDP server is created and the locator response data is
//! initialized to all empty.
//!
//! \return None.
//
//*****************************************************************************
void
LocatorInit(void)
{
    uint32_t ui32Idx;
    void *pcb;

    //
    // Clear out the response data.
    //
    for(ui32Idx = 0; ui32Idx < 84; ui32Idx++)
    {
        g_pui8LocatorData[ui32Idx] = 0;
    }

    //
    // Fill in the header for the response data.
    //
    g_pui8LocatorData[0] = TAG_STATUS;
    g_pui8LocatorData[1] = sizeof(g_pui8LocatorData);
    g_pui8LocatorData[2] = CMD_DISCOVER_TARGET;

    //
    // Fill in the MAC address for the response data.
    //
    g_pui8LocatorData[9] = 0;
    g_pui8LocatorData[10] = 0;
    g_pui8LocatorData[11] = 0;
    g_pui8LocatorData[12] = 0;
    g_pui8LocatorData[13] = 0;
    g_pui8LocatorData[14] = 0;

#if LWIP_IGMP
    ip_addr_t groupaddr;
	groupaddr.addr = inet_addr("238.255.255.255");
    err_t iret = igmp_joingroup(IP_ADDR_ANY, &groupaddr);
    UARTprintf("ret of igmp_joingroup: %d \n\r",iret);
#endif

    //
    // Create a new UDP port for listening to device locator requests.
    //
    pcb = udp_new();
    udp_recv(pcb, LocatorReceive, NULL);
    udp_bind(pcb, IP_ADDR_ANY, 0xFFFF);
}

//*****************************************************************************
//
//! Sets the board type in the locator response packet.
//!
//! \param ui32Type is the type of the board.
//!
//! This function sets the board type field in the locator response packet.
//!
//! \return None.
//
//*****************************************************************************
void
LocatorBoardTypeSet(uint32_t ui32Type)
{
    //
    // Save the board type in the response data.
    //
    g_pui8LocatorData[3] = ui32Type & 0xff;
}

//*****************************************************************************
//
//! Sets the board ID in the locator response packet.
//!
//! \param ui32ID is the ID of the board.
//!
//! This function sets the board ID field in the locator response packet.
//!
//! \return None.
//
//*****************************************************************************
void
LocatorBoardIDSet(uint32_t ui32ID)
{
    //
    // Save the board ID in the response data.
    //
    g_pui8LocatorData[4] = ui32ID & 0xff;
}

//*****************************************************************************
//
//! Sets the client IP address in the locator response packet.
//!
//! \param ui32IP is the IP address of the currently connected client.
//!
//! This function sets the IP address of the currently connected client in the
//! locator response packet.  The IP should be set to 0.0.0.0 if there is no
//! client connected.  It should never be set for devices that do not have a
//! strict one-to-one mapping of client to server (for example, a web server).
//!
//! \return None.
//
//*****************************************************************************
void
LocatorClientIPSet(uint32_t ui32IP)
{
    //
    // Save the client IP address in the response data.
    //
    g_pui8LocatorData[5] = ui32IP & 0xff;
    g_pui8LocatorData[6] = (ui32IP >> 8) & 0xff;
    g_pui8LocatorData[7] = (ui32IP >> 16) & 0xff;
    g_pui8LocatorData[8] = (ui32IP >> 24) & 0xff;
}
