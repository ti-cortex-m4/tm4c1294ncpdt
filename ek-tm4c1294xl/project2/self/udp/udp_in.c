/*------------------------------------------------------------------------------
UDP_IN,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/entities.h"
#include "../kernel/controls.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "driverlib/sysctl.h"
#include "../hardware/storage.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_in_common.h"
#include "udp_out_common.h"
#include "udp_out_controls.h"
#include "udp_entities.h"
#include "routing_status.h"
#include "test_watchdog.h"
#include "udp_in.h"



typedef err_t (*in_fn)(struct pbuf *p);


typedef struct
{
  struct udp_pcb *pcb;
  struct pbuf *p;
  struct ip_addr *addr;
  uint port;
  uchar broadcast;
} udp_arg;



err_t CmdX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  if (p->len > 1)
  {
    uint2 w2 = PopSfx(p);
    if (InvalidInt2(w2)) return w2.err;
    wSfx = w2.w;
  }

  InitPush();
  PushString("A");
  PushMAC(pbMac, 6);
  PushString("/");
  PushString("000001001"); // TODO "000001001"
  PushString("/");
  PushString("N**M*"); // TODO "N**M*"
  PushString("/");
  PushString("**"); // TODO "**"
  PushString("/");
  PushString(szOwnerName);
  PushString("/");
  PushString(szDeviceName);
  PushString("/");
  PushCharDec(UART_COUNT);

  if (p->len > 1)
  {
    PushSfx(wSfx);
  }

  return Out(pcb,p,addr,port,broadcast);
}

err_t CmdW(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}

err_t CmdIn(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, in_fn in)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  err_t err = in(p);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


void    UDPInput(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
{
//  CONSOLE("broadcast: %d\n", broadcast);

  if (IsCmd(p,"X")) {
    CmdX(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"W")) {
    CmdW(pcb,p,addr,port,broadcast); // TODO
  } else if (IsCmd(p,"E")) {
    SysCtlReset();
  } else if (IsCmd(p,"L")) {
    OutString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"I")) {
    ResetSettings();
    OutString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"O")) {
    OutString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"V")) {
    OutString(pcb,p,addr,port,broadcast,"{ds1.0}");
  } else if (IsCmd(p,"H")) {
    OutString(pcb,p,addr,port,broadcast,"1A");
  } else if (IsCmd(p,"CS")) {
    OutIntDec(pcb,p,addr,port,broadcast,wControlsSize);
  } else if (IsCmd(p,"FS")) {
    OutControls(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    OutString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    OutString(pcb,p,addr,port,broadcast,"0");
  } else if (IsRoutingStatusSize(p)) {
    GetRouingStatusSize(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"watchdog")) {
    TestWatchdog(pcb,p,addr,port,broadcast);
  }

  else if (AreEnities(pcb,p,addr,port,broadcast)) {
  }

  else if (IsRoutingStatusContent(p)) {
    GetRouingStatusContent(pcb,p,addr,port,broadcast);
  }

  else { // TODO
    WARNING("unknown command\n");
  }
}
