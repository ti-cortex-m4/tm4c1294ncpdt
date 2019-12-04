/*------------------------------------------------------------------------------
OUT_SCHEDULE!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_schedule.h"
#include "../../serial/ports.h"
#include "../../digitals/schedule/schedule.h"
#include "../out_common.h"
#include "../../nvram/cache.h"
#include "../out_common.h"
#include "out_schedule.h"



void    OutGetEnblPrtHou(void)
{
  if (bInBuff6 < bPORTS)
    OutBoolArray(mpboEnblPrtHou[ bInBuff6 ], 48);
  else
    Result(bRES_BADADDRESS);
}


void    OutSetEnblPrtHou(void)
{
  if (bInBuff6 < bPORTS)
  {
    InitPop(7);

    uchar i;
    for (i=0; i<48; i++)
    {
      mpboEnblPrtHou[bInBuff6][i] = CharToBool(PopChar());
    }

    SaveCache(&chEnblPrtHou);

    LongResult(bRES_OK);
  }
  else Result(bRES_BADADDRESS);
}



void    OutGetCtrlHou(void)
{
  OutBoolArray(mpboCtrlHou, 48);
}


void    OutSetCtrlHou(void)
{
  InitPop(6);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboCtrlHou[i] = CharToBool(PopChar());
  }

  SaveCache(&chCtrlHou);

  Result(bRES_OK);
}



void    OutGetRecalcHou(void)
{
  InitPushCRC();
  PushBool(boRecalcAlways);
  PushBoolArray(mpboRecalcHou, 48);
  Output(1+48);
}


void    OutSetRecalcHou1(void)
{
  InitPop(6);

  boRecalcAlways = CharToBool(PopChar());
  SaveCache(&chRecalcAlways);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboRecalcHou[i] = CharToBool(PopChar());
  }

  SaveCache(&chRecalcHou);

  Result(bRES_OK);
}


void    OutSetRecalcHou2(void)
{
  InitPop(6);

  PopChar();

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboRecalcHou[i] = CharToBool(PopChar());
  }

  SaveCache(&chRecalcHou);

  Result(bRES_OK);
}



void    OutGetTransitHou(void)
{
  OutBoolArray(mpboTransitHou, 48);
}


void    OutSetTransitHou(void)
{
  InitPop(6);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboTransitHou[i] = CharToBool(PopChar());
  }

  SaveCache(&chTransitHou);

  Result(bRES_OK);
}
