/*------------------------------------------------------------------------------
broadcast_select.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "../kernel/wrappers.h"
#include "udp_pop.h"
#include "udp_in_common.h"
#include "udp_out.h"
#include "udp_out_common.h"
#include "broadcast_select.h"



bool                    fBroadcastSelect;

static uchar            mbBuff6[6];



static bool PopBuff6(struct pbuf *p, const uchar ibStart)
{
  uchar *pb = p->payload;

  uchar j = 0;
  uchar b = 0;

  uint i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '.')
    {
      if (j > 5)
      {
        WARNING("PopBuff6[%u]: wrong points number %u\n", i, j);
        return false;
      }
      else
      {
        mbBuff6[j] = b;
        j++;
        b = 0;
      }
    }
    else if (pb[i] == '|')
    {
      mbBuff6[j] = b;
      return true;
    }
    else
    {
      uchar2 b2 = DecodeChar(pb[i],10);
      if (InvalidChar2(b2))
      {
        WARNING("PopBuff6[%u]: wrong char\n", i);
        return false;
      }

      b = b*10 + b2.b;
    }
  }

  WARNING("PopBuff6[%u]: wrong length \n", i, p->len);
  return false;
}


static bool GetBroadcastSelect(void)
{
  uchar i;
  for (i=0; i<6; i++)
  {
    if (mbMAC[i] != mbBuff6[i])
      return false;
  }

  return true;
}


void OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast)
{
  if (broadcast != 0) {
    if (IsCmd(p,"W|")) {
      fBroadcastSelect = true;
      CONSOLE("broadcast select: yes, by default\n");
    } else {
      if (PopBuff6(p, 1)) {
        fBroadcastSelect = GetBroadcastSelect();
        if (fBroadcastSelect) {
          CONSOLE("broadcast select: yes\n");
          OutStringZ(pcb,p,addr,port,broadcast,"");
        } else {
          CONSOLE("broadcast select: no\n");
        }
      } else {
        WARNING("broadcast select: wrong MAC\n");
      }
    }
  } else {
    WARNING("broadcast select: wrong mode\n");
  }
}
