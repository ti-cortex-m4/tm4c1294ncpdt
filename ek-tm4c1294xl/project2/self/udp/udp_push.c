/*------------------------------------------------------------------------------
udp_push.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_push_numbers.h"
#include "udp_push.h"



uchar                   mbUDPPush[UDP_PUSH_SIZE];
uint                    iwUDPPush;


uint                    cwErrUPDPushCharOverflow = 0;



void InitPush(void)
{
  iwUDPPush = 0;
}


void PushChar(const uchar b)
{
  if (iwUDPPush < UDP_PUSH_SIZE)
    mbUDPPush[iwUDPPush++] = b;
  else
    cwErrUPDPushCharOverflow++;
}


void PushStringZ(const char *pcsz)
{
  while (*pcsz)
  {
    PushChar(*pcsz++);
  }
}


void PushBuff(buff bf) // TODO const
{
  uint i;
  for (i=0; i<bf.wSize; i++)
  {
    PushChar(*(bf.pbBuff++));
  }
}



void PushIP(const ulong dw)
{
  combo32 cm;
  cm.dw = dw;

  PushCharDec(cm.mb4[3]);
  PushChar('.');
  PushCharDec(cm.mb4[2]);
  PushChar('.');
  PushCharDec(cm.mb4[1]);
  PushChar('.');
  PushCharDec(cm.mb4[0]);
}


void PushMAC(const uchar *pb, const uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushCharDec(pb[i]);

    if (i < bSize-1)
      PushChar('.');
  }
}


void PushSfx(const uint w)
{
  PushChar('|');
  PushIntHex(w);
}
