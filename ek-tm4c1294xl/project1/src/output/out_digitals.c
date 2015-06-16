/*------------------------------------------------------------------------------
OUT_DIGITALS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals0.h"
#include "../digitals/digitals.h"
#include "../serial/ports.h"
#include "../flash/files.h"
#include "../nvram/cache.h"
#include "out_digitals.h"



void    OutGetDigital(void)
{
  if (bInBuff5 < bCANALS)
  {
    InitPushCRC();
    Push(&mpdiDigital[ bInBuff5 ], sizeof(digital));
    Output(sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetDigital(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    if (bInBuff5 < bCANALS)
    {
      digital di;

      di.ibPort   = bInBuff6;
      di.ibPhone  = bInBuff7;
      di.bDevice  = bInBuff8;
      di.bAddress = bInBuff9;
      di.ibLine   = bInBuffA;

      if (TrueDigital(&di))
      {
        mpdiDigital[bInBuff5] = di;

        if (bInBuff5 == bCANALS - 1)
          SaveCache(&chDigitals);

        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    OutGetDigitalsExt(void)
{
  InitPushPtr();
  uint wSize = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
    {
      Push(&mpdiDigital[c], sizeof(digital));
      wSize += sizeof(digital);
    }
  }

  OutptrOutBuff(wSize);
}
