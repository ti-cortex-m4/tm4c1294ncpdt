/*------------------------------------------------------------------------------
udp_in.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/restart.h"
#include "../kernel/controls.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "echo.h"
#include "buzz.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_in_common.h"
#include "udp_out_common.h"
#include "udp_out_controls.h"
#include "udp_entities.h"
#include "routing_status.h"
#include "test_watchdog.h"
#include "broadcast_select.h"
#include "udp_in.h"



void    UDPInput(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port, u8_t broadcast)
{
//  CONSOLE("broadcast: %d\n", broadcast);

  if (IsCmd(p,"X")) {
    OutEcho(pcb,p,addr,port,broadcast);
    return;
  } else if (IsCmd(p,"W")) {
    OutBroadcastSelect(pcb,p,addr,port,broadcast);
    return;
  } else if (IsCmd(p,"V")) {
    OutStringZ(pcb,p,addr,port,broadcast,"{ds1.0}");
    return;
  }

  if (fBroadcastSelect != true) {
    pbuf_free(p);
    return;
  }

  if (IsCmd(p,"E")) {
    Restart();
  } else if (IsCmd(p,"L")) {
    OutStringZ(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"I")) {
    ResetSettings();
    OutStringZ(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"O")) {
    OutStringZ(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"H")) {
    OutStringZ(pcb,p,addr,port,broadcast,"1A");
  } else if (IsCmd(p,"CS")) {
    OutIntDec(pcb,p,addr,port,broadcast,wControlsSize);
  } else if (IsCmd(p,"FS")) {
    OutControls(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    OutStringZ(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    OutStringZ(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"B")) {
    OutBuzz(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"watchdog")) {
    TestWatchdog(pcb,p,addr,port,broadcast);
  } else if (IsSomeEnity(pcb,p,addr,port,broadcast)) {
    //
  } else if (IsRoutingStatusSize(p)) {
    GetRoutingStatusSize(pcb,p,addr,port,broadcast);
  } else if (IsRoutingStatusContent(p)) {
    GetRoutingStatusContent(pcb,p,addr,port,broadcast);
  } else {
    WARNING("UDPInput: unknown command\n");
  }
}
