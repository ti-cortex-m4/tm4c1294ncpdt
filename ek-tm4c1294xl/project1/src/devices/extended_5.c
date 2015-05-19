/*------------------------------------------------------------------------------
EXTENDED_5.C

 �������� ��������� �� ������ ������� ����� �� ������� (����� � 18a �� 01.02.2008)
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
static char const       szExtended5[]   = "����� ������: 5 ";



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
    if (fKey == true) return (0);
    Clear();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  
    if (ReadCntAbsTariff(ibDig,t+1) == 0) return (0);

    uchar i;
    for (i=0; i<4; i++)
    {
      vaBuff[i].mpreSelf[t] = mpreChannelsB[i];
    }
  }

  return (1);
}


void    MakeExtended5(void)
{ 
  if ((boExt5Flag == TRUE) && ((mpCntDayCan5[ibDig].boSelf == FALSE) || (boManualProfile == TRUE)))
  {
    ShowHi(szExtended5); Clear();
   
    if (MakeDevices() == 1)
    {
      LoadCurrDigital(ibDig);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        LoadPrevDigital(c);
        if (CompareCurrPrevLines(ibDig, c) == 1)
        {
          mpCntDayCan5[c].cwOK++;
          mpCntDayCan5[c].tiSelf = *GetCurrTimeDate();
          mpCntDayCan5[c].vaValue5 = vaBuff[diPrev.ibLine];
          mpCntDayCan5[c].boSelf = TRUE;
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

      Error();
      DelayInf();
    }  

    ShowCanalNumber(ibDig);
    Clear();
  }
}


void    NextDayExtended5(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpCntDayCan5[c].boSelf = FALSE;
  }

  SaveFile(&flExt5Values);
}


void    CloseExtended5(void)
{
  SaveFile(&flExt5Values);
}



uint    PushData5(uchar  ibCan)
{
  uint wSize = 0;

  value5 va = mpCntDayCan5[ibCan];

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    wSize += PushFloat(va.vaValue5.mpreSelf[t]);
  }

  wSize += PushTime(va.tiSelf);
  wSize += PushChar(va.boSelf);

  wSize += PushInt(va.cwOK);
  wSize += PushInt(va.cwError);

  return wSize;
}


void    OutExtended50(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    uint wSize = 1;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        Push(&mpCntDayCan5[c], sizeof(value5));
        wSize += sizeof(value5);
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
    PushChar(boExt5Flag);
    uint wSize = 1;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        Push(&mpCntDayCan5[c].vaValue5, sizeof(buff5));
        wSize += sizeof(buff5);
        Push(&mpCntDayCan5[c].tiSelf, sizeof(time));
        wSize += sizeof(time);
      }
    }

    OutptrOutBuff(wSize);
  }
}
