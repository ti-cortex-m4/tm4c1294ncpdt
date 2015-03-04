/*------------------------------------------------------------------------------
FLASH2.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include 		"inc/hw_gpio.h"
#include 		"inc/hw_memmap.h"
#include 		"inc/hw_sysctl.h"
#include 		"inc/hw_types.h"
#include        "../time/delay.h"
#include        "at45.h"
#include        "flash1.h"



#ifdef NATIVE_FLASH

void Init_SPIhandAT45DB321(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R3; // GPIO Port D Run Mode Clock Gating Control

  RunClocking();

  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x000E; // GPIO Direction
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) &= 0xFFFE;

  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x000F; // GPIO Digital Enable
}

#endif
