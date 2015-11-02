/*------------------------------------------------------------------------------
UDP_OUTPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"



static struct pbuf      *p;
static uchar            *pbOut;
static uchar            ibOut;

static uchar            pbMAC[6];



void SetMAC(uchar *_pbMAC)
{
  pbMAC[0] = _pbMAC[0];
  pbMAC[1] = _pbMAC[1];
  pbMAC[2] = _pbMAC[2];
  pbMAC[3] = _pbMAC[3];
  pbMAC[4] = _pbMAC[4];
  pbMAC[5] = _pbMAC[5];
}



static void InitPush(uchar bSize)
{
  p = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (p == NULL) return;

  pbOut = p->payload;
  ibOut = 0;
}


static void PushChar(uchar b)
{
  pbOut[ibOut++] = b;
}


static void PushCharDec(uchar b)
{
  PushChar('0' + b / 100);
  PushChar('0' + (b % 100) / 10);
  PushChar('0' + b % 10);
}


static void PushMAC(uchar *pbMAC)
{
  PushCharDec(pbMAC[0]); PushChar('.');
  PushCharDec(pbMAC[1]); PushChar('.');
  PushCharDec(pbMAC[2]); PushChar('.');
  PushCharDec(pbMAC[3]); PushChar('.');
  PushCharDec(pbMAC[4]); PushChar('.');
  PushCharDec(pbMAC[5]);
}


static void UDPOutput(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  if (true)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
  else
    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
}



void UDPOutputX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  InitPush(5);
  PushChar('A');
  PushMAC(pbMAC);
  UDPOutput(pcb, p, addr, port);
}
