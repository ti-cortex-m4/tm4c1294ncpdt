/*------------------------------------------------------------------------------
EXTENDED_4T.C

 «начени€ счетчиков на Ќј„јЋќ мес€цев (по тарифам)
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


static value6t          vaT;



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
  boExt4TFlag = FALSE;
  SaveFile(&flExt4TFlag);

  bExt4TMonths = 4;
  SaveFile(&flExt4TMonths);


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
        vaT = mpCntMonCan4T[c];

        vaT.bStatus = st;
        vaT.mpdbValues[ibTrf] = 0;
        vaT.tiUpdate = *GetCurrTimeDate();

        mpCntMonCan4T[c] = vaT;
      }
    }

    if (st == ST4_BADDIGITAL) { ShowLo(szNoLink); DelayInf(); }
    return (0);
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
          vaT = mpCntMonCan4T[c];

          vaT.bStatus = ST4_OK;
          vaT.mpdbValues[ibTrf] = mpdbChannelsC[diPrev.ibLine];
          vaT.tiUpdate = *GetCurrTimeDate();

          mpCntMonCan4T[c] = vaT;
        }
      }
    }

    return (1);
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

      vaT = mpCntMonCan4T[ibDig];
      if ((vaT.bStatus == ST4_OK) || (vaT.bStatus == ST4_NOTPRESENTED)) continue;

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



void    PushData4T(uchar  ibCan)
{
  if (SupportedCntMonCanTariff(ibCan) == false)
  {
    PushChar(ST4_NOTSUPPORTED);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
      PushFloat(0);

    PushTime(tiZero);
  }
  else
  {
    value6t va = mpCntMonCan4T[ibCan];

    PushChar(va.bStatus);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
      PushFloat(va.mpdbValues[t]);

    PushTime(va.tiUpdate);
  }
}



void    OutExtended4T(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();            
    PushChar(boExt4TFlag);
    PushChar(bExt4TMonths);
    uint wSize = 1+1;

    LoadExt4TValues(InBuff(6));

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        PushData4T(c);
        wSize += (1+4*4+6);
      }
    }

    OutptrOutBuff(wSize);
  }
}
