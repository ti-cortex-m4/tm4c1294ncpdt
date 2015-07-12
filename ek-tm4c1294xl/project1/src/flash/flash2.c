/*------------------------------------------------------------------------------
FLASH2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../time/delay.h"



void    InitGPIO_Flash2(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R1; // GPIO Port B Run Mode Clock Gating Control

  DelayGPIO();

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR) |= 0x0030; // GPIO Direction

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DEN) |= 0x0030; // GPIO Digital Enable


  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R4; // GPIO Port E Run Mode Clock Gating Control

  DelayGPIO();

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) |= 0x0010; // GPIO Direction
  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DIR) &= 0xFFDF;

  HWREG(GPIO_PORTE_AHB_BASE + GPIO_O_DEN) |= 0x0030; // GPIO Digital Enable
}
