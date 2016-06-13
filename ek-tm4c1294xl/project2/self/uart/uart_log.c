/*------------------------------------------------------------------------------
uart_log,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "../kernel/settings.h"
#include "uart_log.h"


/*
static volatile ulong       dwLogTimer;



void    LogTimer_1000Hz(void)
{
  dwLogTimer++;
}
*/


void    InitUARTLog(ulong dwClockFreq)
{
#ifdef DEBUG
  UARTStdioConfig(0, 115200, dwClockFreq);
#endif
}

/*
void    PrintLogTimer(void)
{
  UARTprintf("%5u.%03u ", (dwLogTimer / 1000), (dwLogTimer % 1000));
}
*/
