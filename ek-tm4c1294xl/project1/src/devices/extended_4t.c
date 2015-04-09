/*------------------------------------------------------------------------------
EXTENDED_4T.C

 «начени€ счетчиков по тарифам на Ќј„јЋќ мес€ца
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "rtc.h"
#include        "delay.h"
#include        "display.h"
#include        "timedate.h"
#include        "engine.h"
#include        "sensors.h"
#include        "ports.h"
#include        "queries.h"
#include        "keyboard.h"
#include        "automatic3.h"



//                                         0123456789ABCDEF
message         code    szExtended4T    = "ќпрос данных: 6 ";

extern	message         code    szNoLink;



void    InitExtended4T(void) 
{ 
  if ((bExt4TMonths <= 0) || (bExt4TMonths > 12))
    bExt4TMonths = 4;
}



void    ResetExtended4T(void) 
{ 
  boExt4TFlag = boFalse;
  bExt4TMonths = 4;

  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));
}


void    ResetExtended4T1(void) 
{ 
  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));
}


void    ResetExtended4T2(uchar  ibMonth, uchar  ibCanal) 
{ 
  memset(&mpCntMonCan4T[ibMonth][ibCanal], 0, sizeof(value6t));
}



void    NextMonExtended4T(void) 
{
  memset(&mpCntMonCan4T[ibHardMon], 0, sizeof(value6t)*bCANALS);
}



bit     MakeSimple4T(uchar	ibTariff)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  

  ibX = ReadCntMonCanTariff(ibMon, ibDig, ibTariff);

  if ((ibX == ST4_BADDIGITAL) || (ibX == ST4_NOTSUPPORTED) || (ibX == ST4_NOTPRESENTED)) 
  { 
    LoadCurrDigital(ibDig);      
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        v6tBuff = mpCntMonCan4T[ibMon][ibCan];

        v6tBuff.bSelf = ibX;
        v6tBuff.mpreSelf[ibTariff] = 0;

        v6tBuff.tiSelf = *PGetCurrTimeDate();
        mpCntMonCan4T[ibMon][ibCan] = v6tBuff;
      }
    }

    if (ibX == ST4_BADDIGITAL) { ShowLo(szNoLink); DelayInf(); }
    return (0);
  }
  else
  { 
    LoadCurrDigital(ibDig);      
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1)
      {
        if (mpboChannelsA[diPrev.ibLine] == boTrue)
        {
          v6tBuff = mpCntMonCan4T[ibMon][ibCan];

          v6tBuff.bSelf = ST4_OK;
          v6tBuff.mpreSelf[ibTariff] = mpreChannelsB[diPrev.ibLine];

          v6tBuff.tiSelf = *PGetCurrTimeDate();
          mpCntMonCan4T[ibMon][ibCan] = v6tBuff;
        }
      }
    }

    return (1);
  }
}



void    MakeExtended4T(void)
{
uchar   i,j;

  if ((boExt4TFlag == boTrue) && (mpEnblCan4[ibDig] == boTrue))
  {
    ShowHi(szExtended4T); 
    Clear(); sprintf(szLo+3,"глубина: %bu", bExt4TMonths); DelayInf();
    ibMinor = 0xFF;

    for (i=0; i<bExt4TMonths; i++)
    {
      if (fKey == 1) break;

      ibMon = (bMONTHS + ibHardMon - i) % bMONTHS;

      v6tBuff = mpCntMonCan4T[ibMon][ibDig];
      if ((v6tBuff.bSelf == ST4_OK) || (v6tBuff.bSelf == ST4_NOTPRESENTED)) continue;

      for (j=0; j<bTARIFFS; j++)
      {
        Clear(); sprintf(szLo+3,"мес€ц: %-2bu",ibMon+1); sprintf(szLo+14,"T%bu",j+1); DelayInf();
        if (MakeSimple4T(j) == 0) break;
        ibMinor = ibMon;
      }
    }

    ShowDigitalHi(); Clear();
  }
}



#ifndef MODBUS

void    PushData4T(uchar  ibCanal, uchar  ibMonth)
{
  if (IsCntMonCanTariff(ibCanal) == 0)
  {
    PushChar(ST4_NOTSUPPORTED);
    reBuffA = 0; 
    PushReal();
    PushReal();
    PushReal();
    PushReal();
    Push(&tiZero, sizeof(time));
  }
  else
  {
    v6tBuff = mpCntMonCan4T[ibMonth][ibCanal]; 
    PushChar(v6tBuff.bSelf);
    Push(&v6tBuff.mpreSelf, sizeof(real)*bTARIFFS);
    Push(&v6tBuff.tiSelf, sizeof(time));
  }
}



void    OutExtended40T(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    InitPushPtr();            
    PushChar(boExt4TFlag);
    PushChar(bExt4TMonths);
    wBuffD = 1+1;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(7 + i/8) & (0x80 >> i%8)) != 0) 
      {
        PushData4T(i, InBuff(6));
        wBuffD += (1+4*4+6);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}

#endif
*/
