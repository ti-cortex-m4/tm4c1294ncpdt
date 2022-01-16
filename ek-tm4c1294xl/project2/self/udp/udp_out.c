/*------------------------------------------------------------------------------
udp_out.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "udp_push.h"
#include "udp_out.h"



uint                    cwErrUPDOutPbufAlloc = 0;
uint                    cwErrUPDOutSendUnicast = 0;
uint                    cwErrUPDOutSendBroadcast = 0;



err_t Out(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast) {
  pbuf_free(p);

  p = pbuf_alloc(PBUF_TRANSPORT, iwUDPPush, PBUF_RAM);
  if (p == NULL) {
    ERROR("Out.pbuf_alloc: NULL\n");
    cwErrUPDOutPbufAlloc++;
    return ERR_MEM;
  }

  memcpy(p->payload, mbUDPPush, iwUDPPush);

  if (broadcast != 0) {
    err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
    if (err != ERR_OK) {
      ERROR("Out.udp_sendto: send broadcast, error=%d\n", err);
      cwErrUPDOutSendBroadcast++;
    }
  } else {
    err_t err = udp_sendto(pcb, p, addr, port);
    if (err != ERR_OK) {
      ERROR("Out.udp_sendto: send unicast, error=%d\n", err);
      cwErrUPDOutSendUnicast++;
    }
  }

  pbuf_free(p);
  return ERR_OK;
}
