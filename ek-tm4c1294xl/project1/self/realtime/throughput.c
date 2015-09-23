/*------------------------------------------------------------------------------
THROUGHPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_throughput.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "../serial/ports_stack.h"
#include "throughput.h"



//static volatile bool    fLock;



void    InitThroughput(void)
{
  iwThroughput = tiCurr.bSecond*10 - 1;
//  fLock = false;
}



void    RunThroughput(void)
{
//  if (fLock == false)
  {
    mdwThroughput[iwThroughput]++;
  }
}



void    EveryMinuteThroughput(void)
{
  iwThroughput = 0;
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
}
