/*------------------------------------------------------------------------------
OUT_COMMON,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "out_common.h"



void    OutGetFloatOrDoubleCan(double  *mpdb, bool  fDouble)
{
  InitPushCRC();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    wSize += PushFloatOrDouble(*mpdb++, fDouble);
  }

  Output(wSize);
}



void    OutGetFloatOrDoubleCan_GlobalWork(double  *mpdb, bool  fDouble)
{
  if (enGlobal != GLB_PROGRAM)
    OutGetFloatOrDoubleCan(mpdb, fDouble);
  else
    Result(bRES_NEEDWORK);
}


void    OutSetFloatOrDoubleCan(double  *mpdb, cache const  *pch, bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
  {
    InitPop(5);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      (*mpdb++) = fDouble ? PopDouble() : PopFloat();
    }

    SaveCache(pch);
    LongResult(bRES_OK);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutFloatOrDoubleCanExt(double  *mpdb, bool  fDouble)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushFloatOrDouble(mpdb[c], fDouble);
    }
  }

  OutptrOutBuff(wSize);
}


void    OutIntCanExt(uint  *mpw)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushInt(mpw[c]);
    }
  }

  OutptrOutBuff(wSize);
}


void    OutCharCanExt(uchar  *mpb)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushChar(mpb[c]);
    }
  }

  OutptrOutBuff(wSize);
}


void    OutBoolCanExt(bool  *mpf)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushBool(mpf[c]);
    }
  }

  OutptrOutBuff(wSize);
}



uchar   PushStatusFloatOrDouble(status  bStatus, double  db, bool  fDouble)
{
  uchar bSize = 0;

  bSize += PushChar(bStatus);
  bSize += PushFloatOrDouble(db, fDouble);

  return bSize;
}
