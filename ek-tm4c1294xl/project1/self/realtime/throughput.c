/*------------------------------------------------------------------------------
THROUGHPUT.C

Измерение производительности
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "throughput.h"



static volatile uint    mwThroughput[600];

static volatile uint    iwThroughput;



void    InitThroughput(void)
{
  iwThroughput = tiCurr.bSecond*10;
  mwThroughput[iwThroughput] = 0;
}



void    RunThroughput(void)
{
  mwThroughput[iwThroughput]++;
}



void    EveryMinuteThroughput(void)
{
  iwThroughput = 0;
  mwThroughput[iwThroughput] = 0;
}



void    OutThroughput(void)
{
  InitPushCRC();
  PushInt(iwThroughput);
  PushIntArray((uint *)mwThroughput, 600);
  Output(2 + sizeof(mwThroughput));
}



void    Throughput_10Hz(void)
{
  iwThroughput = (iwThroughput + 1) % 600;
  mwThroughput[iwThroughput] = 0;
}
