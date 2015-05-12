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


void    OutGetFloatCan_GlobalWork(float  *mfl)
{
  if (enGlobal != GLB_PROGRAM)
    OutGetFloatCan(mfl);
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



void    OutRealCanExt(real  *mpe)
{
  InitPushPtr();
  uint w = 0;

  uchar i;
  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      PushFloat(mpe[i]);
      w += sizeof(real);
    }
  }

  OutptrOutBuff(w);
}


void    OutIntCanExt(uint  *mpw)
{
  InitPushPtr();
  uint w = 0;

  uchar i;
  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      PushInt(mpw[i]);
      w += sizeof(uint);
    }
  }

  OutptrOutBuff(w);
}


void    OutCharCanExt(uchar  *mpb)
{
  InitPushPtr();
  uint w = 0;

  uchar i;
  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpb[i], sizeof(uchar));
      w += sizeof(uchar);
    }
  }

  OutptrOutBuff(w);
}


void    OutBoolCanExt(boolean  *mpf)
{
  InitPushPtr();
  uint w = 0;

  uchar i;
  for (i=0; i<bCANALS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpf[i], sizeof(boolean));
      w += sizeof(boolean);
    }
  }

  OutptrOutBuff(w);
}
