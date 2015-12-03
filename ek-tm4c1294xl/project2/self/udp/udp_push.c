/*------------------------------------------------------------------------------
UDP_PUSH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_push.h"



#define PUSH_SIZE       0x200

extern int usprintf(char * restrict s, const char * restrict format, ...);



static uint             iwPush;
static uchar            mbPush[PUSH_SIZE];


void InitPush(void)
{
  iwPush = 0;
}


void PushChar(uchar b)
{
  mbPush[iwPush++] = b;
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


void PushIP(ulong dw)
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


void PushSfx(uint w)
{
  PushChar('|');
  PushIntHex(w);
}


void PushArray(uchar *pb, uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushChar(pb[i]);
  }
}


void PushArrayString(uchar *pb, uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushCharDec(pb[i]);
    if (i < bSize-1) PushChar('.');
  }
}


err_t UDPOutput2(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) // TODO
{
  pbuf_free(p);
  p = pbuf_alloc(PBUF_TRANSPORT, iwPush, PBUF_RAM);
  if (p == NULL) return ERR_MEM;

  memcpy(p->payload, mbPush, iwPush);

//  if (addr->addr == IPADDR_BROADCAST)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
//  else
//    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
  return ERR_OK;
}


// TODO test overflow
