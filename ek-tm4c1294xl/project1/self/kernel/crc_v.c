/*------------------------------------------------------------------------------
CRC_V.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "crc_v.h"



uchar   MakeCrcV(uchar  *pbData, uint  wSize)
{
  uchar bCrc = 0;

  while (wSize-- > 0)
  {
    uchar b = *(pbData++);

    uchar i;
    for (i=0; i<8; i++)
    {
      if (((bCrc ^ b) & 0x80) == 0)
        bCrc <<= 1;
      else
        bCrc = (bCrc << 1) ^ 0xA9;

      b <<= 1;
    }
  }

  return bCrc;
}
