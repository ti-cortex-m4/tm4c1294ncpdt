/*------------------------------------------------------------------------------
OUT_COMMON,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"



void    OutFloatCan(float  *mfl)
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



void    OutFloatCan_GlobalWork(float  *mfl)
{
  if (enGlobal != GLB_PROGRAM)
    OutFloatCan(mfl);
  else
    Result(bRES_NEEDWORK);
}
