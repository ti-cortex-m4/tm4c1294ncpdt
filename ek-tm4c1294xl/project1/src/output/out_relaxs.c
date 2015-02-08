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
#include        "../flash/files.h"



void    OutGetRelaxs(void)
{
  InitPushCRC();
  PushChar(boRelaxsFlag);
  PushChar(ibRelaxsTariff);
  Push(&reRelaxs, sizeof(relax));
  Output(2+sizeof(relax));
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
