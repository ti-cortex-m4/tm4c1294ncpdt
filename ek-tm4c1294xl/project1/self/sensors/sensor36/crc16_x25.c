/*------------------------------------------------------------------------------
crc16_x25.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "crc16_x25.h"



uint MakeCRC16_X25(uchar  *pbData, uint  wSize)
{
 uint Crc = 0xFFFF;
 uchar i;

 while (wSize--)
 {
  Crc = Crc ^ (*pbData++);
  for (i = 0; i < 8; i++)
  {
   if (Crc & 1) { Crc = (Crc >> 1) ^ 0x8408; }
   else { Crc = Crc >> 1; }
  }
 }

 Crc ^= 0xFFFF;
 bCRCLo = Crc >> 8;
 bCRCHi = Crc;

 return Crc;
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
