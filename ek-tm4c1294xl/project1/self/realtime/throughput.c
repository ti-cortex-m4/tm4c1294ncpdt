/*------------------------------------------------------------------------------
THROUGHPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_throughput.h"
#include "../serial/ports.h"
#include "../serial/ports_stack.h"
#include "throughput.h"



static volatile bool    fLock;



void    InitThroughput(void)
{
  iwThroughput = 0;
  fLock = false;
}



void    RunThroughput(void)
{
  if (fLock == false)
  {
    mdwThroughput[iwThroughput]++;
  }
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
  fLock = true;
  iwThroughput = (iwThroughput + 1) % 600;
  fLock = false;
}
