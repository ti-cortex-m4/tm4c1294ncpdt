/*------------------------------------------------------------------------------
hdlc_address.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "hdlc_address.h"



#define HDLC_ADDRESS_SIZE_4



uchar   GetHdlcAddressesSize(void)
{
#ifdef HDLC_ADDRESS_SIZE_4
  return 4+1;
#else
  return 1+1;
#endif
}



void    PushHdlcAddresses(void)
{
#ifdef HDLC_ADDRESS_SIZE_4
  PushChar(0x00);
  PushChar(0x02);

  uint wAddr = mpdwAddress1[diCurr.bAddress-1];

  uchar bHi = wAddr / 0x100;
  uchar bLo = wAddr % 0x100;

  bHi = (bHi << 2) & 0xFC;
  if (bLo & 0x80) bHi |= 0x02;
  bLo = (bLo << 1) | 0x01;

  PushChar(bHi);
  PushChar(bLo);

  PushChar((bLogical << 1) + 0x01);
#else
  PushChar(0x03);
  PushChar(0x03);
#endif
}



uchar   GetHdlcAddressesSize_Single(void)
{
  return 1+1;
}

void    PushHdlcAddresses_Single(void)
{
  PushChar(0x03);
  PushChar(0x03);
}
