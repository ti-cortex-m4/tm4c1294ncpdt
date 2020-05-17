/*------------------------------------------------------------------------------
UNPACK_S!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_profile.h"
#include "../../kernel/crc_s.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "unpack_s.h"



#ifndef SKIP_S

static uchar RepackS(uchar  bCode)
{
  uchar i;
  for (i=1; i<=IndexInBuff()-2; i++)
    if ((InBuff(i) == 0xDB) && (InBuff(i+1) == bCode)) return i;

  return 0;
}


void    DecompressS(void)
{
uchar   i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (InBuff(i) == 0xC0) j++;
  if (j != 2) return;

  if ((InBuff(0) != 0xC0) || (InBuff(IndexInBuff()-1) != 0xC0))
    return;

  MonitorIn();

  if ((InBuff(6) & 0xF0) != 0x50)
  {
    Clear(); sprintf(szLo+1,"ошибка: 24.1.%u",(InBuff(6) & 0xF0));
    DelayInf();

    mpcwErrorLink[ibDig]++;

    mpSerial[ibPort] = SER_BADLINK;
    return;
  }

  bool f = 1;
  while ((f == 1) && (IndexInBuff() > 11) && (IndexInBuff() != (InBuff(6) & 0x0F) + 11))
  {
    MonitorString("\n Unpack");
    MonitorIn();

    f = 0;

    j = RepackS(0xDD);
    if (j != 0)
    {
      SetInBuff(j, 0xDB);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, InBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }

    j = RepackS(0xDC);
    if (j != 0)
    {
      SetInBuff(j, 0xC0);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, InBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }
  }

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}



static uchar CheckS(void)
{
  if (InBuff(0) != 0xC0) return 1;
  if (InBuff(1) != 0x48) return 2;

  if (InBuffIntLtl(2) != wPrivate) return 3;
  if (InBuffIntLtl(4) != (mpdwAddress1[diCurr.bAddress-1] % 0x10000)) return 4;

  if ((InBuff(6) & 0xF0) != 0x50) return 5;
  if ((IndexInBuff() >= 11) && (IndexInBuff() != (InBuff(6) & 0x0F) + 11)) return 6;

  if (InBuff(7) != OutBuff(11)) return 7;
  if (InBuff(8) != OutBuff(12)) return 8;

  if (MakeCrcSInBuff(1, IndexInBuff()-2) != 0) return 9;
  if (InBuff(IndexInBuff()-1) != 0xC0) return 10;

  return 0;
}


uchar   ChecksumS(void)
{
  uchar i = CheckS();
  if (i != 0)
  {
    Clear(); sprintf(szLo+1,"ошибка: 24.2.%u",i);
    DelayInf();
  }

  return i;
}

#endif
