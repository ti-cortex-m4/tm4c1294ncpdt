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



uchar                   mbT[6];
bool                    fBroadcastSelect;



static bool PopMAC(struct pbuf *p, const uchar ibStart)
{
  uchar *pb = p->payload;

  combo32 cb;
  cb.dw = 0;

  uchar j = 0;
  uchar b = 0;

  uint i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '.')
    {
      if (j > 3)
      {
        WARNING("PopIP[%u]: wrong points number %u\n", i, j);
        return GetLong2Error();
      }
      else
      {
        cb.mb4[3-j] = b;
        j++;
        b = 0;
      }
    }
    else if (pb[i] == '|')
    {
      cb.mb4[3-j] = b;
      return GetLong2Success(cb.dw);
    }
    else
    {
      uchar2 b2 = DecodeChar(pb[i],10);
      if (InvalidChar2(b2))
      {
        WARNING("PopIP[%u]: wrong char\n", i);
        return GetLong2Error();
      }

      b = b*10 + b2.b;
    }
  }

  WARNING("PopIP[%u]: wrong length \n", i, p->len);
  return GetLong2Error();
}



err_t OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  if (broadcast == 0)
  {
    OutStringZ(pcb,p,addr,port,broadcast,"");
  }
  else
  {
    if (IsCmd(p,"W|"))
      fBroadcastSelect = true;
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
