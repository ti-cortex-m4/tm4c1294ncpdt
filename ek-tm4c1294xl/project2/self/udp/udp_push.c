/*------------------------------------------------------------------------------
udp_push,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_push_numbers.h"
#include "udp_push.h"



#define PUSH_SIZE       0x200

static uchar            mbPush[PUSH_SIZE];
static uint             iwPush;


uint                    cwErrUPDPushCharOverflow = 0;



void InitPush(void)
{
  iwPush = 0;
}


void PushChar(uchar b)
{
  if (iwPush < PUSH_SIZE)
    mbPush[iwPush++] = b;
  else
    cwErrUPDPushCharOverflow++;
}


void PushString(const char *sz)
{
  while (*sz)
  {
    PushChar(*sz++);
  }
}


void PushBuff(buff bf)
{
  while (bf.wSize-- > 0)
  {
    PushChar(*(bf.pbBuff++));
  }
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


void PushMAC(uchar *pb, uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushCharDec(pb[i]);
    if (i < bSize-1) PushChar('.');
  }
}


void PushSuffix(uint w)
{
  PushChar('|');
  PushIntHex(w);
}



err_t UDPOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  pbuf_free(p);

  p = pbuf_alloc(PBUF_TRANSPORT, iwPush, PBUF_RAM);
  if (p == NULL)
    return ERR_MEM;

  memcpy(p->payload, mbPush, iwPush);

  if (broadcast != 0)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port); // TODO check result
  else
    udp_sendto(pcb, p, addr, port); // TODO check result

  pbuf_free(p);
  return ERR_OK;
}
