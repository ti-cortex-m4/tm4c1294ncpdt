/*------------------------------------------------------------------------------
hdlc_address.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "hdlc_address.h"



uchar   GetHdlcAddressesSize0(uint wAddr)
{
  if (wAddr == 0) {
    return 1+1;
  } else if (wAddr <= 0x7F) {
    return 2+1;
  } else {
    return 4+1;
  }
}


uchar   GetHdlcAddressesSize(void)
{
  return  GetHdlcAddressesSize0(mpdwAddress1[diCurr.bAddress-1]);
}



void    PushHdlcAddresses0(uint wAddr)
{
  if (wAddr == 0) {
    PushChar(0x03);
  } else if (wAddr <= 0x7F) {
    PushChar(0x02);
  } else {
    PushChar(0x00);
    PushChar(0x02);
  }

  uchar bHi = wAddr / 0x100;
  uchar bLo = wAddr % 0x100;

  bHi = (bHi << 2) & 0xFC;
  if (bLo & 0x80) bHi |= 0x02;
  bLo = (bLo << 1) | 0x01;

  if (wAddr == 0) {
  } else if (wAddr <= 0x7F) {
    PushChar(bLo);
  } else {
    PushChar(bHi);
    PushChar(bLo);
  }

  PushChar((32 << 1) + 0x01); // client address: 32
}


void    PushHdlcAddresses(void)
{
  PushHdlcAddresses0(mpdwAddress1[diCurr.bAddress-1]);
}
