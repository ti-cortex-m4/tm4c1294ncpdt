/*------------------------------------------------------------------------------
OUT_LIMITS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_limits.h"
#include "../digitals/digitals.h"
#include "../serial/ports.h"



void    OutStopCan2(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      if (GetDigitalDevice(c) == 0)
        PushIntBig(0);
      else
        PushIntBig(mpcwStopCan[c]);

      wSize += sizeof(uint);
    }
  }

  OutptrOutBuff(wSize);
}
