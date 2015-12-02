/*------------------------------------------------------------------------------
UDP_PUSH.C


------------------------------------------------------------------------------*/

#include <string.h>
#include "../main.h"
#include "udp_push.h"

extern int usprintf(char * restrict s, const char * restrict format, ...);



static uchar            *pbPush;
static uchar            ibPush;



err_t InitPush(struct pbuf **pp, uchar bSize)
{
  //
  // The incoming pbuf is no longer needed, so free it.
  //
  pbuf_free(*pp);

  *pp = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (pp == NULL) return ERR_MEM;

  pbPush = (*pp)->payload;
  ibPush = 0;

  return ERR_OK;
}


void PushChar(uchar b)
{
  pbPush[ibPush++] = b;
}


void PushIntLtl(uint w)
{
  PushChar(w % 0x100);
  PushChar(w / 0x100);
}


void PushLongLtl(ulong dw)
{
  PushIntLtl(dw % 0x10000);
  PushIntLtl(dw / 0x10000);
}


void PushString(const char *sz)
{
  while (*sz)
  {
    PushChar(*sz++);
  }
}


uchar   PushIntHex(uint w)
{
static char mb[6*2];

  memset(&mb, 0, sizeof(mb));
  uchar n = usprintf(mb, "%X" ,w);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mb[i]);
  }

  return n;
}


uchar   PushCharDec(uchar b)
{
static char mb[4*2];

  memset(&mb, 0, sizeof(mb));
  uchar n = usprintf(mb, "%u" ,b);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mb[i]);
  }

  return n;
}


void PushIP_String(ulong dw)
{
  combo32 cb;
  cb.dwBuff = dw;

  PushCharDec(cb.mpbBuff[3]);
  PushChar('.');
  PushCharDec(cb.mpbBuff[2]);
  PushChar('.');
  PushCharDec(cb.mpbBuff[1]);
  PushChar('.');
  PushCharDec(cb.mpbBuff[0]);
}


void PushSuffix(uint w)
{
  PushChar('|');
  PushIntHex(w);
}


void PushMAC(uchar *pbMAC)
{
  PushChar(pbMAC[0]);
  PushChar(pbMAC[1]);
  PushChar(pbMAC[2]);
  PushChar(pbMAC[3]);
  PushChar(pbMAC[4]);
  PushChar(pbMAC[5]);
}


uchar GetPushSize(void)
{
  return ibPush;
}


// TODO test overflow
