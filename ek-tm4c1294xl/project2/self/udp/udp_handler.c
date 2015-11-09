/*------------------------------------------------------------------------------
UDP_HANDLER.C


------------------------------------------------------------------------------*/

#include "self/main.h"
#include "self/settings.h"
#include "../delay.h"
#include <stdint.h>
#include "utils/locator.h"
#include "utils/lwiplib.h"
#include "driverlib/sysctl.h"
#include "lwip/udp.h"
#include "../delay.h"
#include "driverlib/sysctl.h"
#include "udp_output.h"

static void UDP_In(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
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
      if (pui8Data[1] == 'I') {
        UDPOutput_GetLong3(pcb, p, addr, port, dwIP, dwGateway, dwNetmask);
      } else {
        UDPOutput_Unknown(pcb,p,addr,port);
      }
    } else if (pui8Data[0] == 'S') {
      if (pui8Data[1] == 'I') {
        UDPOutput_SetLong3(pcb, p, addr, port, &dwIP, &dwGateway, &dwNetmask);
        SaveSettings();

        DelayMillySecond(100);
        SysCtlReset();
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



void    InitUDP_Handler(void)
{
  void *pcb = udp_new();
  udp_recv(pcb, UDP_In, NULL);
  udp_bind(pcb, IP_ADDR_ANY, 0xFFFF);
}
