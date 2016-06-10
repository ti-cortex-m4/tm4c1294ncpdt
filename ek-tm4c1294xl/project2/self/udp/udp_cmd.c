/*------------------------------------------------------------------------------
udp_cmd,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_cmd.h"



err_t CmdString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *sz)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushString(sz);
  PushSfx(wSfx.w);

  return PushOut(pcb,p,addr,port,broadcast);
}


err_t CmdBuff(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, buff bf)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushBuff(bf);
  PushSfx(wSfx.w);

  return PushOut(pcb,p,addr,port,broadcast);
}


err_t CmdIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, ulong dw)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushIP(dw);
  PushSfx(wSfx.w);

  return PushOut(pcb,p,addr,port,broadcast);
}

err_t CmdCharDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, uchar b)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushCharDec(b);
  PushSfx(wSfx.w);

  return PushOut(pcb,p,addr,port,broadcast);
}

err_t CmdIntDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, uint w)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushIntDec(w);
  PushSfx(wSfx.w);

  return PushOut(pcb,p,addr,port,broadcast);
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
