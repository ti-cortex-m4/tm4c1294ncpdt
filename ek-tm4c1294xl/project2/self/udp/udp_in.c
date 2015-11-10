/*------------------------------------------------------------------------------
UDP_IN.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "../delay.h"
#include "driverlib/sysctl.h"
#include "udp_out.h"
#include "udp_in.h"



void    UDP_In(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
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


    if (pui8Data[0] == 'M') {
      UDPOut_MAC(pcb, p, addr, port);
    } else if (pui8Data[0] == 'G') {
      if (pui8Data[1] == 'I') {
        UDPOut_GetLong3(pcb, p, addr, port, dwIP, dwGateway, dwNetmask);
      } else {
        UDPOut_Unknown(pcb,p,addr,port);
      }
    } else if (pui8Data[0] == 'S') {
      if (pui8Data[1] == 'I') {
        UDPOut_SetLong3(pcb, p, addr, port, &dwIP, &dwGateway, &dwNetmask);
        SaveSettings();

        DelayMillySecond(100);
        SysCtlReset();
      } else {
        UDPOut_Unknown(pcb,p,addr,port);
      }
    } else if (pui8Data[0] == 'B') {
      UDPOut_Begin(pcb,p,addr,port);
    } else if (pui8Data[0] == 'E') {
      UDPOut_End(pcb,p,addr,port);
    } else {
      UDPOut_Unknown(pcb,p,addr,port);
    }
}
