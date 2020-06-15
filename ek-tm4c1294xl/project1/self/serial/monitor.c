/*------------------------------------------------------------------------------
MONITOR.C


------------------------------------------------------------------------------*/

#include <math.h>
#include "../main.h"
#include "utils/uartstdio.h"
#include "../time/rtc.h"
#include "ports_common.h"
#include "monitor_settings.h"
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


void    MonitorCharChar(uchar  b)
{
  MonitorChar("%c", (b < ' ' ? '_' : b));
}


void    MonitorBool(bool  f)
{
  MonitorChar("%c", (f ? '+' : '-'));
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


void    MonitorIntHex(uint  w)
{
  MonitorInt("%04X", w);
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


void    MonitorLongHex(ulong  dw)
{
  MonitorLong("%8X", dw);
}


void    MonitorLongDec4(ulong  dw)
{
  if (UseMonitor())
  {
    MonitorLong("%u", (uint)(dw / 10000));
    MonitorString(".");
    MonitorLong("%04u", (uint)(dw % 10000));
  }
}


void    MonitorLong64Hex(uint64_t  ddw)
{
  MonitorLong("%08X", ddw / 0x100000000);
  MonitorString("_");
  MonitorLong("%08X", ddw % 0x100000000);
}


void    MonitorDouble6(double  db)
{
  if (UseMonitor())
  {
    MonitorLong("%u", (ulong)db);
    MonitorString(".");
    double integral = 0;
    MonitorLong("%06u", (ulong)(modf(db, &integral) * 1000000));
  }
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



static void MonitorOutHex(uint  cwOut)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwOut; i++)
  {
    MonitorCharHex(OutBuff(i));
  }
}


static void MonitorOutChar7(uint  cwOut)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwOut; i++)
  {
    MonitorCharChar(OutBuff(i) & 0x7F);
  }
}


static void MonitorOutChar8(uint  cwOut)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwOut; i++)
  {
    MonitorCharChar(OutBuff(i));
  }
}


void    MonitorOut(uint  cwIn, uint  cwOut)
{
  if (UseMonitor())
  {
    if (fMonitorLogBasic)
    {
      MonitorString("\n\n Output: out="); MonitorIntDec(cwOut);
      MonitorString(" in="); MonitorIntDec(cwIn);
//      MonitorString(" "); MonitorTime(*GetCurrTimeDate());
    }

    if (fMonitorLogHex) MonitorOutHex(cwOut);
    if (fMonitorLogChar7) MonitorOutChar7(cwOut);
    if (fMonitorLogChar8) MonitorOutChar8(cwOut);
  }
}



static void MonitorInHex(uint  cwIn)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwIn; i++)
  {
    MonitorCharHex(InBuff(i));
  }
}


static void MonitorInChar7(uint  cwIn)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwIn; i++)
  {
    MonitorCharChar(InBuff(i) & 0x7F);
  }
}


static void MonitorInChar8(uint  cwIn)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwIn; i++)
  {
    MonitorCharChar(InBuff(i));
  }
}


void    MonitorIn(void)
{
  if (UseMonitor())
  {
    if (fMonitorLogBasic)
    {
      MonitorString("\n Input: in="); MonitorIntDec(IndexInBuff());
//      MonitorString(" "); MonitorTime(*GetCurrTimeDate());
    }

    if (fMonitorLogHex) MonitorInHex(IndexInBuff());
    if (fMonitorLogChar7) MonitorInChar7(IndexInBuff());
    if (fMonitorLogChar8) MonitorInChar8(IndexInBuff());
  }
}



void    MonitorArrayHex(uchar  *pbData, uint  wSize)
{
  if (UseMonitor())
  {
    MonitorString("\n");
    MonitorString("\n Size="); MonitorIntDec(wSize); MonitorString(" "); MonitorIntHex(wSize);
    MonitorString("\n");

    uint i = 0;
    while (wSize--)
    {
      MonitorCharHex(*pbData++);
      if (++i % 16 == 0) MonitorString("\n");
    }

    MonitorString("\n");
  }
}
