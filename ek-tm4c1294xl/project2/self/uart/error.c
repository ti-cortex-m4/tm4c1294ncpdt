/*------------------------------------------------------------------------------
ERROR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../uart/uart_log.h"



#ifdef DEBUG

void __error__(char *pcFileName, ulong dwLine)
{
  CONSOLE_UART("\nfile: %s line: %d\n", pcFileName, dwLine);
  while(1)
  {
  }
}

#endif
