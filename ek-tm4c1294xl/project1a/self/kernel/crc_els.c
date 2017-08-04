/*------------------------------------------------------------------------------
CRC_ELS!C

 x^16 + x^15 + x^2 + 1
------------------------------------------------------------------------------*/

#include "../main.h"
#include "crc_els.h"



uint                    wCrcEls;



void    MakeCrcEls(uchar  *pbData, uint  wSize)
{
  wCrcEls = 0;
  while (wSize-- > 0)
  {
     uint i = *(pbData++) ^ wCrcEls;
     wCrcEls = wCrcEls >> 8;

     if (i & 0x01) wCrcEls = wCrcEls ^ 0xC0C1;
     if (i & 0x02) wCrcEls = wCrcEls ^ 0xC181;
     if (i & 0x04) wCrcEls = wCrcEls ^ 0xC301;
     if (i & 0x08) wCrcEls = wCrcEls ^ 0xC601;
     if (i & 0x10) wCrcEls = wCrcEls ^ 0xCC01;
     if (i & 0x20) wCrcEls = wCrcEls ^ 0xD801;
     if (i & 0x40) wCrcEls = wCrcEls ^ 0xF001;
     if (i & 0x80) wCrcEls = wCrcEls ^ 0xA001;
  }
}
