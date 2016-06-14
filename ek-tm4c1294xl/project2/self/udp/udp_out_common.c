/*------------------------------------------------------------------------------
udp_out_common,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_out_common.h"



err_t OutString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *pcsz)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushString(pcsz);
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutBuff(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, buff bf)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushBuff(bf);
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutCharDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uchar b)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushCharDec(b);
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutIntDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const uint w)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushIntDec(w);
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


err_t OutIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const ulong dw)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushIP(dw);
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}



bool IsCmd(struct pbuf *p, const char *szCmd)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (*szCmd)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCmd++) return false;
  }

  return true;
}


bool IsPrefix(struct pbuf *p, const char *szCode, uchar *pibStart) // TODO
{
  uchar *pb = p->payload;
  uchar i = 0;

  while (*szCode)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCode++) return false;
  }

  *pibStart = i;
  return true;
}


bool IsChar(struct pbuf *p, uchar bChar, uchar *pibStart) // TODO
{
  uchar *pb = p->payload;
  uchar i = 0;

  while (true)
  {
    if (i >= p->len) return false;
    if (pb[i++] == bChar)
    {
      *pibStart = i;
      return true;
    }
  }

//  return false;
}
