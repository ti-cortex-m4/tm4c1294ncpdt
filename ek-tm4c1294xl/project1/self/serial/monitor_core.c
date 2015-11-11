/*------------------------------------------------------------------------------
MONITOR_CORE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "speeds.h"
#include "ports_common.h"
#include "monitor_core.h"



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
    UARTStdioConfig(0, 38400, 120000000);

    ibMonitorPort = 0;
  }
  else if (ibPrt == 1)
  {
    IntDisable(INT_UART1);
    UARTStdioConfig(1, 38400, 120000000);

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



uint    GetMonitorDelay(void)
{
  return cwMonitorDelay;
}
