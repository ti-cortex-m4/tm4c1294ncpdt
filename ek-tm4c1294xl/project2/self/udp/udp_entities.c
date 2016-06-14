/*------------------------------------------------------------------------------
udp_entities,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/entities.h"
//#include "../kernel/controls.h"
#include "../kernel/log.h"
//#include "../kernel/settings.h"
//#include "driverlib/sysctl.h"
//#include "../hardware/storage.h"
//#include "../uart/uart_log.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_out_common.h"
//#include "udp_out_controls.h"
//#include "routing_status.h"
//#include "test_watchdog.h"
#include "udp_entities.h"



static bool IsEnityCode(struct pbuf *p, uchar const bOperation, const char *szCode, uchar *pibStart)
{
//  const char *sz = szCode;

  uchar *pb = p->payload;
  uchar i = 0;

  if (i >= p->len) return false;
  if (pb[i++] != bOperation) return false;

  while (*szCode)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCode++) return false;
  }

//  WARNING("code: %c%s %u\n", bOperation, sz, i);

  *pibStart = i;
  return true;
}


static err_t PopEntity(struct pbuf *p, entity const *pen, uchar *pibStart)
{
  uchar ibStart = *pibStart;

  if (ibStart == 0xFF)
  {
    WARNING("index %u\n",ibStart);
    return -1;
  }
  else
  {
    switch (pen->eType)
    {
       case CHAR:
       {
         uchar2 b2 = PopCharDec(p, ibStart);
         if (!InvalidChar2(b2)) {
           (*(uchar *)pen->pbRam) = b2.b;
         }
//         WARNING("char[%u]=%u \n",ibStart,*(uchar *)pen->pbRAM);
         return b2.err;
       }
       case INT:
       {
         uint2 w2 = PopIntDec(p, ibStart);
         if (!InvalidInt2(w2)) {
           *(uint *)pen->pbRam = w2.w;
         }
//         WARNING("int[%u]=%u \n",ibStart,*(uint *)pen->pbRAM);
         return w2.err;
       }
       case IP:
       {
         ulong2 dw2 = PopIP(p, ibStart);
         if (!InvalidLong2(dw2)) {
           *(ulong *)pen->pbRam = dw2.dw;
         }
//         WARNING("long[%u]=%08x \n",ibStart,*(ulong *)pen->pbRAM);
         return dw2.err;
       }
       case STRING:
       {
         err_t err = PopBuff(p, (char *)pen->pbRam, NAME_SIZE, ibStart);
         return err;
       }
       default: ASSERT(false); return -1;
    }
  }
}


static err_t SetEntity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, entity const *pen, uchar *pibStart)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  err_t err = PopEntity(p, pen, pibStart);
  if (err != ERR_OK) return err;

  err = SaveEntity(pen);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}


bool IsEnity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast, entity const *pen) // TODO check errors
{
  uchar ibStart = 0xFF;
  if (IsEnityCode(p, 'G', pen->szCode, &ibStart))
  {
    switch (pen->eType)
    {
      case CHAR: OutCharDec(pcb,p,addr,port,broadcast,*(uchar *)pen->pbRam); break;
      case INT: OutIntDec(pcb,p,addr,port,broadcast,*(uint *)pen->pbRam); break;
      case IP: OutIP(pcb,p,addr,port,broadcast,*(ulong *)pen->pbRam); break;
      case STRING: OutString(pcb,p,addr,port,broadcast,(const char *)pen->pbRam); break;
      default: ASSERT(false); break;
    }

    return true;
  }
  else if (IsEnityCode(p, 'S', pen->szCode, &ibStart))
  {
    SetEntity(pcb,p,addr,port,broadcast,pen,&ibStart);
    return true;
  }
  else
  {
    return false;
  }
}
