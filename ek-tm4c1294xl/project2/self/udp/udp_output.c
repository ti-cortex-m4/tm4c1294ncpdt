/*------------------------------------------------------------------------------
UDP_OUTPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "udp_output.h"



static uchar            pbMAC[6];

static uchar            *pbOut;
static uchar            ibOut;



void SetMAC(uchar *pb)
{
  pbMAC[0] = pb[0];
  pbMAC[1] = pb[1];
  pbMAC[2] = pb[2];
  pbMAC[3] = pb[3];
  pbMAC[4] = pb[4];
  pbMAC[5] = pb[5];
}



static err_t InitPush(struct pbuf *p, uchar bSize)
{
  p = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (p == NULL) return ERR_MEM;

  pbOut = p->payload;
  ibOut = 0;

  return ERR_OK;
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
  if (addr->addr == IPADDR_BROADCAST)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
  else
    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
}



err_t UDPOutputX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  err_t err = InitPush(p, 1+23);
  if (err == ERR_MEM) return err;

  PushChar('A');
  PushMAC(pbMAC);

  UDPOutput(pcb, p, addr, port);

  return ERR_OK;
}
