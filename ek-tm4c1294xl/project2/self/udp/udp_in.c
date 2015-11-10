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
  uchar *pbBuff = p->payload;

  if (pbBuff[0] == 'I') {
    UDP_OutInfo(pcb,p,addr,port,broadcast,dwIP);
  } else if (pbBuff[0] == 'G') {
    if (pbBuff[1] == 'I') {
      UDP_OutGetLong3(pcb,p,addr,port,broadcast,dwIP,dwGateway,dwNetmask);
    } else {
      UDP_OutUnknown(pcb,p,addr,port,broadcast);
    }
  } else if (pbBuff[0] == 'S') {
    if (pbBuff[1] == 'I') {
      UDP_OutSetLong3(pcb,p,addr,port,broadcast,&dwIP,&dwGateway,&dwNetmask);
      SaveSettings();

      DelayMillySecond(100);
      SysCtlReset();
    } else {
      UDP_OutUnknown(pcb,p,addr,port,broadcast);
    }
  } else if (pbBuff[0] == 'B') {
    UDP_OutBegin(pcb,p,addr,port,broadcast);
  } else if (pbBuff[0] == 'E') {
    UDP_OutEnd(pcb,p,addr,port,broadcast);
  } else {
    UDP_OutUnknown(pcb,p,addr,port,broadcast);
  }
}
