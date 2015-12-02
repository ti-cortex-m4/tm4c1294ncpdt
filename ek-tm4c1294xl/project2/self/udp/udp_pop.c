/*------------------------------------------------------------------------------
UDP_POP.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_pop.h"



static uchar DecodeChar(uchar b)
{
const static char mbCHARS[] = "0123456789abcdef";

  uchar i;
  for (i=0; i<16; i++)
  {
    if (mbCHARS[i] == b) return i;
  }

  return 0xFF;
}


err_t PopArgument(struct pbuf *p, uint *pw)
{
  uchar *pb = p->payload;

  *pw = 0;

  uchar i;
  for (i=2; i<p->len; i++)
  {
    if (pb[i] == '|') return ERR_OK;

    char b = DecodeChar(pb[i]);
    if (b == 0xFF) return ERR_VAL;

    *pw = *pw*0x10 + b;
  }

  return ERR_ARG;
}


err_t PopSuffix(struct pbuf *p, uint *pw)
{
  uchar *pb = p->payload;

  bool f = false;
  *pw = 0;

  uchar i;
  for (i=0; i<p->len; i++)
  {
    if (f)
    {
      char b = DecodeChar(pb[i]);
      if (b == 0xFF) return ERR_VAL;

     *pw = *pw*0x10 + b;
    }
    else
    {
      if (pb[i] == '|') f = true;
    }
  }

  return (f) ? ERR_OK : ERR_ARG;
}
