/*------------------------------------------------------------------------------
uart_log.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "../kernel/settings.h"
#include "uart_log.h"



void InitUARTLog(ulong dwClockFreq) {
  if (ibDebugMode == DEBUG_MODE_UART) {
    UARTStdioConfig(0, 115200, dwClockFreq);
  }
}
