/*------------------------------------------------------------------------------
hardware_restart.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "../hardware/delay.h"
//#include "../kernel/settings.h"
//#include "../kernel/log.h"
#include "hardware_restart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"



static void SetPL6To0(void)
{
  HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + 0x0020) = ~0x0008;
}

static void SetPL6To1(void)
{
  HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + 0x0020) = 0x0008;
}



static void InitPL6(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R10; // GPIO Port L Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0008; // GPIO Direction
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0008; // GPIO Digital Enable
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
}



void InitHardwareRestart(void)
{
  InitPL6();
  SetPL6To0();
}

void RunHardwareRestart(void)
{
  SetPL6To1();
  DelaySecond(1);
}
