/*------------------------------------------------------------------------------
ERROR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "log.h"



#ifdef DEBUG

void __error__(char *pcFileName, ulong dwLine)
{
  LOG(("\nfile: %s line: %d\n", pcFileName, dwLine));
  while(1)
  {
  }
}

#endif
