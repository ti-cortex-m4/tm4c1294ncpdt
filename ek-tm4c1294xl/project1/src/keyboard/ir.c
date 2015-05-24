/*------------------------------------------------------------------------------
IR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "keyboard.h"
#include "../time/delay.h"
#include "../../irmp/irmp.h"
#include "ir.h"



void    InitIR(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R13; // GPIO Port P Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR) &= 0xFFFE; // GPIO Direction
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN) |= 0x0001; // GPIO Digital Enable
}



void    RunIR(void)
{
  static IRMP_DATA irmp_data;

  if (irmp_get_data (&irmp_data))
  {
    bKey = (irmp_data).command;
    fKey = true;
  }
}
