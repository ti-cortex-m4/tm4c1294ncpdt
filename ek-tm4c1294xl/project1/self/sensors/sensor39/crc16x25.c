/*------------------------------------------------------------------------------
crc16x25*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_serial0.h"
#include "../../memory/mem_serial1.h"
#include "../../memory/mem_serial2.h"
#include "../../memory/mem_serial3.h"
#include "../../isr/serial0.h"
#include "../../isr/serial1.h"
#include "../../isr/serial2.h"
#include "../../isr/serial3.h"
#include "../../serial/ports.h"
#include "crc16x25.h"



uint    MakeCRC16_X25(uchar  *pbData, uint  wSize)
{
 uint w = 0xFFFF;
 uchar i;

 while (wSize--)
 {
  w = w ^ (*pbData++);
  for (i = 0; i < 8; i++)
  {
   if (w & 1) { w = (w >> 1) ^ 0x8408; }
   else { w = w >> 1; }
  }
 }

 w ^= 0xFFFF;
 return w;
}



uint    MakeCRC16_X25OutBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  return MakeCRC16_X25(mpbOutBuff0 + bOffset, wSize);
    case 1:  return MakeCRC16_X25(mpbOutBuff1 + bOffset, wSize);
    case 2:  return MakeCRC16_X25(mpbOutBuff2 + bOffset, wSize);
    case 3:  return MakeCRC16_X25(mpbOutBuff3 + bOffset, wSize);
    default: ASSERT(false); return 0;
  }
}


uint    MakeCRC16_X25InBuff(uchar  bOffset, uint  wSize)
{
  switch (ibPort)
  {
    case 0:  return MakeCRC16_X25(mpbInBuff0 + bOffset, wSize);
    case 1:  return MakeCRC16_X25(mpbInBuff1 + bOffset, wSize);
    case 2:  return MakeCRC16_X25(mpbInBuff2 + bOffset, wSize);
    case 3:  return MakeCRC16_X25(mpbInBuff3 + bOffset, wSize);
    default: ASSERT(false); return 0;
  }
}
