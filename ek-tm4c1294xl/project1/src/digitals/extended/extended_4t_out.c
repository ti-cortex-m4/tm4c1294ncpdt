/*------------------------------------------------------------------------------
EXTENDED_4T_OUT,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "../../time/timedate.h"
#include "automatic_4t.h"
#include "extended_4t.h"
#include "extended_4t_out.h"



uint    PushData4T(uchar  ibCan, bool  fDouble)
{
  if (SupportedExtended4T(ibCan) == false)
  {
    uint wSize = 0;
    wSize += PushChar(ST4_NOTSUPPORTED);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
    {
      wSize += PushFloatOrDouble(0, fDouble);
    }

    wSize += PushTime(tiZero);
    return wSize;
  }
  else
  {
    value4t vl = mpCntMonCan4T[ibCan];

    uint wSize = 0;

    wSize += PushChar(vl.bStatus);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
    {
      wSize += PushFloatOrDouble(vl.mpdbValuesT[t], fDouble);
    }

    wSize += PushTime(vl.tiUpdate);
    return wSize;
  }
}



void    OutExtended4T(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    wSize += PushChar(fExt4TFlag);
    wSize += PushChar(bExt4TMonths);

    LoadExt4TValues(InBuff(6));

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        wSize += PushData4T(c, fDouble);
      }
    }

    OutptrOutBuff(wSize);
  }
}
