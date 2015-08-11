/*------------------------------------------------------------------------------
SYS_TICK.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/systick.h"
#include "sys_tick.h"



void    InitSysTick(uint32_t  ui32SysClock)
{
  SysTickPeriodSet(ui32SysClock / 1000); // 1 ms
  HWREG(NVIC_ST_CURRENT) = 0;
}


void    StartSysTick(void)
{
  HWREG(NVIC_ST_CURRENT) = 0;
  SysTickEnable();
}


ulong   StopSysTick(void)
{
  SysTickDisable();
  return HWREG(NVIC_ST_CURRENT);
}
