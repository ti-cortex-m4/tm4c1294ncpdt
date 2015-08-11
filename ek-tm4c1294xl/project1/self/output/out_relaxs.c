/*------------------------------------------------------------------------------
OUT_RELAXS.C
                    

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_tariffs.h"
#include "../serial/ports.h"
#include "../time/timedate.h"
#include "../keyboard/keyboard.h"
#include "../tariffs/relaxs.h"
#include "../nvram/cache.h"



void    OutGetRelaxs(void)
{
  InitPushCRC();
  PushBool(boRelaxsFlag);
  PushChar(ibRelaxsTariff);
  Push(&reRelaxs, sizeof(relaxs));
  Output(2+sizeof(relaxs));
}


void    OutSetRelaxs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    InitPop(6);

    uchar bSize = PopChar();
    if (bSize <= bRELAXS)
    {
      memset(&reRelaxs, 0, sizeof(reRelaxs));
      reRelaxs.bSize = bSize;

      if (reRelaxs.bSize > 0)
      {
        uchar i;
        for (i=0; i<reRelaxs.bSize; i++)
        {
          time ti;
          Pop(&ti, sizeof(time));
          reRelaxs.mptiDate[i] = ti;
        }
      }

      SaveCache(&chRelaxs);

      LongResult(bRES_OK);
    }
    else Result(bRES_BADDATA);
  }
  else Result(bRES_NEEDREPROGRAM);
}
