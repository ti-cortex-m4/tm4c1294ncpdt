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
    if (i >= p->len)
      return false;

    if (pb[i++] != *szCmd++)
      return false;
  }

  return true;
}


uchar2 GetCmdIndex(struct pbuf *p, const char *szCmd)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (*szCmd)
  {
    if (i >= p->len)
      return GetChar2Error();

    if (pb[i++] != *szCmd++)
      return GetChar2Error();
  }

  return GetChar2Success(i);
}


uchar2 GetBorderIndex(struct pbuf *p, uchar bBorder)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (true)
  {
    if (i >= p->len)
    {
      return GetChar2Error();
    }

    if (pb[i++] == bBorder)
    {
      return GetChar2Success(i);
    }
  }
}
