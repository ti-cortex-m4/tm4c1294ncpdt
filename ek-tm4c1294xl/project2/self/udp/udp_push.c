/*------------------------------------------------------------------------------
UDP_PUSH.C


------------------------------------------------------------------------------*/

#include <string.h>
#include "../main.h"
//#include "../settings.h"
#include "udp_push.h"



static uchar            *pbOut;
static uchar            ibOut;



err_t InitPush(struct pbuf **pp, uchar bSize)
{
  //
  // The incoming pbuf is no longer needed, so free it.
  //
  pbuf_free(*pp);

  *pp = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (pp == NULL) return ERR_MEM;

  pbOut = (*pp)->payload;
  ibOut = 0;

  return ERR_OK;
}


void PushChar(uchar b)
{
  pbOut[ibOut++] = b;
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


extern int usprintf(char * restrict s, const char * restrict format, ...);

uchar   PushIntHex(uint w)
{
static char mbT[6*2];

  memset(&mbT, 0, sizeof(mbT));
  uchar n = usprintf(mbT, "%X" ,w);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbT[i]);
  }

  return n;
}


uchar   PushCharDec(uchar b)
{
static char mbT[4*2];

  memset(&mbT, 0, sizeof(mbT));
  uchar n = usprintf(mbT, "%u" ,b);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mbT[i]);
  }

  return n;
}


void PushIPCtrl(ulong dw)
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


void PushCode(uint wCode)
{
  PushChar('|');
  PushIntHex(wCode);
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
  return ibOut;
}
