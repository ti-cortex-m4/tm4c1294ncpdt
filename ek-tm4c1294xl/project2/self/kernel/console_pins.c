/*------------------------------------------------------------------------------
console_pins.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/rom.h"
#include "log.h"
#include "console_pins.h"



void ConsolePins(void)
{
#if 1
  uint32_t dwStrength = 0;
  uint32_t dwPadType = 0;

  CONSOLE("UART 0 \n");
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_0, &dwStrength, &dwPadType); CONSOLE("A.0 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_1, &dwStrength, &dwPadType); CONSOLE("A.1 %X %X\n", dwStrength, dwPadType);
  CONSOLE("UART 4 \n");
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_2, &dwStrength, &dwPadType); CONSOLE("A.2 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_3, &dwStrength, &dwPadType); CONSOLE("A.3 %X %X\n", dwStrength, dwPadType);
  CONSOLE("UART 3 \n");
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_4, &dwStrength, &dwPadType); CONSOLE("A.4 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_5, &dwStrength, &dwPadType); CONSOLE("A.5 %X %X\n", dwStrength, dwPadType);
  CONSOLE("UART 2 \n");
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_6, &dwStrength, &dwPadType); CONSOLE("A.6 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTA_BASE, GPIO_PIN_7, &dwStrength, &dwPadType); CONSOLE("A.7 %X %X\n", dwStrength, dwPadType);
  CONSOLE("UART 1 \n");
  GPIOPadConfigGet(GPIO_PORTB_BASE, GPIO_PIN_0, &dwStrength, &dwPadType); CONSOLE("B.0 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTB_BASE, GPIO_PIN_1, &dwStrength, &dwPadType); CONSOLE("B.1 %X %X\n", dwStrength, dwPadType);

  GPIOPadConfigGet(GPIO_PORTF_BASE, GPIO_PIN_3, &dwStrength, &dwPadType); CONSOLE("F.3 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTF_BASE, GPIO_PIN_2, &dwStrength, &dwPadType); CONSOLE("F.2 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTF_BASE, GPIO_PIN_1, &dwStrength, &dwPadType); CONSOLE("F.1 %X %X\n", dwStrength, dwPadType);
  GPIOPadConfigGet(GPIO_PORTF_BASE, GPIO_PIN_0, &dwStrength, &dwPadType); CONSOLE("F.0 %X %X\n", dwStrength, dwPadType);
#endif
}
