/*------------------------------------------------------------------------------
UDP_PUSH,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/ustdlib.h"
#include "udp_push.h"



#define PUSH_SIZE       0x200 // TODO check overflow


static uchar            mbPush[PUSH_SIZE];
static uint             iwPush;



void InitPush(void)
{
  iwPush = 0;
}


void PushChar(uchar b)
{
  mbPush[iwPush++] = b;
}


void PushString(const char *sz)
{
  while (*sz)
  {
    PushChar(*sz++);
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


void PushBuff(buff bf)
{
  while (bf.wSize-- > 0 > 0)
  {
    PushChar(*(bf.pbBuff++));
  }
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


uchar   PushIntDec(uint w)
{
static char mb[6*2];

  memset(&mb, 0, sizeof(mb));
  uchar n = usprintf(mb, "%u" ,w);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mb[i]);
  }

  return n;
}

uchar   PushIntHex(uint w)
{
static char mb[5*2];

  memset(&mb, 0, sizeof(mb));
  uchar n = usprintf(mb, "%X" ,w);

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


void PushSuffix(uint w)
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


err_t UDPPush(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) // TODO
{
  pbuf_free(p);
  p = pbuf_alloc(PBUF_TRANSPORT, iwPush, PBUF_RAM);
  if (p == NULL)
    return ERR_MEM;

  memcpy(p->payload, mbPush, iwPush);

  if (broadcast != 0)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
  else
    udp_sendto(pcb, p, addr, port); // TODO check result

  pbuf_free(p);
  return ERR_OK;
}
