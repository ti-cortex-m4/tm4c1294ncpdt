/*------------------------------------------------------------------------------
CRC_ELS.C

 x^16 + x^15 + x^2 + 1
------------------------------------------------------------------------------*/

#include "../main.h"
#include "crc_els.h"



void    MakeCRC_Els(uchar  *pbData, uint  wSize)
{
  wCRC = 0;
  while (wSize-- > 0)
  {
     uint i = *(pbData++) ^ wCRC;
     wCRC = wCRC >> 8;

     if (i & 0x01) wCRC = wCRC ^ 0xC0C1;
     if (i & 0x02) wCRC = wCRC ^ 0xC181;
     if (i & 0x04) wCRC = wCRC ^ 0xC301;
     if (i & 0x08) wCRC = wCRC ^ 0xC601;
     if (i & 0x10) wCRC = wCRC ^ 0xCC01;
     if (i & 0x20) wCRC = wCRC ^ 0xD801;
     if (i & 0x40) wCRC = wCRC ^ 0xF001;
     if (i & 0x80) wCRC = wCRC ^ 0xA001;
  }
}
