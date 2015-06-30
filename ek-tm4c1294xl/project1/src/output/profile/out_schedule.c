/*------------------------------------------------------------------------------
OUT_SCHEDULE.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_schedule.h"
#include "../../serial/ports.h"
#include "../../digitals/schedule/schedule.h"
#include "../../flash/files.h"
#include "../../nvram/cache.h"



void    OutGetEnblPrtHou(void)
{
  if (bInBuff6 < bPORTS)
    Common(&mpboEnblPrtHou[ bInBuff6 ], 48);
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
      mpboEnblPrtHou[bInBuff6][i] = CharToBoolean(PopChar());
    }

    SaveFile(&flEnblPrtHou);

    LongResult(bRES_OK);
  }
  else Result(bRES_BADADDRESS);
}



void    OutGetCtrlHou(void)
{
  Common(&mpboCtrlHou, 48);
}


void    OutSetCtrlHou(void)
{
  InitPop(6);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboCtrlHou[i] = CharToBoolean(PopChar());
  }

  SaveFile(&flCtrlHou);

  Result(bRES_OK);
}



void    OutGetRecalcHou(void)
{
  InitPushCRC();
  PushBool(boRecalcAlways);
  Push(&mpboRecalcHou, sizeof(mpboRecalcHou));
  Output(1+48);
}


void    OutSetRecalcHou1(void)
{
  InitPop(6);

  boRecalcAlways = CharToBoolean(PopChar());
  SaveCache(&chRecalcAlways);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboRecalcHou[i] = CharToBoolean(PopChar());
  }

  SaveFile(&flRecalcHou);

  Result(bRES_OK);
}


void    OutSetRecalcHou2(void)
{
  InitPop(6);

  PopChar();

  uchar i;
  for (i=0; i<48; i++)
  {
    mpboRecalcHou[i] = CharToBoolean(PopChar());
  }

  SaveFile(&flRecalcHou);

  Result(bRES_OK);
}
