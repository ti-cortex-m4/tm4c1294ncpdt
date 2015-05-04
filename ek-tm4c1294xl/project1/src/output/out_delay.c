/*------------------------------------------------------------------------------
OUT_DELAY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../time/delay.h"



void    OutDelay(void)
{
  Delay(10000);
  LongResult(bRES_OK);
}
