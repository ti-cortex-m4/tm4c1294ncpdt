/*------------------------------------------------------------------------------
dlms_addresses.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "dlms_addresses.h"



#define DLMS_SERVER_ADDRESS_SIZE_4



uchar   GetDlmsAddressesSize(void)
{
#ifdef DLMS_SERVER_ADDRESS_SIZE_4
  return 4+1;
#else
  return 1+1;
#endif
}



void    PushDlmsAddresses(void)
{
#ifdef DLMS_SERVER_ADDRESS_SIZE_4
  PushChar(0x00);
  PushChar(0x02);

  uint wAddr = 1230; // TODO add real server address

  uchar bHi = wAddr / 0x100;
  uchar bLo = wAddr % 0x100;

  bHi = (bHi << 2) & 0xFC;
  if (bLo & 0x80) bHi |= 0x02;
  bLo = (bLo << 1) | 0x01;

  PushChar(bHi % 0x100);
  PushChar(bLo % 0x100);

  PushChar((bLogical << 1) + 0x01);
#else
  PushChar(0x03);
  PushChar(0x03);
#endif
}
