/*------------------------------------------------------------------------------
udp_pop,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/wrappers.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"



static uchar2 DecodeChar(const uchar b, const uchar bRadix)
{
const static char mbCHARS[] = "0123456789abcdef";

  ASSERT((bRadix == 10) || (bRadix == 16));

  uchar i;
  for (i=0; i<bRadix; i++)
  {
    if (mbCHARS[i] == b)
      return GetChar2Success(i);
  }

  WARNING("DecodeChar failed: wrong char %02X for radix %u\n", b, bRadix);
  return GetChar2Error();
}



uint2 PopInt(struct pbuf *p, const uchar ibStart, const uchar bRadix, const uchar cBorder)
{
  uchar *pb = p->payload;

  uint w = 0;

  uint i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == cBorder)
      return GetInt2Success(w);

    uchar2 b2 = DecodeChar(pb[i], bRadix);
    if (InvalidChar2(b2))
    {
      WARNING("PopInt failed: wrong integer for radix %u with border @c, position %u\n", bRadix, cBorder, i);
      return GetInt2Error();
    }

    w = w*bRadix + b2.b;
  }

  WARNING("PopInt failed: cycle, position %u\n", i);
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



uchar2 PopChar(struct pbuf *p, const uchar ibStart, const uchar bRadix, const uchar cBorder)
{
  uint2 w2 = PopInt(p, ibStart, bRadix, cBorder);
  if (InvalidInt2(w2))
  {
    WARNING("PopChar failed\n");
    return GetChar2Error();
  }

  if (w2.w >= 0x100) {
    WARNING("PopChar failed: char overflow %u\n", w2.w);
    return GetChar2Error();
  }

  return GetChar2Success(w2.w);
}


uchar2 PopCharDec(struct pbuf *p, const uchar ibStart)
{
  return PopChar(p, ibStart, 10, '|');
}



ulong2 PopIP(struct pbuf *p, const uchar ibStart)
{
  uchar *pb = p->payload;

  combo32 cb;
  cb.dwBuff = 0;

  uchar y = 0;
  uchar x = 0;

  uint i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '.')
    {
      if (y > 3)
      {
        WARNING("PopIP failed: points, position %u\n", i);
        return GetLong2Error();
      }
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
      return GetLong2Success(cb.dwBuff);
    }
    else
    {
      uchar2 b2 = DecodeChar(pb[i],10);
      if (InvalidChar2(b2))
      {
        WARNING("PopIP failed: char decoding, position %u\n", i);
        return GetLong2Error();
      }

      x = x*10 + b2.b;
    }
  }

  WARNING("PopIP failed: cycle, position %u\n",i );
  return GetLong2Error();
}



err_t PopString(struct pbuf *p, char *szString, const uchar bSize, const uchar ibStart)
{
  uchar *pb = p->payload;

  memset(szString, 0, bSize);

  uint i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '|')
      return ERR_OK;

    char b = pb[i];
    if (b < 0x20)
    {
      WARNING("PopString failed: wrong char %02X, position %u\n", b, i);
      return ERR_VAL;
    }

    if (i-ibStart >= bSize)
    {
      WARNING("PopString: wrong size, position %u\n",i );
      return ERR_VAL;
    }

    szString[i-ibStart] = b;
  }

  WARNING("PopString failed: cycle, position %u\n", i);
  return ERR_ARG;
}



uint2 PopSuffix(struct pbuf *p)
{
  uchar *pb = p->payload;

  bool fStart = false;
  uint w = 0;

  uint i;
  for (i=0; i<p->len; i++)
  {
    if (fStart)
    {
      uchar2 b2 = DecodeChar(pb[i], 0x10);
      if (InvalidChar2(b2))
      {
        WARNING("PopSuffix failed: wrong char, position %u\n", i);
        return GetInt2Error();
      }

      w = w*0x10 + b2.b;
    }
    else
    {
      if (pb[i] == '|') fStart = true;
    }
  }

  if (fStart)
  {
    return GetInt2Success(w);
  }
  else
  {
    WARNING("PopSuffix failed: not found '|'\n");
    return GetInt2Error();
  }
}
