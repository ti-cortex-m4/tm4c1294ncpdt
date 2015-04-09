/*------------------------------------------------------------------------------
EXTENDED_4T.C

 «начени€ счетчиков по тарифам на Ќј„јЋќ мес€ца
------------------------------------------------------------------------------*/

#include        "../console.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_profile.h"
#include        "../serial/ports.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/digitals_messages.h"
#include        "../devices/devices.h"
#include        "../sensors/automatic3.h"
#include        "../time/rtc.h"
#include        "extended_4t.h"



file const              flExt4TFlag = {FLS_EXT_4T_FLAG, &boExt4TFlag, sizeof(boolean)};
file const              flExt4TMonths = {FLS_EXT_4T_MONTHS, &bExt4TMonths, sizeof(uchar)};



//                                         0123456789ABCDEF
static char const       szExtended4T[]  = "ќпрос данных: 6 ";


static value6t          vaBuff;



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

/*
void    ResetExtended4T1(void) 
{ 
  memset(&mpCntMonCan4T_, 0, sizeof(mpCntMonCan4T_));
}


void    ResetExtended4T2(uchar  ibMonth, uchar  ibCanal) 
{ 
  memset(&mpCntMonCan4T_[ibMonth][ibCanal], 0, sizeof(value6t));
}



void    NextMonExtended4T(void) 
{
  memset(&mpCntMonCan4T_[ibHardMon], 0, sizeof(value6t)*bCANALS);
}
*/


bool    MakeSimple4T(uchar  ibMon, uchar  ibTariff)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  

  status4 st = ReadCntMonCanTariff(ibMon, ibDig, ibTariff);

  if ((st == ST4_BADDIGITAL) || (st == ST4_NOTSUPPORTED) || (st == ST4_NOTPRESENTED)) 
  { 
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == 1)
      {
        vaBuff = mpCntMonCan4T_[ibMon][c];

        vaBuff.bSelf = st;
        vaBuff.mpreSelf[ibTariff] = 0;

        vaBuff.tiSelf = *GetCurrTimeDate();
        mpCntMonCan4T_[ibMon][c] = vaBuff;
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
          vaBuff = mpCntMonCan4T_[ibMon][c];

          vaBuff.bSelf = ST4_OK;
          vaBuff.mpreSelf[ibTariff] = mpreChannelsB[diPrev.ibLine];

          vaBuff.tiSelf = *GetCurrTimeDate();
          mpCntMonCan4T_[ibMon][c] = vaBuff;
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
    ibMinor = 0xFF; // TODO ReadCntMonCanTariffP

    uchar m;
    for (m=0; m<bExt4TMonths; m++)
    {
      if (fKey == 1) break;

      uchar ibMon = (bMONTHS + ibHardMon - m) % bMONTHS;

      vaBuff = mpCntMonCan4T_[ibMon][ibDig];
      if ((vaBuff.bSelf == ST4_OK) || (vaBuff.bSelf == ST4_NOTPRESENTED)) continue;

      uchar t;
      for (t=0; t<bTARIFFS; t++)
      {
        Clear(); sprintf(szLo+3,"мес€ц: %-2u",ibMon+1); sprintf(szLo+14,"T%u",t+1); DelayInf();
        if (MakeSimple4T(ibMon, t) == 0) break;
        ibMinor = ibMon;
      }
    }

    ShowCanalNumber(ibDig);
    Clear();
  }
}



void    PushData4T(uchar  ibCanal, uchar  ibMonth)
{
  if (IsCntMonCanTariff(ibCanal) == 0)
  {
    PushChar(ST4_NOTSUPPORTED);
    real re = 0;
    PushFloat(re);
    PushFloat(re);
    PushFloat(re);
    PushFloat(re);
    PushTime(&tiZero);
  }
  else
  {
    v6tBuff = mpCntMonCan4T_[ibMonth][ibCanal]; 
    PushChar(v6tBuff.bSelf);
    Push(&v6tBuff.mpreSelf, sizeof(real)*bTARIFFS);
    PushTime(&v6tBuff.tiSelf);
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

   uchar c;
   for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        PushData4T(c, InBuff(6));
        wSize += (1+4*4+6);
      }
    }

    OutptrOutBuff(wSize);
  }
}
