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

  if (pbBuff[0] == 'M') {
    UDPOut_MAC(pcb, p, addr, port);
  } else if (pbBuff[0] == 'G') {
    if (pbBuff[1] == 'I') {
      UDPOut_GetLong3(pcb, p, addr, port, dwIP, dwGateway, dwNetmask);
    } else {
      UDPOut_Unknown(pcb,p,addr,port);
    }
  } else if (pbBuff[0] == 'S') {
    if (pbBuff[1] == 'I') {
      UDPOut_SetLong3(pcb, p, addr, port, &dwIP, &dwGateway, &dwNetmask);
      SaveSettings();

      DelayMillySecond(100);
      SysCtlReset();
    } else {
      UDPOut_Unknown(pcb,p,addr,port);
    }
  } else if (pbBuff[0] == 'B') {
    UDPOut_Begin(pcb,p,addr,port);
  } else if (pbBuff[0] == 'E') {
    UDPOut_End(pcb,p,addr,port);
  } else {
    UDPOut_Unknown(pcb,p,addr,port);
  }
}
