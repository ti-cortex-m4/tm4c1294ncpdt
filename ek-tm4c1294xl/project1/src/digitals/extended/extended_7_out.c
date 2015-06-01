/*------------------------------------------------------------------------------
EXTENDED_7_OUT.C

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../serial/ports.h"
#include "extended_7.h"
#include "extended_6_out.h"
#include "extended_7_out.h"



void    OutExtended7(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bDAYS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntBoxCan7( (bDAYS+ibHardDay-InBuff(6)) % bDAYS );

    InitPushPtr();
    uint wSize = 0;

    wSize += PushInt(cwDayCan7);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
      {
        wSize += PushData6(mpCntBoxCan7[c], fDouble);
      }
    }

    OutptrOutBuff(wSize);
  }
}
