/*------------------------------------------------------------------------------
KEY.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include 		    "inc/hw_gpio.h"
#include 		    "inc/hw_memmap.h"
#include 		    "inc/hw_sysctl.h"
#include 		    "inc/hw_types.h"
#include        "time/delay.h"
#include        "key.h"




void InitKey(void)
{
#ifdef NATIVE_KEYBOARD

  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R12; // GPIO Port N Run Mode Clock Gating Control

  RunClocking();

  HWREG(GPIO_PORTN_BASE + GPIO_O_DIR) &= 0xFFF0; // GPIO Direction
  HWREG(GPIO_PORTN_BASE + GPIO_O_DEN) |= 0x000F; // GPIO Digital Enable

#endif
}

//Lo(5, HWREG((GPIO_PORTN_BASE + GPIO_O_DATA + 0x0004)));
