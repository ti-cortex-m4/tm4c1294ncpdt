/*------------------------------------------------------------------------------
EXPANSION_CRC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../response_crc.h"
#include "expansion_crc.h"



bool    IsExpansionCrc(void)
{
  return false;
}


bool    UseExpansionCrc(void)
{
  return false;
}


bool    CheckExpansionCrcRequest(void)
{
  InitPop(IndexInBuff() - 11);

  uchar bExpansionCRC = PopChar();
  if (bExpansionCRC != 0)
  {
    ShowResponseCRC(bSTA_BADSIZE);
    Result(bRES_BADSIZE);
    return false;
  }

  time tiExpansionCRC = PopTime();
  if (!ValidTimeDate(tiExpansionCRC))
  {
    ShowResponseCRC(bSTA_BADSIZE);
    Result(bRES_BADSIZE);
    return false;
  }

  uint wExpansionCRC = PopInt();

  return true;
}


void    PushExpansionCrcResponse(void)
{
  PushChar(0);
  PushTime(*GetCurrTimeDate());
  PuchInt(wExpansionCRC);
}


uchar   ExpansionCrcResponseSize(void)
{
  return UseExpansionCrc() ? 1 + 6 + 2 : 0;
}
