/*------------------------------------------------------------------------------
MONITOR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../../tm4c1294xl/utils/uartstdio.h"
//#include "../../tm4c1294xl/driverlib/interrupt.h"
//#include "inc/hw_ints.h"
#include "../time/rtc.h"
//#include "speeds.h"
#include "ports_common.h"
#include "monitor.h"



void    MonitorString(const char  *psz)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz);
  }
}


void    MonitorChar(const char  *psz, uchar  b)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz, b);
  }
}


void    MonitorCharDec(uchar  b)
{
  MonitorChar("%u", b);
}


void    MonitorCharDec3(uchar  b)
{
  MonitorChar("%3u ", b);
}


void    MonitorCharHex(uchar  b)
{
  MonitorChar("%02X ", b);
}


void    MonitorInt(const char  *psz, uint  w)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz, w);
  }
}


void    MonitorIntDec(uint  w)
{
  MonitorInt("%u", w);
}


void    MonitorIntDec5(uint  w)
{
  MonitorInt("%5u ", w);
}


void    MonitorLong(const char  *psz, ulong  dw)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz, dw);
  }
}


void    MonitorLongDec(ulong  dw)
{
  MonitorLong("%u", dw);
}


void    MonitorTime(time  ti)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf("%02u:%02u:%02u %02u.%02u.%02u ",
               ti.bHour,
               ti.bMinute,
               ti.bSecond,
               ti.bDay,
               ti.bMonth,
               ti.bYear);
  }
}



void    MonitorOut(uint  cwIn, uint  cwOut)
{
  if (UseMonitor())
  {
    MonitorString("\n\n Output: out ="); MonitorIntDec(cwOut);
    MonitorString(" in ="); MonitorIntDec(cwIn);
    MonitorString(" "); MonitorTime(*GetCurrTimeDate());
    MonitorString("\n");

    uint i;
    for (i=0; i<cwOut; i++)
    {
      MonitorCharHex(OutBuff(i));
    }
  }
}


void    MonitorIn(void)
{
  if (UseMonitor())
  {
    MonitorString("\n Input: in ="); MonitorIntDec(IndexInBuff());
    MonitorString(" "); MonitorTime(*GetCurrTimeDate());
    MonitorString("\n");

    uint i;
    for (i=0; i<IndexInBuff(); i++)
    {
      MonitorCharHex(InBuff(i));
    }
  }
}
