/*------------------------------------------------------------------------------
SYS_TICK!C

 SysTick timer
------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/systick.h"
#include "sys_tick.h"



static volatile ulong   dwSysTick;



void    InitSysTick(uint32_t  ui32SysClockFreq)
{
  SysTickPeriodSet(ui32SysClockFreq / 10000); // 1 ms
  SysTickEnable();
}



void    StartSysTick(void)
{
  dwSysTick = 0;
  SysTickIntEnable();
}


ulong   StopSysTick(void)
{
  SysTickIntDisable();
  return dwSysTick;
}



void    SysTickIntHandler(void)
{
  dwSysTick++;
}
