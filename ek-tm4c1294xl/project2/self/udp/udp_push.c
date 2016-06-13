/*------------------------------------------------------------------------------
udp_push,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "udp_push_numbers.h"
#include "udp_push.h"



#define PUSH_SIZE       0x200

static uchar            mbPush[PUSH_SIZE];
static uint             iwPush;


uint                    cwErrUPDPushCharOverflow = 0;
uint                    cwErrUPDPushAlloc = 0; // TODO
uint                    cwErrUPDPushSendUnicast = 0;
uint                    cwErrUPDPushSendBroadcast = 0;



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
  {
    ERROR("UDPOut.pbuf_alloc: NULL\n");
    cwErrUPDPushAlloc++;
    return ERR_MEM;
  }

  memcpy(p->payload, mbPush, iwPush);

  if (broadcast != 0)
  {
    err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
    if (err != ERR_OK)
    {
      ERROR("UDPOut.udp_sendto: err=%u", err);
      cwErrUPDPushSendBroadcast++;
    }
  }
  else
  {
    err_t err = udp_sendto(pcb, p, addr, port);
    if (err != ERR_OK)
    {
      ERROR("UDPOut.udp_sendto: err=%u", err);
      cwErrUPDPushSendUnicast++;
    }
  }

  pbuf_free(p);
  return ERR_OK;
}
