/*------------------------------------------------------------------------------
THROUGHPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_throughput.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "../serial/ports_stack.h"
#include "throughput.h"



void    InitThroughput(void)
{
  iwThroughput = tiCurr.bSecond*10;
}



void    RunThroughput(void)
{
  mdwThroughput[iwThroughput]++;
}



void    EveryMinuteThroughput(void)
{
  iwThroughput = 0;
  mdwThroughput[iwThroughput] = 0;
}


void    OutThroughput(void)
{
  InitPushCRC();
  PushInt(iwThroughput);
  Push(&mdwThroughput, sizeof(mdwThroughput));
  Output(2 + sizeof(mdwThroughput));
}



void    Throughput_10Hz(void)
{
  iwThroughput = (iwThroughput + 1) % 600;
  mdwThroughput[iwThroughput] = 0;
}
