/*------------------------------------------------------------------------------
hardware_restart.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "../hardware/delay.h"
#include "hardware_restart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"



static void SetPL6To0(void)
{
  HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + (GPIO_PIN_6 << 2)) = ~0x0040;
}

static void SetPL6To1(void)
{
  HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + (GPIO_PIN_6 << 2)) = 0x0040;
}



static void InitPL6(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R10; // GPIO Port L Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTL_BASE + GPIO_O_DIR) |= 0x0040; // GPIO Direction
  HWREG(GPIO_PORTL_BASE + GPIO_O_DEN) |= 0x0040; // GPIO Digital Enable
  GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_6, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
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
