/*------------------------------------------------------------------------------
MONITOR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "monitor.h"



static volatile bool    fMonitor;

static volatile uint    cwMonitorDelay;



void    InitMonitor(void)
{
  fMonitor = false;
  cwMonitorDelay = 0;
}



void    RepeatMonitor(void)
{
  if (fMonitor == true)
    cbFlowDelay = cbMaxFlowDelay;
}


void    CloseMonitor(void)
{
  if (fMonitor == true)
  {
    cwMonitorDelay = 0;
    fMonitor = false;

    //
  }
}


void    DelayMonitor_1Hz(void)
{
  if (cwMonitorDelay == 0)
    CloseMonitor();
  else
    cwMonitorDelay--;
}



bool    UseMonitor(void)
{
  return false;
}

/*
void    MonitorStart(void) {
 if (UseMonitor()) {

  IntDisable(INT_UART0);
  UARTStdioConfig(0, 9600, 120000000);

  }
}


void    MonitorStop(void) {
 if (UseMonitor()) {

  IntEnable(INT_UART0);

  }
}
*/


void    MonitorString(const char  *psz)
{
  if (UseMonitor()) {
    UARTprintf(psz);
  }
}


void    MonitorChar(uchar  b)
{
  if (UseMonitor())
  {
    UARTprintf(" %u ", b);
  }
}


void    MonitorInt(uint  w)
{
  if (UseMonitor())
  {
    UARTprintf(" %u ", w);
  }
}


void    MonitorLong(ulong  dw)
{
  if (UseMonitor())
  {
    UARTprintf(" %u ", dw);
  }
}


void    MonitorTime(time  ti)
{
  if (UseMonitor())
  {
    UARTprintf("%02u:%02u:%02u %02u.%02u.%02u",
               ti.bHour,
               ti.bMinute,
               ti.bSecond,
               ti.bDay,
               ti.bMonth,
               ti.bYear);
  }
}
