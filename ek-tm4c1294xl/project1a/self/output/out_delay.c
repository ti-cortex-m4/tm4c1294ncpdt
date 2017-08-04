/*------------------------------------------------------------------------------
OUT_DELAY.C

Измерение реальной длительности задержек
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../time/delay.h"
#include "out_delay.h"



void    OutDelay(void)
{
  DelaySeconds(10);
  LongResult(bRES_OK);
}
