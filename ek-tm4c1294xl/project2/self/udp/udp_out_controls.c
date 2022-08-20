/*------------------------------------------------------------------------------
udp_out_controls.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/controls.h"
#include "../kernel/wrappers.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_out_controls.h"



err_t OutControls(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  uint2 w2 = PopIntDec(p, 2);
  if (InvalidInt2(w2)) return w2.err;
  uint wArg = w2.w;

  InitPush();

  if (wArg < wControlsSize)
    PushStringZ(*mppcszControls[wArg]);
  else
  {
    WARNING("OutControls: wrong index, must be %u < %u\n", wArg, wControlsSize);
  }

  PushChar(0x0D);
  PushChar(0x0A);
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}
