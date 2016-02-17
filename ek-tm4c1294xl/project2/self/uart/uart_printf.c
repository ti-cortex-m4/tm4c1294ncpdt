/*------------------------------------------------------------------------------
uart_printf.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "uart_printf.h"



void UartPrintF(const char *pcString, ...)
{
  if (fUartDebugFlag)
  {
    va_list va;
    va_start(va, pcString);

    UARTvprintf(pcString, va);

    va_end(va);
  }
}
