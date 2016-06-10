/*------------------------------------------------------------------------------
UDP_POP,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/wrappers.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"



static uchar2 DecodeChar(uchar b, uchar bRadix)
{
const static char mbCHARS[] = "0123456789abcdef";

  ASSERT((bRadix == 10) || (bRadix == 16));

  uchar i;
  for (i=0; i<bRadix; i++)
  {
    if (mbCHARS[i] == b)
      return GetChar2(i, ERR_OK);
  }

  CONSOLE("WARNING bad char %02X of radix %u\n", b, bRadix);
  return GetChar2Error();
}


uint2 PopInt(struct pbuf *p, uchar ibStart, uchar bRadix, uchar cBorder)
{
  uchar *pb = p->payload;

  uint w = 0;

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == cBorder)
      return GetInt2(w, ERR_OK);

    uchar2 b2 = DecodeChar(pb[i],bRadix);
    if (InvalidChar2(b2)) {
      WARNING("WARNING bad integer of radix %u with border @c\n",bRadix,cBorder);
      return GetInt2Error();
    }

    w = w*bRadix + b2.b;
  }

  WARNING("WARNING PopInt #2\n");
  return GetInt2Error();
}


uint2 PopIntDec(struct pbuf *p, const uchar ibStart)
{
  return PopInt(p, ibStart, 10, '|');
}

uint2 PopIntHex(struct pbuf *p, const uchar ibStart)
{
  return PopInt(p, ibStart, 0x10, '|');
}


static uchar2 PopChar(struct pbuf *p, uchar ibStart, uchar bRadix, uchar cBorder)
{
  uint2 w2 = PopInt(p, ibStart, bRadix, cBorder);
  if (InvalidInt2(w2))
    return GetChar2Error();

  if (w2.w >= 0x100) {
    WARNING("WARNING char overflow\n");
    return GetChar2Error();
  }

  return GetChar2(w2.w, ERR_OK);
}

uchar2 PopCharDec(struct pbuf *p, const uchar ibStart)
{
  return PopChar(p, ibStart, 10, '|');
}


ulong2 PopIP(struct pbuf *p, const uchar ibStart) // TODO
{
  uchar *pb = p->payload;

  combo32 cb;
  cb.dwBuff = 0;

  uchar y = 0;
  uchar x = 0;

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '.')
    {
      if (y > 3) { WARNING("WARNING PopIP #1\n"); return GetLong2Error(); }
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
      return GetLong2(cb.dwBuff, ERR_OK);
    }

    else
    {
      uchar2 b2 = DecodeChar(pb[i],10);
      if (InvalidChar2(b2)) { WARNING("WARNING PopIP #2\n"); return GetLong2Error(); }

      x = x*10 + b2.b;
    }
  }

  WARNING("WARNING PopIP #3\n");
  return GetLong2Error();
}


err_t PopString(struct pbuf *p, char *sz, const uchar bSize, const uchar ibStart) // TODO
{
  uchar *pb = p->payload;

  memset(sz, 0, bSize);

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '|') return ERR_OK;

    char b = pb[i];
    if (b < 0x20) { WARNING("WARNING PopString #1\n"); return ERR_VAL; }

    if (i-ibStart >= bSize) { WARNING("WARNING PopString #2\n"); return ERR_VAL; }
    sz[i-ibStart] = b;
  }

  WARNING("WARNING PopString #3\n");
  return ERR_ARG;
}


uint2 PopSfx(struct pbuf *p)
{
  uchar *pb = p->payload;

  bool f = false;
  uint w = 0;

  uchar i;
  for (i=0; i<p->len; i++)
  {
    if (f)
    {
      uchar2 b2 = DecodeChar(pb[i],0x10);
      if (InvalidChar2(b2)) {
        WARNING("WARNING PopSfx #1\n");
        return GetInt2Error();
      }

     w = w*0x10 + b2.b;
    }
    else
    {
      if (pb[i] == '|') f = true;
    }
  }

  if (f)
  {
    return GetInt2(w, ERR_OK);
  }
  else
  {
    CONSOLE("WARNING PopSfx #2\n");
    return GetInt2Error();
  }
}
