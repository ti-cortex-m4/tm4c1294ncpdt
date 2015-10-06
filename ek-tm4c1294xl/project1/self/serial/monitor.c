/*------------------------------------------------------------------------------
MONITOR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../../tm4c1294xl/utils/uartstdio.h"
#include "../../tm4c1294xl/driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "../time/rtc.h"
#include "speeds.h"
#include "ports_common.h"
#include "monitor.h"



#define MONITOR_DELAY   60*5



static volatile bool    fMonitor;

static volatile uint    cwMonitorDelay;

static volatile uchar   ibMonitorPort;



void    InitMonitor(void)
{
  fMonitor = false;
  cwMonitorDelay = 0;
}


bool    UseMonitor(void)
{
  return (fMonitor == true) && (cwMonitorDelay > 0);
}



void    MonitorRepeat(void)
{
  if (UseMonitor())
  {
    cwMonitorDelay = MONITOR_DELAY;
  }
}



void    MonitorOpen(uchar  ibPrt)
{
  if (ibPrt == 0)
  {
    IntDisable(INT_UART0);
    UARTStdioConfig(0, 57600, 120000000);

    ibMonitorPort = 0;
  }
  else if (ibPrt == 1)
  {
    IntDisable(INT_UART1);
    UARTStdioConfig(1, 57600, 120000000);

    ibMonitorPort = 1;
  }
  else
  {
    ASSERT(false);
  }

  fMonitor = true;
  cwMonitorDelay = MONITOR_DELAY;
}


void    MonitorClose(void)
{
  if (fMonitor == true)
  {
    fMonitor = false;
    cwMonitorDelay = 0;

    if (ibMonitorPort == 0)
    {
      SetSpeed(0);
      IntEnable(INT_UART0);
    }
    else if (ibMonitorPort == 1)
    {
      SetSpeed(1);
      IntEnable(INT_UART1);
    }
  }
}



void    DelayMonitor_1Hz(void)
{
  if (cwMonitorDelay == 0)
    MonitorClose();
  else
    cwMonitorDelay--;
}



void    MonitorString(const char  *psz)
{
  if (UseMonitor())
  {
    UARTprintf(psz);
  }
}


void    MonitorChar(const char  psz, uchar  b)
{
  if (UseMonitor())
  {
    UARTprintf(psz, b);
  }
}


void    MonitorCharDec(uchar  b)
{
  if (UseMonitor())
  {
    UARTprintf(" %3u", b);
  }
}


void    MonitorCharHex(uchar  b)
{
  if (UseMonitor())
  {
    UARTprintf(" %02X", b);
  }
}


void    MonitorInt(const char  psz, uint  w)
{
  if (UseMonitor())
  {
    UARTprintf(psz, w);
  }
}


void    MonitorIntDec(uint  w)
{
  if (UseMonitor())
  {
    UARTprintf(" %u", w);
  }
}


void    MonitorLongDec(ulong  dw)
{
  if (UseMonitor())
  {
    UARTprintf(" %u", dw);
  }
}


void    MonitorTime(time  ti)
{
  if (UseMonitor())
  {
    UARTprintf(" %02u:%02u:%02u %02u.%02u.%02u",
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
    MonitorRepeat();

    MonitorString("\n\n Output: out ="); MonitorIntDec(cwOut);
    MonitorString(" in ="); MonitorIntDec(cwIn);
    MonitorString("  "); MonitorTime(*GetCurrTimeDate());
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
    MonitorString("  "); MonitorTime(*GetCurrTimeDate());
    MonitorString("\n");

    uint i;
    for (i=0; i<IndexInBuff(); i++)
    {
      MonitorCharHex(InBuff(i));
    }
  }
}



uint    GetMonitorDelay(void)
{
  return cwMonitorDelay;
}
