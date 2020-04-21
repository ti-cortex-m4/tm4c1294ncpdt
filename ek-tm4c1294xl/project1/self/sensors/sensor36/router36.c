/*------------------------------------------------------------------------------
ROUTER35!C


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
#include "device35.h"
#include "unpack35.h"
#include "router35.h"



void    Decompress35(void)
{
  uchar i,j;

  if (mpSerial[ibPort] != SER_INPUT_MASTER) return;

  j = 0;
  for (i=0; i<IndexInBuff(); i++) if (InBuff(i) == 0xC0) j++;
  if (j != 2) return;

  if ((InBuff(0) != 0xC0) || (InBuff(IndexInBuff()-1) != 0xC0))
    return;

#ifdef MONITOR_35
  MonitorString("\n router unpack start");
  MonitorIn();
#endif

  Unpack35();

#ifdef MONITOR_35
  MonitorString("\n router unpack finish");
  MonitorIn();
#endif

  mpSerial[ibPort] = SER_POSTINPUT_MASTER;
}



static uchar CheckRouter35(void)
{
  if (InBuff(0) != 0xC0) return 1;
  if (InBuff(1) != 0x02) return 2;

  if (InBuffIntLtl(8) != (mpdwAddress1[diCurr.bAddress-1] % 0x10000)) return 3;
  if (InBuffIntLtl(10) != 0) return 4;

  if (MakeCrc35InBuff(1, IndexInBuff()-2) != 0) return 5;
  if (InBuff(IndexInBuff()-1) != 0xC0) return 6;

  return 0;
}


uchar   ChecksumRouter35(void)
{
  uchar i = CheckRouter35();
  if (i != 0)
  {
    Clear(); sprintf(szLo+1,"ошибка: 35.1.%u",i);
    DelayInf();

#ifdef MONITOR_35
    MonitorString("\n router packet error: "); MonitorCharDec(i);
#endif
  }

  return i;
}



static uchar CheckSensor35(void)
{
  if (InBuff(0) != 0xC0) return 1;
  if (InBuff(1) != 0x48) return 2;

  if (InBuffIntLtl(2) != GetExchange35()) return 3;
  if (InBuffIntLtl(4) != (mpdwAddress1[diCurr.bAddress-1] % 0x10000)) return 4;

  if ((InBuff(6) & 0xF0) != 0x50) return 5;

  if (MakeCrcSInBuff(1, IndexInBuff()-2) != 0) return 6;
  if (InBuff(IndexInBuff()-1) != 0xC0) return 7;

  return 0;
}


uchar   ChecksumSensor35(void)
{
  uchar i = CheckSensor35();
  if (i != 0)
  {
    Clear(); sprintf(szLo+1,"ошибка: 35.2.%u",i);
    DelayInf();

#ifdef MONITOR_35
    MonitorString("\n sensor packet error: "); MonitorCharDec(i);
#endif
  }

  return i;
}
