/*------------------------------------------------------------------------------
echo.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/wrappers.h"
#include "../kernel/settings.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "broadcast_select.h"
#include "echo.h"



static bool HardwareError(void)
{
  return ((cwErrSettingsInitStorage > 0) || (cwErrSettingsSaveEntity > 0));
}

static bool EthernetToSerialBufferOverflow(void)
{
  return false; // TODO Ethernet-to-serial buffer overflow
}

static bool SerialToEthernetBufferOverflow(void)
{
  return false; // TODO serial-to-Ethernet buffer overflow
}


err_t OutEcho(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast)
{
  if (broadcast == 0)
    fBroadcastSelect = true;

  uint wSfx = 0;

  if (p->len > 1)
  {
    uint2 w2 = PopSfx(p);
    if (InvalidInt2(w2)) return w2.err;
    wSfx = w2.w;
  }

  InitPush();
  PushChar('A');
  PushMAC(mbMAC, 6);
  PushChar('/');
  PushStringZ("000001001"); // TODO "000001001"
  PushChar('/');
  PushChar('N');
  PushChar('*');
  HardwareError() ? PushChar('E') : PushChar('*');
  PushChar('M');
  PushChar('*');
  PushChar('/');
  EthernetToSerialBufferOverflow() ? PushChar('E') : PushChar('*');
  SerialToEthernetBufferOverflow() ? PushChar('S') : PushChar('*');
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
