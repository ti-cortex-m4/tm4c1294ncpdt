/*------------------------------------------------------------------------------
uart_log.h


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "uart_log.h"



static volatile ulong       dwLogTimer;



void    LogTimer_1000Hz(void)
{
  dwLogTimer++;
}



void    InitLog(void)
{
#ifdef DEBUG
  UARTStdioConfig(0, 115200, 120000000);
#endif
}


void    PrintLogTimer(void)
{
  UARTprintf("%5u.%03u ", (dwLogTimer / 1000), (dwLogTimer % 1000));
}
