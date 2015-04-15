/*------------------------------------------------------------------------------
EXTENDED_5.C

 Cчетчики (раздельно по тарифам) на начало текущих суток
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_extended_5.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../devices/devices.h"
#include        "../serial/ports.h"
#include        "../time/rtc.h"
#include        "../console.h"
#include        "extended_5_b.h"
#include        "extended_5_c.h"
#include        "extended_5.h"



//                                         0123456789ABCDEF
static char const       szExtended5[]   = "Опрос данных: 5 ";


file const              flExt5Flag = {EXT_5_FLAG, &boExt5Flag, sizeof(boolean)};
file const              flExt5Values = {EXT_5_VALUES, &mpvaValue5, sizeof(mpvaValue5)};


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

  memset(&mpvaValue5, 0, sizeof(mpvaValue5));
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
    if (fKey == 1) return (0);
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
  if ((boExt5Flag == TRUE) && ((mpvaValue5[ibDig].boSelf == FALSE) || (boManualProfile == TRUE)))
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
          mpvaValue5[c].cwOK++;
          mpvaValue5[c].tiSelf = *GetCurrTimeDate();
          mpvaValue5[c].vaValue5 = vaBuff[diPrev.ibLine];
          mpvaValue5[c].boSelf = TRUE;
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
          mpvaValue5[c].cwError++;
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
    mpvaValue5[c].boSelf = FALSE;
  }

  SaveFile(&flExt5Values);
}


void    CloseExtended5(void)
{
  SaveFile(&flExt5Values);
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
        Push(&mpvaValue5[c], sizeof(value5));
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
        Push(&mpvaValue5[c].vaValue5, sizeof(buff5));
        wSize += sizeof(buff5);
        Push(&mpvaValue5[c].tiSelf, sizeof(time));
        wSize += sizeof(time);
      }
    }

    OutptrOutBuff(wSize);
  }
}
