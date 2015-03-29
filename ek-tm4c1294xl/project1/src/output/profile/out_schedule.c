/*------------------------------------------------------------------------------
OUT_SCHEDULE.C
                    

------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_schedule.h"
#include        "../../serial/ports.h"
#include        "../../digitals/schedule/schedule.h"
#include        "../../flash/files.h"



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
      mpboEnblPrtHou[bInBuff6][i] = (PopChar() == TRUE ? TRUE : FALSE);

    SaveFile(&flEnblPrtHou);

    LongResult(bRES_OK);
  }
  else
    Result(bRES_BADADDRESS);
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
    mpboCtrlHou[i] = (PopChar() == TRUE ? TRUE : FALSE);

  SaveFile(&flCtrlHou);

  Result(bRES_OK);
}



void    OutGetRecalcHou(void)
{
  InitPushCRC();
  PushChar(boRecalcAlways);
  Push(&mpboRecalcHou, sizeof(mpboRecalcHou));
  Output(1+48);
}


void    OutSetRecalcHou1(void)
{
  InitPop(6);

  boRecalcAlways = (PopChar() == TRUE ? TRUE : FALSE);
  SaveFile(&flRecalcAlways);

  uchar i;
  for (i=0; i<48; i++)
    mpboRecalcHou[i] = (PopChar() == TRUE ? TRUE : FALSE);

  SaveFile(&flRecalcHou);

  Result(bRES_OK);
}


void    OutSetRecalcHou2(void)
{
  InitPop(6);

  PopChar();

  uchar i;
  for (i=0; i<48; i++)
    mpboRecalcHou[i] = (PopChar() == TRUE ? TRUE : FALSE);

  SaveFile(&flRecalcHou);

  Result(bRES_OK);
}
