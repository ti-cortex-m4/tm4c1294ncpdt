/*------------------------------------------------------------------------------
EXTENDED_5.C

 Значения счетчиков на начало текущих суток по тарифам (отчет № 18a от 01.02.2008)
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_profile.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_display.h"
#include "../devices/devices.h"
#include "../serial/ports.h"
#include "../time/rtc.h"
#include "../console.h"
#include "extended_5_a.h"
#include "extended_5_b.h"
#include "extended_5_c.h"
#include "extended_5.h"



file const              flExt5Flag = {EXT_5_FLAG, &boExt5Flag, sizeof(boolean)};
file const              flExt5Values = {EXT_5_VALUES, &mpCntDayCan5, sizeof(mpCntDayCan5)};


//                                         0123456789ABCDEF
static char const       szExtended5[]   = "Опрос данных: 5 ";



static buff5            vaBuff[4];



void    InitExtended5(void)
{
  LoadFile(&flExt5Flag);
  LoadFile(&flExt5Values);
}


void    ResetExtended5(void)
{
  boExt5Flag = FALSE;
  SaveFile(&flExt5Flag);

  memset(&mpCntDayCan5, 0, sizeof(mpCntDayCan5));
  SaveFile(&flExt5Values);
}



void    NextDayExtended5(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpCntDayCan5[c].boSuccess = FALSE;
  }

  SaveFile(&flExt5Values);
}



bool    ReadCntAbsTariff(uchar  ibCanal, uchar  bTariff)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return( ReadCntAbsTariffA(bTariff) );
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadCntAbsTariffB(bTariff) );
#endif

#ifndef SKIP_C
    case 3:  return( ReadCntAbsTariffC(bTariff) );
#endif

#ifndef SKIP_H
    case 10: return( ReadCntAbsTariffH(bTariff) );
#endif

    default: return 0;
  }
}


static bool MakeDevices(void)
{
  memset(&vaBuff, 0, sizeof(vaBuff));  

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    if (fKey == true) return false;
    Clear();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));

    if (ReadCntAbsTariff(ibDig,t+1) == 0) return (0);

    uchar i;
    for (i=0; i<4; i++)
    {
      vaBuff[i].mpdbValuesT[t] = mpreChannelsB[i];
    }
  }

  return true;
}


void    MakeExtended5(void)
{ 
  if ((boExt5Flag == TRUE) && ((mpCntDayCan5[ibDig].boSuccess == FALSE) || (boManualProfile == TRUE)))
  {
    ShowHi(szExtended5); Clear();
   
    if (MakeDevices() == true)
    {
      LoadCurrDigital(ibDig);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        LoadPrevDigital(c);
        if (CompareCurrPrevLines(ibDig, c) == 1)
        {
          mpCntDayCan5[c].cwSuccess++;
          mpCntDayCan5[c].tiUpdate = *GetCurrTimeDate();
          mpCntDayCan5[c].vaValue5 = vaBuff[diPrev.ibLine];
          mpCntDayCan5[c].boSuccess = TRUE;
        }
      }
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
          mpCntDayCan5[c].cwError++;
        }
      }

      Error(); DelayInf();
    }

    SaveFile(&flExt5Values);

    ShowCanalNumber(ibDig);
    Clear();
  }
}



void    OutExtended50(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();

    uint wSize = 0;

    wSize += PushChar(boExt5Flag);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        value5 va = mpCntDayCan5[c];

        uchar t;
        for (t=0; t<bTARIFFS; t++)
        {
          wSize += PushFloat(va.vaValue5.mpdbValuesT[t]);
        }

        wSize += PushTime(va.tiUpdate);

        wSize += PushChar(va.boSuccess);

        wSize += PushInt(va.cwSuccess);
        wSize += PushInt(va.cwError);
      }
    }

    OutptrOutBuff(wSize);
  }
}


void    OutExtended51(void)
{

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();

    uint wSize = 0;

    wSize += PushChar(boExt5Flag);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        value5 va = mpCntDayCan5[c];

        uchar t;
        for (t=0; t<bTARIFFS; t++)
        {
          wSize += PushFloat(va.vaValue5.mpdbValuesT[t]);
        }

        wSize += PushTime(va.tiUpdate);
      }
    }

    OutptrOutBuff(wSize);
  }
}
