/*------------------------------------------------------------------------------
OUT_RELAXS.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../ports.h"
#include        "../timedate.h"
#include        "../keyboard.h"
#include        "../tariffs/relaxs.h"



void    OutGetRelaxs(void)
{
  InitPushCRC();
  PushChar(boRelaxsFlag);
  PushChar(ibRelaxsTariff);
  Push(&mpreRelaxs, sizeof(mpreRelaxs));
  Output(2+sizeof(mpreRelaxs));
}


void    OutSetRelaxs(void)
{
uchar  i;

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    InitPop(6);
    i = PopChar();
    if (i <= bRELAXS)
    {
      memset(&mpreRelaxs, 0, sizeof(mpreRelaxs));
      mpreRelaxs.bSize = i;
      if (mpreRelaxs.bSize > 0)
      {
        for (i=0; i<mpreRelaxs.bSize; i++)
        {
          Pop(&tiAlt, sizeof(time));
          mpreRelaxs.mptiDate[i] = tiAlt;
        }
      }
      LongResult(bRES_OK);
    }
    else Result(bRES_BADDATA);
  }
  else Result(bRES_NEEDREPROGRAM);
}
