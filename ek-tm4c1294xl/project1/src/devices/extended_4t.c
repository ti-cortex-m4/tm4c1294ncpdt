/*------------------------------------------------------------------------------
EXTENDED_4T.C

 «начени€ счетчиков по тарифам на Ќј„јЋќ мес€ца
------------------------------------------------------------------------------*/

#include        "../console.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_extended_4.h"
#include        "../serial/ports.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
#include        "../sensors/automatic_p.h"
#include        "../sensors/automatic3.h"
#include        "../time/rtc.h"
#include        "../time/timedate.h"
#include        "extended_4t.h"



file const              flExt4TFlag = {FLS_EXT_4T_FLAG, &boExt4TFlag, sizeof(boolean)};
file const              flExt4TMonths = {FLS_EXT_4T_MONTHS, &bExt4TMonths, sizeof(uchar)};



//                                         0123456789ABCDEF
static char const       szExtended4T[]  = "ќпрос данных: 6 ";


static value6t          vaT;



static boolean SaveExt4TValues(uchar  ibMonth)
{
  return SaveBuff(FLS_EXT_4T_VALUES + ibMonth*VALUE6T_CAN_PAGES, &mpCntMonCan4T, sizeof(mpCntMonCan4T));
}


static boolean LoadExt4TValues(uchar  ibMonth)
{
  return LoadBuff(FLS_EXT_4T_VALUES + ibMonth*VALUE6T_CAN_PAGES, &mpCntMonCan4T, sizeof(mpCntMonCan4T));
}



void    InitExtended4T(void) 
{
  LoadFileBoolean(&flExt4TFlag, FALSE);
  LoadFileChar(&flExt4TMonths, 0, 12, 4);
}


void    ResetExtended4T(void) 
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



void    ResetExtended4T1(void) 
{ 
  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4TValues(m);
  }
}


void    ResetExtended4T2(uchar  ibCanMin, uchar  ibCanMax, uchar  ibMonMin, uchar  ibMonMax)
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



static bool MakeSimple4T(uchar  ibMon, uchar  ibTar)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  

  status4 st = ReadCntMonCanTariff(ibMon, ibDig, ibTar);

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

        vaT.bSelf = st;
        vaT.mpreSelf[ibTar] = 0;
        vaT.tiSelf = *GetCurrTimeDate();

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

          vaT.bSelf = ST4_OK;
          vaT.mpreSelf[ibTar] = mpreChannelsB[diPrev.ibLine];
          vaT.tiSelf = *GetCurrTimeDate();

          mpCntMonCan4T[c] = vaT;
        }
      }
    }

    return (1);
  }
}



void    MakeExtended4T(void)
{
  if ((boExt4TFlag == TRUE) && (mpEnblCan4[ibDig] == TRUE))
  {
    ShowHi(szExtended4T); 
    Clear(); sprintf(szLo+3,"глубина: %u", bExt4TMonths); DelayInf();
    ibMonthP = 0xFF;

    uchar m;
    for (m=0; m<bExt4TMonths; m++)
    {
      if (fKey == 1) break;

      uchar ibMonth = (bMONTHS + ibHardMon - m) % bMONTHS;
      LoadExt4TValues(ibMonth);

      vaT = mpCntMonCan4T[ibDig];
      if ((vaT.bSelf == ST4_OK) || (vaT.bSelf == ST4_NOTPRESENTED)) continue;

      uchar t;
      for (t=0; t<bTARIFFS; t++)
      {
        Clear(); sprintf(szLo+3,"мес€ц: %-2u",ibMonth+1); sprintf(szLo+14,"T%u",t+1); DelayInf();
        if (MakeSimple4T(ibMonth, t) == 0) break;
        ibMonthP = ibMonth;
      }

      SaveExt4TValues(ibMonth);
    }

    ShowCanalNumber(ibDig);
    Clear();
  }
}



void    PushData4T(uchar  ibCan)
{
  if (IsCntMonCanTariff(ibCan) == 0)
  {
    PushChar(ST4_NOTSUPPORTED);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
      PushFloat(0);

    PushTime((time *) &tiZero);
  }
  else
  {
    value6t va = mpCntMonCan4T[ibCan];

    PushChar(va.bSelf);

    uchar t;
    for (t=0; t<bTARIFFS; t++)
      PushFloat(va.mpreSelf[t]);

    PushTime(&va.tiSelf);
  }
}



void    OutExtended40T(void)
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
