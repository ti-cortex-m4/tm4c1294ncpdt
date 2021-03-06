/*------------------------------------------------------------------------------
OUT_LIMITS!C
                    

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_limits.h"
#include "../../serial/ports.h"
#include "../../digitals/limits.h"



void    OutStartCan(void)
{
  InitPushPtr();
  uint wSize = 0;

  PushBool(fUseBounds);
  wSize++;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      PushBool(mpboStartCan[c]);
      PushIntBig(mpcwStopCan[c]);
      PushIntBig(mpcwStartRelCan[c]);
      PushIntBig(mpcwStartAbs16Can[c]);
      PushLongBig(mpcdwStartAbs32Can[c]);
      PushChar(0);
      PushChar(0);
      wSize += 13;
    }
  }

  OutptrOutBuff(wSize);
}


void    OutStopAuxCan(void)
{
  InitPushCRC();

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    PushIntBig(mpcwStopAuxCan[c]);
  }

  Output(2*64);
}
