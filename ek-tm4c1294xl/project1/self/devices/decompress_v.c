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
#include "../serial/monitor.h"
#include "../devices/devices.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "decompress_v.h"



#ifndef SKIP_V

static uchar RepackV(uchar  bCode1, uchar  bCode2)
{
  uchar i;
  for (i=1; i<=IndexInBuff()-2; i++)
    if ((InBuff(i) == bCode1) && (InBuff(i+1) == bCode2)) return i;

  return 0;
}


void    DecompressV(void)
{
uchar   i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (InBuff(i) == 0x55) j++;
  if (j != 2) return;

  if ((InBuff(0) != 0x73) || (InBuff(1) != 0x55) || (InBuff(IndexInBuff()-1) != 0x55))
    return;

  MonitorIn();

  if (InBuff(12) != 0)
  {
    mpcwErrorLink[ibDig]++;

    mpSerial[ibPort] = SER_BADLINK;
    return;
  }

  bool f = 1;
  while ((f == 1) && (IndexInBuff() > 15) && (IndexInBuff() != (InBuff(2) & 0x1F) + 15))
  {
    if (UseMonitor())
    {
      MonitorString("\n Decompress");
      MonitorIn();
    }

    f = 0;

    j = RepackV(0x73, 0x11);
    if (j != 0)
    {
      SetInBuff(j, 0x55);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, InBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }

    j = RepackV(0x73, 0x22);
    if (j != 0)
    {
      SetInBuff(j, 0x73);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, InBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }
  }

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}



static uchar CheckV(void)
{
  if (InBuff(0) != 0x73) return 1;
  if (InBuff(1) != 0x55) return 2;

  if ((IndexInBuff() >= 15) && (IndexInBuff() != (InBuff(2) & 0x1F) + 15)) return 3;

  if (InBuff(3) != 0) return 4;

  if (InBuffIntLtl(4) != wPrivate) return 5;
  if (InBuffIntLtl(6) != (mpdwAddress1[diCurr.bAddress-1] % 0x10000)) return 6;

  if (InBuff(8) != OutBuff(8)) return 7;

  if (MakeCrcVInBuff(2, IndexInBuff()-3) != 0) return 8;
  if (InBuff(IndexInBuff()-1) != 0x55) return 9;

  return 0;
}


uchar   ChecksumV(void)
{
  uchar i = CheckV();
  if (i != 0)
  {
    Clear(); sprintf(szLo+1,"код ошибки: %u",i);
    DelayInf();
  }

  return i;
}

#endif
