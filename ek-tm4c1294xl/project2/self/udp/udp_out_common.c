/*------------------------------------------------------------------------------
udp_out_common.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/wrappers.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_out_common.h"



err_t OutStringZ(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const char *pcsz)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushStringZ(pcsz);
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutBuff(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const buff bf)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushBuff(bf);
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutCharDec(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const uchar b)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushCharDec(b);
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutIntDec(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const uint w)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushIntDec(w);
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutIP(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const ulong dw)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushIP(dw);
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}
