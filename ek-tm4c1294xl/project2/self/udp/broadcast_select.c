/*------------------------------------------------------------------------------
broadcast_select.c


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../hardware/led.h"
//#include "../hardware/delay.h"
//#include "../kernel/wrappers.h"
//#include "udp_pop.h"
//#include "udp_out.h"
#include "broadcast_select.h"



bool                    fBroadcastSelect;



err_t OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  if (broadcast == 0)
  {
    OutStringZ(pcb,p,addr,port,broadcast,"");
  }
  else
  {
    if (IsCmd(p,"W|"))
      fBroadcastSelect = true
    else
    {
    }

  }

  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  Buzz();

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}

OutStringZ(pcb,p,addr,port,broadcast,"");
