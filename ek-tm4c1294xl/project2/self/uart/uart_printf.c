/*------------------------------------------------------------------------------
uart_printf.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "uart_printf.h"



void UartPrintF(const char *pcString, ...)
{
  va_list va;
  va_start(va, pcString);

  UARTvprintf(pcString, va);

  va_end(va);
}
