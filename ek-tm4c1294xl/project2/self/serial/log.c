/*------------------------------------------------------------------------------
LOG.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "log.h"



static volatile ulong       dwLogTimer;



void    LogTimer_1000Hz(void)
{
  dwLogTimer++;
}


void    PrintLogTimer(void)
{
  UARTprintf("%5u.%03u ", (dwLogTimer / 1000), (dwLogTimer % 1000));
}
