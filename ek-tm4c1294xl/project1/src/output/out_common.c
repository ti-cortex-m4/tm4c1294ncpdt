/*------------------------------------------------------------------------------
OUT_COMMON,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../flash/files.h"



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



void    OutGetFloatOrDoubleCan(double  *mdb, bool  fDouble)
{
  InitPushCRC();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    wSize += PushFloatOrDouble(*mdb++, fDouble);
  }

  Output(wSize);
}



void    OutGetFloatOrDoubleCan_GlobalWork(double  *mdb, bool  fDouble)
{
  if (enGlobal != GLB_PROGRAM)
    OutGetFloatOrDoubleCan(mdb, fDouble);
  else
    Result(bRES_NEEDWORK);
}


void    OutSetFloatCan(float  *mfl, file const  *pfl)
{
  if (enGlobal == GLB_PROGRAM)
  {
    InitPop(5);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      (*mfl++) = PopFloat();
    }

    SaveFile(pfl);
    LongResult(bRES_OK);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutFloatCanMap(real  *mpe)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushFloat(mpe[c]);
    }
  }

  OutptrOutBuff(wSize);
}


void    OutIntCanMap(uint  *mpw)
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


void    OutCharCanMap(uchar  *mpb)
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


void    OutBoolCanMap(bool  *mpf)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      wSize += PushChar(mpf[c]);
    }
  }

  OutptrOutBuff(wSize);
}
