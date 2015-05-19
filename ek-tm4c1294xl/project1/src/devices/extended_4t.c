/*------------------------------------------------------------------------------
EXTENDED_4T.C

 «начени€ счетчиков на начало мес€цев по тарифам (oтчет є86с от 07.04.2013)
------------------------------------------------------------------------------*/

#include "../console.h"
#include "../memory/mem_realtime.h"
#include "../serial/ports.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_display.h"
#include "../digitals/digitals_messages.h"
#include "../devices/devices.h"
#include "../sensors/automatic_p.h"
#include "../sensors/automatic3.h"
#include "../time/rtc.h"
#include "../time/timedate.h"
#include "extended_4t.h"



file const              flExt4TFlag = {EXT_4T_FLAG, &boExt4TFlag, sizeof(boolean)};
file const              flExt4TMonths = {EXT_4T_MONTHS, &bExt4TMonths, sizeof(uchar)};


//                                         0123456789ABCDEF
static char const       szExtended4T[]  = "ќпрос данных: 6 ";



boolean SaveExt4TValues(uchar  ibMon)
{
  return SaveBuff(EXT_4T_MON_VALUES + ibMon*VALUE4T_CAN_PAGES, &mpCntMonCan4T, sizeof(mpCntMonCan4T));
}


boolean LoadExt4TValues(uchar  ibMon)
{
  return LoadBuff(EXT_4T_MON_VALUES + ibMon*VALUE4T_CAN_PAGES, &mpCntMonCan4T, sizeof(mpCntMonCan4T));
}



void    InitExtended4T(void) 
{
  LoadFileBoolean(&flExt4TFlag, FALSE);
  LoadFileChar(&flExt4TMonths, 1, 12, 4);
}


void    ResetExtended4T(bool  fFull)
{ 
  if (fFull)
  {
    boExt4TFlag = FALSE;
    SaveFile(&flExt4TFlag);

    bExt4TMonths = 4;
    SaveFile(&flExt4TMonths);
  }


  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4TValues(m);
  }
}



void    ResetExtended4T_Full(void) 
{ 
  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4TValues(m);
  }
}


void    ResetExtended4T_Custom(uchar  ibCanMin, uchar  ibCanMax, uchar  ibMonMin, uchar  ibMonMax)
{ 
  uchar m;
  for (m=ibMonMin; m<=ibMonMax; m++)
  {
    LoadExt4TValues(m);

    uchar c;
    for (c=ibCanMin; c<=ibCanMax; c++)
    {
      memset(&mpCntMonCan4T[c], 0, sizeof(value6t));
    }

    SaveExt4TValues(m);
  }
}



void    NextMonExtended4T(void) 
{
  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));
  SaveExt4TValues(ibHardMon);
}



static bool MakeDevices(uchar  ibMon, uchar  ibTrf)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  

  status st = ReadCntMonCanTariff(ibMon, ibDig, ibTrf);

  if ((st == ST4_BADDIGITAL) || (st == ST4_NOTSUPPORTED) || (st == ST4_NOTPRESENTED)) 
  { 
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        value6t va = mpCntMonCan4T[c];

        va.bStatus = st;
        va.mpdbValues[ibTrf] = 0;
        va.tiUpdate = *GetCurrTimeDate();

        mpCntMonCan4T[c] = va;
      }
    }

    if (st == ST4_BADDIGITAL) { ShowLo(szNoLink); DelayInf(); }
    return false;
  }
  else
  { 
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == TRUE)
        {
          value6t va = mpCntMonCan4T[c];

          va.bStatus = ST4_OK;
          va.mpdbValues[ibTrf] = mpdbChannelsC[diPrev.ibLine];
          va.tiUpdate = *GetCurrTimeDate();

          mpCntMonCan4T[c] = va;
        }
      }
    }

    return true;
  }
}



void    MakeExtended4T(void)
{
  if ((boExt4TFlag == TRUE) && (mpboExt4EnblCan[ibDig] == TRUE))
  {
    ShowHi(szExtended4T); 
    Clear(); sprintf(szLo+3,"глубина: %u", bExt4TMonths);
    DelayInf();

    ibMonthP = 0xFF;

    uchar m;
    for (m=0; m<bExt4TMonths; m++)
    {
      if (fKey == true) break;

      uchar ibMon = (bMONTHS + ibHardMon - m) % bMONTHS;
      LoadExt4TValues(ibMon);

      status bStatus = mpCntMonCan4T[ibDig].bStatus;
      if ((bStatus == ST4_OK) || (bStatus == ST4_NOTPRESENTED)) continue;

      uchar t;
      for (t=0; t<bTARIFFS; t++)
      {
        Clear(); sprintf(szLo+3,"мес€ц: %-2u",ibMon+1); sprintf(szLo+14,"T%u",t+1); DelayInf();

        if (MakeDevices(ibMon, t) == 0) break;
        ibMonthP = ibMon;
      }

      SaveExt4TValues(ibMon);
    }

    ShowCanalNumber(ibDig);
    Clear();
  }
}



uint    PushData4T(uchar  ibCan, bool  fDouble)
{
  if (SupportedCntMonCanTariff(ibCan) == false)
  {
    uint wSize = 0;
    wSize += PushChar(ST4_NOTSUPPORTED);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
    {
      wSize += PushFloatOrDouble(0, fDouble);
    }

    wSize += PushTime(tiZero);
    return wSize;
  }
  else
  {
    value6t va = mpCntMonCan4T[ibCan];

    uint wSize = 0;
    wSize += PushChar(va.bStatus);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
    {
      wSize += PushFloatOrDouble(va.mpdbValues[t], fDouble);
    }

    wSize += PushTime(va.tiUpdate);
    return wSize;
  }
}



void    OutExtended4T(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();

    uint wSize = 0;

    wSize += PushChar(boExt4TFlag);
    wSize += PushChar(bExt4TMonths);

    LoadExt4TValues(InBuff(6));

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        wSize += PushData4T(c, fDouble);
      }
    }

    OutptrOutBuff(wSize);
  }
}
