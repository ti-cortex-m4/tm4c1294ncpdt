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
  OutStrengthAndPadType("A0", GPIO_PORTA_BASE, GPIO_PIN_0);
  OutStrengthAndPadType("A1", GPIO_PORTA_BASE, GPIO_PIN_1);
  CONSOLE("UART4 \n");
  OutStrengthAndPadType("A2", GPIO_PORTA_BASE, GPIO_PIN_2);
  OutStrengthAndPadType("A3", GPIO_PORTA_BASE, GPIO_PIN_3);
  CONSOLE("UART3 \n");
  OutStrengthAndPadType("A4", GPIO_PORTA_BASE, GPIO_PIN_4);
  OutStrengthAndPadType("A5", GPIO_PORTA_BASE, GPIO_PIN_5);
  CONSOLE("UART2 \n");
  OutStrengthAndPadType("A6", GPIO_PORTA_BASE, GPIO_PIN_6);
  OutStrengthAndPadType("A7", GPIO_PORTA_BASE, GPIO_PIN_7);
  CONSOLE("UART1 \n");
  OutStrengthAndPadType("B0", GPIO_PORTB_BASE, GPIO_PIN_0);
  OutStrengthAndPadType("B1", GPIO_PORTB_BASE, GPIO_PIN_1);

  CONSOLE("\n");
  OutStrengthAndPadType("F3", GPIO_PORTF_BASE, GPIO_PIN_3);
  OutStrengthAndPadType("F2", GPIO_PORTF_BASE, GPIO_PIN_2);
  OutStrengthAndPadType("F1", GPIO_PORTF_BASE, GPIO_PIN_1);
  OutStrengthAndPadType("F0", GPIO_PORTF_BASE, GPIO_PIN_0);
#endif
}


