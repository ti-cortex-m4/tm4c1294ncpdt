/*------------------------------------------------------------------------------
DECOMPRESS_V!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_profile.h"
#include "../kernel/crc_s.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
#include "../devices/devices.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "decompress_v.h"



#ifndef SKIP_V

static uchar RepackV(uchar  bCode1, uchar  bCode2)
{
  uchar i;
  for (i=1; i<=IndexInBuff()-2; i++)
    if ((GetInBuff(i) == bCode1) && (GetInBuff(i+1) == bCode2)) return i;

  return 0;
}


void    DecompressV(void)
{
uchar   i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (GetInBuff(i) == 0x55) j++;
  if (j != 2) return;

  if ((GetInBuff(0) != 0x73) || (GetInBuff(1) != 0x55) || (GetInBuff(IndexInBuff()-1) != 0x55))
    return;
/*
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

    j = RepackV(0xDB, 0xDD);
    if (j != 0)
    {
      SetInBuff(j, 0xDB);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, GetInBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }

    j = RepackV(0xDB, 0xDC);
    if (j != 0)
    {
      SetInBuff(j, 0xC0);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, GetInBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }
  }
*/
  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}



static uchar CheckV(void)
{
  if (GetInBuff(0) != 0x73) return 1;
  if (GetInBuff(1) != 0x55) return 2;
  if (GetInBuff(IndexInBuff()-1) != 0x55) return 3;

  if (GetInBuff(1) != 0x48) return 4;

  uint i = mpdwAddress1[diCurr.bAddress-1] % 0x10000;
  if (GetInBuff(4) != (i % 0x100)) return 5;
  if (GetInBuff(5) != (i / 0x100)) return 6;

  i = wPrivate;
  if (GetInBuff(2) != (i % 0x100)) return 7;
  if (GetInBuff(3) != (i / 0x100)) return 8;

  if (MakeCrcVInBuff(2, IndexInBuff()-2) != 0) return 9;

  return 0;
}


uchar   ChecksumV(void)
{
  uchar i = CheckV();
  if (i != 0)
  {
    Clear(); sprintf(szLo+1,"код ошибки: %u",i);
    Delay(500);
  }

  return i;
}

#endif
