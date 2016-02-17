/*------------------------------------------------------------------------------
uart_printf,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "../settings.h"
#include "uart_printf.h"



void UartPrintF(const char *pcsz, ...)
{
  if (fUartDebugFlag)
  {
    va_list va;
    va_start(va, pcsz);

    UARTvprintf(pcsz, va);

    va_end(va);
  }
}
