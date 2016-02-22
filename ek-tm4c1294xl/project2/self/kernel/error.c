/*------------------------------------------------------------------------------
error.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/interrupt.h"
#include "../kernel/log.h"
#include "../uart/uart_log.h"



#ifdef DEBUG

void __error__(char *pszFileName, ulong dwLine)
{
  CONSOLE("assert error: file %s, line %d\n", pszFileName, dwLine);

  IntMasterDisable();

  while (true)
  {
  }
}

#endif
