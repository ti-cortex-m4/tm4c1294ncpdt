/*------------------------------------------------------------------------------
LOG.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "log.h"



static volatile ulong       dwLogTimer;



void    IncLogTimer(void)
{
  dwLogTimer++;
}


void    OutLogTimer(void)
{
  UARTprintf("%5u.%03u ", (dwLogTimer / 1000), (dwLogTimer % 1000));
}
