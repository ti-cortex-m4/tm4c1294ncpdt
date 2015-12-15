/*------------------------------------------------------------------------------
UDP_POP.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_pop.h"



static uchar DecodeChar(uchar b, uchar bMax) // TODO
{
const static char mbCHARS[] = "0123456789abcdef";

  uchar i;
  for (i=0; i<bMax; i++)
  {
    if (mbCHARS[i] == b) return i;
  }

  return 0xFF;
}


err_t PopCharDec(struct pbuf *p, uchar *pb, uchar ibStart)
{
  uint w = 0;
  err_t err = PopIntDec(p, &w, ibStart);
  if (err != ERR_OK) return err;

  if (w >= 0x100) return ERR_ARG;
  *pb = w;

  return ERR_OK;
}

err_t PopIntDec(struct pbuf *p, uint *pw, uchar ibStart) // TODO
{
  uchar *pb = p->payload;

  *pw = 0;

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '|') return ERR_OK;

    char b = DecodeChar(pb[i],10);
    if (b == 0xFF) return ERR_VAL;

    *pw = *pw*10 + b;
  }

  return ERR_ARG;
}

err_t PopIntHex(struct pbuf *p, uint *pw, uchar ibStart) // TODO
{
  uchar *pb = p->payload;

  *pw = 0;

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '|') return ERR_OK;

    char b = DecodeChar(pb[i],0x10);
    if (b == 0xFF) return ERR_VAL;

    *pw = *pw*0x10 + b;
  }

  return ERR_ARG;
}


err_t PopIP(struct pbuf *p, ulong *pdw) // TODO
{
  uchar *pb = p->payload;

  combo32 cb;
  cb.dwBuff = 0;

  uchar y = 0;
  uchar x = 0;

  uchar i;
  for (i=3; i<p->len; i++)
  {
    if (pb[i] == '.')
    {
      if (y > 3) return ERR_VAL;
      else
      {
        cb.mpbBuff[3-y] = x;
        y++;
        x = 0;
      }
    }

    else if (pb[i] == '|')
    {
      cb.mpbBuff[3-y] = x;
      *pdw = cb.dwBuff;
      return ERR_OK;
    }

    else
    {
      char b = DecodeChar(pb[i],10);
      if (b == 0xFF) return ERR_VAL;

      x = x*10 + b;
    }
  }

  return ERR_ARG;
}


err_t PopString(struct pbuf *p, char *sz, uchar bSize) // TODO
{
  uchar *pb = p->payload;

  memset(sz, 0, bSize);

  uchar i;
  for (i=3; i<p->len; i++)
  {
    if (pb[i] == '|') return ERR_OK;

    char b = pb[i];
    if (b < 0x20) return ERR_VAL;

    if (i-3 >= bSize) return ERR_VAL;
    sz[i-3] = b;
  }

  return ERR_ARG;
}


err_t PopSfx(struct pbuf *p, uint *pw) // TODO
{
  uchar *pb = p->payload;

  bool f = false;
  *pw = 0;

  uchar i;
  for (i=0; i<p->len; i++)
  {
    if (f)
    {
      char b = DecodeChar(pb[i],0x10);
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
