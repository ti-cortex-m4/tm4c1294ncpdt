/*------------------------------------------------------------------------------
dlms_addr.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "dlms_addr.h"


//#define ADDR_4


uchar   GetDlmsServerAddrSize(void)
{
#ifndef ADDR_4
  addr36 addr;
  addr.cBuff.mpbBuff[0] = 0x03;
  addr.cBuff.mpbBuff[1] = 0x03;
  addr.bSize = 1+1;
  return addr;
#else
  addr36 addr;
  addr.cBuff.mpbBuff[0] = 0x00;
  addr.cBuff.mpbBuff[1] = 0x02;

  uint wAddr = 1230;

  uchar b3 = wAddr / 0x100;
  uchar b4 = wAddr % 0x100;

  b3 = (b3 << 2) & 0xFC;
  if (b4 & 0x80) b3 |= 0x02;
  b4 = (b4 << 1) | 0x01;

  addr.cBuff.mpbBuff[2] = b3 % 0x100;
  addr.cBuff.mpbBuff[3] = b4 % 0x100;

  addr.bSize = 4+1;
  return addr;
#endif

}



void    PushDlmsServerAddr(void)
{
#ifndef ADDR_4
  PushChar(addr.cBuff.mpbBuff[0]);
  PushChar(addr.cBuff.mpbBuff[1]);
#else
  PushChar(addr.cBuff.mpbBuff[0]);
  PushChar(addr.cBuff.mpbBuff[1]);
  PushChar(addr.cBuff.mpbBuff[2]);
  PushChar(addr.cBuff.mpbBuff[3]);
  PushChar((bLogical << 1) + 0x01);
#endif
}
