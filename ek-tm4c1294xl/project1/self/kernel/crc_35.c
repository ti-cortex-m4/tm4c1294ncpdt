/*------------------------------------------------------------------------------
CRC_35.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "crc_35.h"



uchar   MakeCrc35(uchar  *pbData, uint  wSize)
{
  uint wCRC = 0;

  while (wSize-- > 0)
  {
    wCRC ^= *(pbData++) << 8;

    uchar i;
    for (i = 0; i < 8; i++)
    {
      if (wCRC & 0x8000)
      {
        wCRC <<= 1;
        wCRC ^= 0x8005;
      }
      else
      {
        wCRC <<= 1;
      }
    }
  }

  return wCRC;
}
