/*------------------------------------------------------------------------------
UDP_POP,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"



static uchar DecodeChar(uchar b, uchar bRadix) // TODO
{
const static char mbCHARS[] = "0123456789abcdef";

  ASSERT((bRadix == 10) || (bRadix == 16));

  uchar i;
  for (i=0; i<bRadix; i++)
  {
    if (mbCHARS[i] == b) return i;
  }

  return 0xFF;
}


static err_t PopInt(struct pbuf *p, uint *pw, uchar ibStart, uchar bRadix) // TODO
{
  uchar *pb = p->payload;

  *pw = 0;

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == '|') return ERR_OK;

    char b = DecodeChar(pb[i],bRadix);
    if (b == 0xFF) { CONSOLE_UART("WARNING PopInt #1\n"); return ERR_VAL; }

    *pw = *pw*bRadix + b;
  }

  CONSOLE_UART("WARNING PopInt #2\n");
  return ERR_ARG;
}

err_t PopInt2(struct pbuf *p, uint *pw, uchar ibStart, uchar bRadix, uchar bChar) // TODO
{
  uchar *pb = p->payload;

  *pw = 0;

  uchar i;
  for (i=ibStart; i<p->len; i++)
  {
    if (pb[i] == bChar) return ERR_OK;

    char b = DecodeChar(pb[i],bRadix);
    if (b == 0xFF) { CONSOLE_UART("WARNING PopInt #1\n"); return ERR_VAL; }

    *pw = *pw*bRadix + b;
  }

  CONSOLE_UART("WARNING PopInt #2\n");
  return ERR_ARG;
}

err_t PopIntDec(struct pbuf *p, uint *pw, const uchar ibStart)
{
  return PopInt(p, pw, ibStart, 10);
}

err_t PopIntHex(struct pbuf *p, uint *pw, const uchar ibStart)
{
  return PopInt(p, pw, ibStart, 0x10);
}


static err_t PopChar(struct pbuf *p, uchar *pb, uchar ibStart, uchar bRadix)
{
  uint w = 0;
  err_t err = PopInt(p, &w, ibStart, bRadix);
  if (err != ERR_OK) return err;

  if (w >= 0x100) { CONSOLE_UART("WARNING PopChar #1\n"); return ERR_ARG; }
  *pb = w;

  return ERR_OK;
}

err_t PopCharDec(struct pbuf *p, uchar *pb, const uchar ibStart)
{
  return PopChar(p, pb, ibStart, 10);
}


err_t PopIP(struct pbuf *p, ulong *pdw, const uchar ibStart) // TODO
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
      if (y > 3) { CONSOLE_UART("WARNING PopIP #1\n"); return ERR_VAL; }
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
      if (b == 0xFF) { CONSOLE_UART("WARNING PopIP #2\n"); return ERR_VAL; }

      x = x*10 + b;
    }
  }

  CONSOLE_UART("WARNING PopIP #3\n");
  return ERR_ARG;
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
    if (b < 0x20) { CONSOLE_UART("WARNING PopString #1\n"); return ERR_VAL; }

    if (i-ibStart >= bSize) { CONSOLE_UART("WARNING PopString #2\n"); return ERR_VAL; }
    sz[i-ibStart] = b;
  }

  CONSOLE_UART("WARNING PopString #3\n");
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
      if (b == 0xFF) { CONSOLE_UART("WARNING PopSfx #1\n"); return ERR_VAL; }

     *pw = *pw*0x10 + b;
    }
    else
    {
      if (pb[i] == '|') f = true;
    }
  }

  if (f)
  {
    return ERR_OK;
  }
  else
  {
    CONSOLE_UART("WARNING PopSfx #2\n");
    return ERR_ARG;
  }
}
