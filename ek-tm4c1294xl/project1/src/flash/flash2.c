/*------------------------------------------------------------------------------
FLASH1.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include 		"inc/hw_gpio.h"
#include 		"inc/hw_memmap.h"
#include 		"inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "at45.h"
//#include "flash1.h"



void InitAT45_2(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R1; // GPIO Port B Run Mode Clock Gating Control

  DelayGPIO();

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR) |= 0x000C; // GPIO Direction
  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR) &= 0xFFFC;

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DEN) |= 0x000C; // GPIO Digital Enable


  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control

  DelayGPIO();

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0002; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) &= 0xFFF2;

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0003; // GPIO Digital Enable
}

