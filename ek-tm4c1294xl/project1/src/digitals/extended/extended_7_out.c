/*------------------------------------------------------------------------------
EXTENDED_7_OUT.C

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../serial/ports.h"
#include "../../time/rtc.h"
#include "../../flash/files.h"
#include "../../energy.h"
#include "extended_7.h"
#include "extended_7_out.h"



void    OutExtended7(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bDAYS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntDayCanBuff7( (bDAYS+ibHardDay-InBuff(6)) % bDAYS );

    InitPushPtr();            
    PushInt(cwDayCan7);
    uint wSize = 2;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0)
      {
        Push(&mpCntBoxCan7[c], sizeof(value6));
        wSize += sizeof(value6);
      }
    }

    OutptrOutBuff(wSize);
  }
}
