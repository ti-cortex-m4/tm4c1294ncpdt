/*------------------------------------------------------------------------------
udp_pop.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/wrappers.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"



uchar2 DecodeChar(const uchar b, const uchar bRadix)
{
const static char mbCHARS[] = "0123456789abcdef";

  ASSERT((bRadix == 10) || (bRadix == 16));

  uchar i;
  for (i=0; i<bRadix; i++)
  {
    if (mbCHARS[i] == b)
      return GetChar2Success(i);
  }

  WARNING("DecodeChar: wrong char %02X for radix %u\n", b, bRadix);
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
      WARNING("PopInt[%u]: wrong integer for radix %u with border @c\n", i, bRadix, cBorder);
      return GetInt2Error();
    }

    w = w*bRadix + b2.b;
  }

  WARNING("PopInt[%u]: wrong length, \n", i, p->len);
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
    WARNING("PopChar: wrong integer\n");
    return GetChar2Error();
  }

  if (w2.w >= 0x100) {
    WARNING("PopChar: char overflow %u\n", w2.w);
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


err_t PopBuff(struct pbuf *p, char *mpBuff, const uchar bSize, const uchar ibStart)
{
  uchar *pb = p->payload;

  memset(mpBuff, 0, bSize);

  uint i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '|')
      return ERR_OK;

    char b = pb[i];
    if (b < 0x20)
    {
      WARNING("PopBuff[%u]: wrong char %02X\n", i, b);
      return GetError();
    }

    if (i-ibStart >= bSize)
    {
      WARNING("PopBuff[%u]: wrong size %u %u\n", i, i-ibStart, bSize);
      return GetError();
    }

    mpBuff[i-ibStart] = b;
  }

  WARNING("PopBuff[%u]: wrong length \n", i, p->len);
  return GetError();
}


uint2 PopSfx(struct pbuf *p)
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
        WARNING("PopSuffix[%u]: wrong char\n", i);
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
    WARNING("PopSuffix[%u]: not found '|'\n", i);
    return GetInt2Error();
  }
}
