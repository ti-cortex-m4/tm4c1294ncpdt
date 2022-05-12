/*------------------------------------------------------------------------------
udp_log.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/inet.h"
#include "../kernel/settings.h"
#include "udp_log.h"



static void            *pcb;


uint                    cwErrUDPLogPbufAlloc;
uint                    cwErrUDPLogSend;



void InitUDPLog(void) {
  if (ibDebugMode == DEBUG_MODE_UDP) {
    pcb = udp_new();
  }
}



void UDPLog(uchar *pb, uint wSize) {
  if (ibDebugMode == DEBUG_MODE_UDP) {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, wSize, PBUF_RAM);
    if (p == NULL) {
      cwErrUDPLogPbufAlloc++;
      return;
    }

    memcpy(p->payload, pb, wSize);

    if (false)
    {
      const ip_addr_t ip = IPADDR4_INIT(dwUDPDebugIP);
      err_t err = udp_sendto(pcb, p, &ip, wUDPDebugPort);
      if (err != 0) {
        cwErrUDPLogSend++;
      }
    }
    else
    {
      err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, wUDPDebugPort);
      if (err != 0) {
        cwErrUDPLogSend++;
      }
    }

    pbuf_free(p);
  }
}
