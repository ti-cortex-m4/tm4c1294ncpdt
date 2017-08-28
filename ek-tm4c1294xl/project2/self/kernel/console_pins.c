/*------------------------------------------------------------------------------
console_pins.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "../hardware/rom.h"
#include "log.h"
#include "console_pins.h"



static void OutStrengthAndPadType(const char *pcszCode, uint32_t dwPort, uint8_t bPin)
{
  uint32_t dwStrength = 0;
  uint32_t dwPadType = 0;
  GPIOPadConfigGet(dwPort, bPin, &dwStrength, &dwPadType);
  CONSOLE("%s %X, %X\n", pcszCode, dwStrength, dwPadType);
}

void ConsolePins(void)
{
#if 1
  CONSOLE("UART0 \n");
  OutStrengthAndPadType("A0", GPIO_PORTA_BASE, 0);
  OutStrengthAndPadType("A1", GPIO_PORTA_BASE, 1);
  CONSOLE("UART4 \n");
  OutStrengthAndPadType("A2", GPIO_PORTA_BASE, 2);
  OutStrengthAndPadType("A3", GPIO_PORTA_BASE, 3);
  CONSOLE("UART3 \n");
  OutStrengthAndPadType("A4", GPIO_PORTA_BASE, 4);
  OutStrengthAndPadType("A5", GPIO_PORTA_BASE, 5);
  CONSOLE("UART2 \n");
  OutStrengthAndPadType("A6", GPIO_PORTA_BASE, 6);
  OutStrengthAndPadType("A7", GPIO_PORTA_BASE, 7);
  CONSOLE("UART1 \n");
  OutStrengthAndPadType("B0", GPIO_PORTB_BASE, 0);
  OutStrengthAndPadType("B1", GPIO_PORTB_BASE, 1);

  CONSOLE("\n");
  OutStrengthAndPadType("F3", GPIO_PORTF_BASE, 3);
  OutStrengthAndPadType("F2", GPIO_PORTF_BASE, 2);
  OutStrengthAndPadType("F1", GPIO_PORTF_BASE, 1);
  OutStrengthAndPadType("F0", GPIO_PORTF_BASE, 0);
#endif
}


