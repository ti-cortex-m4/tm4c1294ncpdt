/*------------------------------------------------------------------------------
error.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../uart/uart_log.h"



#ifdef DEBUG

void __error__(char *pszFileName, ulong dwLine)
{
  ERROR_UART("\n assert error: file %s, line %d\n", pszFileName, dwLine);

  while (true)
  {
  }
}

#endif
