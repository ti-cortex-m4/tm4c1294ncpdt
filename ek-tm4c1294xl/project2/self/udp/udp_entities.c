/*------------------------------------------------------------------------------
udp_entities.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/entities.h"
#include "../kernel/log.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_out_common.h"
#include "udp_entities.h"



static uchar2 IsEnityCode(struct pbuf *p, uchar const bOperation, const char *pcszCode)
{
  uchar *pb = p->payload;
  uchar i = 0;

  if (i >= p->len)
    return GetChar2Error();

  if (pb[i++] != bOperation)
    return GetChar2Error();

  while (*pcszCode)
  {
    if (i >= p->len)
      return GetChar2Error();

    if (pb[i++] != *pcszCode++)
      return GetChar2Error();
  }

  return GetChar2Success(i);
}



static err_t GetEntity(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const entity * const pen)
{
  switch (pen->eType)
  {
    case CHAR: return OutCharDec(pcb,p,addr,port,broadcast,*(uchar *)pen->pbRam);
    case INT: return OutIntDec(pcb,p,addr,port,broadcast,*(uint *)pen->pbRam);
    case IP: return OutIP(pcb,p,addr,port,broadcast,*(ulong *)pen->pbRam);
    case STRING: return OutStringZ(pcb,p,addr,port,broadcast,(const char *)pen->pbRam);
    default: ASSERT(false); return GetError();
  }
}


static err_t PopEntity(struct pbuf *p, const entity * const pen, const uchar ibStart)
{
  switch (pen->eType)
  {
    case CHAR:
    {
      uchar2 b2 = PopCharDec(p, ibStart);
      if (!InvalidChar2(b2)) {
        (*(uchar *)pen->pbRam) = b2.b;
      }
      return b2.err;
    }

    case INT:
    {
      uint2 w2 = PopIntDec(p, ibStart);
      if (!InvalidInt2(w2)) {
        *(uint *)pen->pbRam = w2.w;
      }
      return w2.err;
    }

    case IP:
    {
      ulong2 dw2 = PopIP(p, ibStart);
      if (!InvalidLong2(dw2)) {
        *(ulong *)pen->pbRam = dw2.dw;
      }
      return dw2.err;
    }

    case STRING:
    {
      return PopBuff(p, (char *)pen->pbRam, NAME_SIZE, ibStart);
    }

    default: ASSERT(false); return GetError();
  }
}


static err_t SetEntity(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const entity * const pen, const uchar ibStart)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  err_t err = PopEntity(p, pen, ibStart);
  if (err != ERR_OK) return err;

  if (SaveEntity(pen) != 0) return GetError();

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}



static bool IsEnity(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port, u8_t broadcast, const entity * const pen)
{
  uchar2 ibStart = IsEnityCode(p, 'G', pen->szCode);
  if (!InvalidChar2(ibStart))
  {
    GetEntity(pcb,p,addr,port,broadcast,pen);
    return true;
  }
  else
  {
    ibStart = IsEnityCode(p, 'S', pen->szCode);
    if (!InvalidChar2(ibStart))
    {
      SetEntity(pcb,p,addr,port,broadcast,pen,ibStart.b);
      return true;
    }
    else
    {
      return false;
    }
  }
}


bool IsSomeEnity(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port, u8_t broadcast)
{
  uchar e;
  for (e = 0; e < bEntitiesSize; e++)
  {
    if (IsEnity(pcb,p,addr,port,broadcast,mpenEntities[e]))
      return true;
  }

  return false;
}
