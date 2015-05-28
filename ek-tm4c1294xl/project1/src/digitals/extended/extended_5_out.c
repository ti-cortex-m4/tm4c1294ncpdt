/*------------------------------------------------------------------------------
EXTENDED_5_OUT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "extended_5.h"
#include "extended_5_out.h"



void    OutExtended50(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    wSize += PushChar(fExt5Flag);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        value5b vl = mpCntDayCan5[c];

        uchar t;
        for (t=0; t<bTARIFFS; t++)
        {
          wSize += PushFloatOrDouble(vl.stValue.mpdbValuesT[t], fDouble);
        }

        wSize += PushTime(vl.tiUpdate);

        wSize += PushChar(vl.boSuccess);

        wSize += PushInt(vl.cwSuccess);
        wSize += PushInt(vl.cwError);
      }
    }

    OutptrOutBuff(wSize);
  }
}


void    OutExtended51(bool  fDouble)
{

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();
    uint wSize = 0;

    wSize += PushChar(fExt5Flag);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        value5b vl = mpCntDayCan5[c];

        uchar t;
        for (t=0; t<bTARIFFS; t++)
        {
          wSize += PushFloatOrDouble(vl.stValue.mpdbValuesT[t], fDouble);
        }

        wSize += PushTime(vl.tiUpdate);
      }
    }

    OutptrOutBuff(wSize);
  }
}
