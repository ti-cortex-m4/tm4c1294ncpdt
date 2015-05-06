/*------------------------------------------------------------------------------
OUT_COMMON,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutGetFloatCan(float  *mfl)
{
  InitPushCRC();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    PushFloat(*mfl++);
    wSize += sizeof(float);
  }

  Output(wSize);
}


void    OutGetFloatCan_GlobalWork(float  *mfl)
{
  if (enGlobal != GLB_PROGRAM)
    OutGetFloatCan(mfl);
  else
    Result(bRES_NEEDWORK);
}



void    OutSetFloatCan(float  *mfl)
{
  if (enGlobal == GLB_PROGRAM)
  {
    InitPop(5);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
//      PopReal();
//      SetCanReal(mpreT,c);
    }

    if (c == bCANALS)
      LongResult(bRES_OK);
    else
      Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}
