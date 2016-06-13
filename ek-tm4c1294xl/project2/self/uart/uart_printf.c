/*------------------------------------------------------------------------------
uart_printf.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "../kernel/settings.h"
#include "uart_printf.h"



void UARTPrintF(const char *pcsz, ...)
{
  if (ibDebugMode == DEBUG_MODE_UART)
  {
    va_list va;
    va_start(va, pcsz);

    UARTvprintf(pcsz, va);

    va_end(va);
  }
}
