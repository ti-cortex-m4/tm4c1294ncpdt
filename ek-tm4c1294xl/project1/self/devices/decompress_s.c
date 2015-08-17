/*------------------------------------------------------------------------------
DECOMPRESS_S.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_digitals.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "decompress_s.h"



#ifndef SKIP_S

uchar   RepackS_0xDB(uchar  bCode)
{
uchar   i;

  for (i=1; i<=IndexInBuff()-2; i++)
    if ((GetInBuff(i) == 0xDB) && (GetInBuff(i+1) == bCode)) return i;

  return 0;
}


void    DecompressS(void)
{
uchar   i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (GetInBuff(i) == 0xC0) j++;
  if (j != 2) return;

  if ((GetInBuff(0) != 0xC0) || (GetInBuff(IndexInBuff()-1) != 0xC0))
    return;

  if ((GetInBuff(6) & 0xF0) != 0x50)
  {
    mpcwErrorLink[ibDig]++; 

    mpSerial[ibPort] = SER_BADLINK;
    return;
  }

  bool f = 1;
  while ((f == 1) && (IndexInBuff() > 11) && (IndexInBuff() != (GetInBuff(6) & 0x0F) + 11))
  {
    f = 0;

    j = RepackS_0xDB(0xDD);
    if (j != 0)
    {
      SetInBuff(j, 0xDB);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, GetInBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }

    j = RepackS_0xDB(0xDC);
    if (j != 0)
    {
      SetInBuff(j, 0xC0);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, GetInBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }
  }

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}



uchar   CheckS(void) 
{
uint    i;

  if (GetInBuff(0) != 0xC0) return 1;
  if (GetInBuff(IndexInBuff()-1) != 0xC0) return 2;

  if (GetInBuff(1) != 0x48) return 3;

  i = mpdwAddress1[diCurr.bAddress-1] % 0x10000;
  if (GetInBuff(4) != (i % 0x100)) return 4;
  if (GetInBuff(5) != (i / 0x100)) return 5;

  i = wPrivate;
  if (GetInBuff(2) != (i % 0x100)) return 6;
  if (GetInBuff(3) != (i / 0x100)) return 7;

  MakeCRC9InBuff(1, IndexInBuff()-2); if (bCRC != 0) return 8;

  return 0;
}


uchar   ChecksumS(void) 
{
uchar   i;

  i = CheckS();
  if (i != 0)
  {
    Clear(); sprintf(szLo+1,"код ошибки: %bu",i); 
    Delay(500);
  }

  return i;
}

#endif
