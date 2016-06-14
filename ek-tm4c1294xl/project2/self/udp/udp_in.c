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

  else if (IsEnity(pcb,p,addr,port,broadcast,&enOwnerName)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDeviceName)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enIP)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enGateway)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enNetmask)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity0)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity4)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits0)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits4)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits0)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits4)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enSerialNumber)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enWatchdogFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDebugMode)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enUDPDebugIP)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enUDPDebugPort)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enLwipDebugFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enLwipDebugTimeout)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataDebugFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enIOModeDebugFlag)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enLED0Mode)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enLED1Mode)) {}

  else if (IsRoutingStatusContent(p)) {
    GetRouingStatusContent(pcb,p,addr,port,broadcast);
  }

  else { // TODO
    WARNING("unknown command\n");
  }
}
