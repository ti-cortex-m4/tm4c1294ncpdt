/*------------------------------------------------------------------------------
OUT_RELAXS.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_tariffs.h"
#include        "../serial/ports.h"
#include        "../time/timedate.h"
#include        "../keyboard/keyboard.h"
#include        "../tariffs/relaxs.h"
#include        "../flash/files.h"



void    OutGetRelaxs(void)
{
  InitPushCRC();
  PushChar(boRelaxsFlag);
  PushChar(ibRelaxsTariff);
  Push(&reRelaxs, sizeof(relaxs));
  Output(2+sizeof(relaxs));
}


void    OutSetRelaxs(void)
{
uchar  i;
time   ti;

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    InitPop(6);

    i = PopChar();
    if (i <= bRELAXS)
    {
      memset(&reRelaxs, 0, sizeof(reRelaxs));
      reRelaxs.bSize = i;
      if (reRelaxs.bSize > 0)
      {
        for (i=0; i<reRelaxs.bSize; i++)
        {
          Pop(&ti, sizeof(time));
          reRelaxs.mptiDate[i] = ti;
        }
      }
    	SaveFile(&flRelaxs);

      LongResult(bRES_OK);
    }
    else Result(bRES_BADDATA);
  }
  else Result(bRES_NEEDREPROGRAM);
}
