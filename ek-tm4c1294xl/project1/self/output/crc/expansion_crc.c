/*------------------------------------------------------------------------------
EXPANSION_CRC.C


------------------------------------------------------------------------------*/
/*
#include "../../main.h"
#include "../../serial/ports.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../response_crc.h"
#include "expansion_crc.h"



static uchar            bExpansionCrc;

static time             tiExpansionCrc;

static uint             wExpansionCrc;



bool    UseExpansionCrc(void)
{
  return false;
}


bool    CheckExpansionCrcRequest(void)
{
  InitPop(IndexInBuff() - 11);

  bExpansionCrc = PopChar();
  if (bExpansionCrc != 0)
  {
    ShowResponseCRC(bSTA_BADSIZE);
    Result(bRES_BADSIZE);
    return false;
  }

  tiExpansionCrc = PopTime();
  if (!ValidTimeDate(tiExpansionCrc))
  {
    ShowResponseCRC(bSTA_BADSIZE);
    Result(bRES_BADSIZE);
    return false;
  }

  wExpansionCrc = PopInt();

  return true;
}


void    PushExpansionCrcResponse(void)
{
  PushChar(0);
  PushTime(*GetCurrTimeDate());
  PushInt(wExpansionCrc);
}


uchar   ExpansionCrcResponseSize(void)
{
  return UseExpansionCrc() ? 1 + 6 + 2 : 0;
}
*/
