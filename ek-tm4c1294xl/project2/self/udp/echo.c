/*------------------------------------------------------------------------------
echo.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/wrappers.h"
#include "../kernel/settings.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "echo.h"



err_t OutEcho(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  if (p->len > 1)
  {
    uint2 w2 = PopSfx(p);
    if (InvalidInt2(w2)) return w2.err;
    wSfx = w2.w;
  }

  InitPush();
  PushChar('A');
  PushMAC(pbMAC, 6);
  PushChar('/');
  PushStringZ("000001001"); // TODO "000001001"
  PushChar('/');
  PushChar('N');
  PushChar('*');
  PushChar('*');
  PushChar('M');
  PushChar('*');
  PushChar('/');
  (false) ? PushChar('E') : PushChar('*'); // TODO Ethernet-to-serial buffer overflow
  (false) ? PushChar('S') : PushChar('*'); // TODO serial-to-Ethernet buffer overflow
  PushChar('/');
  PushStringZ(szOwnerName);
  PushChar('/');
  PushStringZ(szDeviceName);
  PushChar('/');
  PushCharDec(UART_COUNT);

  if (p->len > 1)
  {
    PushSfx(wSfx);
  }

  return Out(pcb,p,addr,port,broadcast);
}
