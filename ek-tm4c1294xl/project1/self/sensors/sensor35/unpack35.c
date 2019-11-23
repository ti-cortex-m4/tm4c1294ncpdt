/*------------------------------------------------------------------------------
DECOMPRESS35!C


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
#include "unpack35.h"



#ifndef SKIP_35


//                                          0123456789ABCDEF
static char const       szError35[]      = "    Ошибка      ";



void    Decompress35(void)
{
uchar   i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (InBuff(i) == 0xC0) j++;
  if (j != 2) return;

  if ((InBuff(0) != 0xC0) || (InBuff(IndexInBuff()-1) != 0xC0))
    return;

  MonitorString("\n Unpack start");
  MonitorIn();

  i = 1;
  j = 1;
  while (i < IndexInBuff()) {
    if ((InBuff(i) == 0xDB) && (InBuff(i+1) == 0xDD)) {
      MonitorString("\n Unpack character 0хDB after input: "); MonitorCharDec(i);
      SetInBuff(j, 0xDB);
      i++; i++;
      j++;
    } else if ((InBuff(i) == 0xDB) && (InBuff(i+1) == 0xDC)) {
      MonitorString("\n Unpack character 0хC0 after input: "); MonitorCharDec(i);
      SetInBuff(j, 0xC0);
      i++; i++;
      j++;
    } else {
      SetInBuff(j, InBuff(i));
      i++;
      j++;
    }
  }

  SetIndexInBuff(j);

  MonitorString("\n Unpack finish");
  MonitorIn();

/*
  if ((InBuff(6) & 0xF0) != 0x50) // TODO 35
  {
    Clear(); sprintf(szLo+1,"ошибка: 35.1.%u",(InBuff(6) & 0xF0));
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

    j = Repack35(0xDD);
    if (j != 0)
    {
      SetInBuff(j, 0xDB);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, InBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }

    j = Repack35(0xDC);
    if (j != 0)
    {
      SetInBuff(j, 0xC0);
      for (i=j+1; i<=IndexInBuff()-2; i++) SetInBuff(i, InBuff(i+1));
      SetIndexInBuff(IndexInBuff()-1);
      f = 1;
      continue;
    }
  }
*/
  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}



static uchar CheckRouter35(void) // TODO 35
{
  if (InBuff(0) != 0xC0) return 1;
//  if (InBuff(1) != 0x48) return 2;
//
//  if (InBuffIntLtl(2) != wPrivate) return 3;
//  if (InBuffIntLtl(4) != (mpdwAddress1[diCurr.bAddress-1] % 0x10000)) return 4;
//
//  if ((InBuff(6) & 0xF0) != 0x50) return 5;
//  if ((IndexInBuff() >= 11) && (IndexInBuff() != (InBuff(6) & 0x0F) + 11)) return 6;
//
//  if (InBuff(7) != OutBuff(11)) return 7;
//  if (InBuff(8) != OutBuff(12)) return 8;
//
//  if (MakeCrcSInBuff(1, IndexInBuff()-2) != 0) return 9;
  if (InBuff(IndexInBuff()-1) != 0xC0) return 10;

  return 0;
}


uchar   ChecksumRouter35(void)
{
  uchar i = CheckRouter35();
  if (i != 0)
  {
    SaveDisplay();

    ShowHi(szError35);
    Clear(); sprintf(szLo+3,"роутера: %u",i);

    MonitorString("\n router frame error: "); MonitorCharHex(i);

    DelayInf();
    LoadDisplay();
  }

  return i;
}




static uchar CheckSensor35(void)
{
  if (InBuff(0) != 0xC0) return 1;
  if (InBuff(1) != 0x48) return 2;

  if (InBuffIntLtl(2) != wPrivate) return 3;
  if (InBuffIntLtl(4) != (mpdwAddress1[diCurr.bAddress-1] % 0x10000)) return 4;

  if ((InBuff(6) & 0xF0) != 0x50) return 5;
  if ((IndexInBuff() >= 11) && (IndexInBuff() != (InBuff(6) & 0x0F) + 11)) return 6;

//  if (InBuff(7) != OutBuff(11)) return 7;
//  if (InBuff(8) != OutBuff(12)) return 8;

  if (MakeCrcSInBuff(1, IndexInBuff()-2) != 0) return 9;
  if (InBuff(IndexInBuff()-1) != 0xC0) return 10;

  return 0;
}


uchar   ChecksumSensor35(void)
{
  uchar i = CheckSensor35();
  if (i != 0)
  {
    SaveDisplay();

    ShowHi(szError35);
    Clear(); sprintf(szLo+2,"счетчика: %u",i);

    MonitorString("\n sensor frame error: "); MonitorCharHex(i);

    DelayInf();
    LoadDisplay();
  }

  return i;
}

#endif
