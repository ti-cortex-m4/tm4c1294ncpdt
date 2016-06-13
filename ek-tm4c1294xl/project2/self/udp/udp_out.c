/*------------------------------------------------------------------------------
udp_out,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "udp_push.h"
#include "udp_out.h"


uint                    cwErrUPDPushAlloc = 0; // TODO
uint                    cwErrUPDPushSendUnicast = 0;
uint                    cwErrUPDPushSendBroadcast = 0;



err_t UDPOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  pbuf_free(p);

  p = pbuf_alloc(PBUF_TRANSPORT, iwPush, PBUF_RAM);
  if (p == NULL)
  {
    ERROR("UDPOut.pbuf_alloc: NULL\n");
    cwErrUPDPushAlloc++;
    return ERR_MEM;
  }

  memcpy(p->payload, mbPush, iwPush);

  if (broadcast != 0)
  {
    err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
    if (err != ERR_OK)
    {
      ERROR("UDPOut.udp_sendto: err=%u", err);
      cwErrUPDPushSendBroadcast++;
    }
  }
  else
  {
    err_t err = udp_sendto(pcb, p, addr, port);
    if (err != ERR_OK)
    {
      ERROR("UDPOut.udp_sendto: err=%u", err);
      cwErrUPDPushSendUnicast++;
    }
  }

  pbuf_free(p);
  return ERR_OK;
}
