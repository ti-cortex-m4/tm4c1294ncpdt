/*------------------------------------------------------------------------------
EXTENDED_5.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "rtc.h"
#include        "delay.h"
#include        "sensors.h"
#include        "ports.h"
#include        "queries.h"
#include        "engine.h"
#include        "keyboard.h"
#include        "extended_5_a.h"
#include        "extended_5_b.h"
#include        "extended_5_c.h"
#include        "extended_5_h.h"



//                                         0123456789ABCDEF
message         code    szExtended5     = "Опрос данных: 5 ";



bit     ReadCntAbsTariff(uchar  ibCanal, uchar  bTariff)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 15:
    case 1:  return( ReadCntAbsTariffA(bTariff) );  break;

    case 8:
    case 2:  return( ReadCntAbsTariffB(bTariff) );  break;

    case 3:  return( ReadCntAbsTariffC(bTariff) );  break;

    case 10: return( ReadCntAbsTariffH(bTariff) );  break;
  }
}


bit     CoreExtended5(void)
{
uchar i,j;

  memset(&mpvaValue50, 0, sizeof(mpvaValue50));  

  for (i=0; i<bTARIFFS; i++)
  {
    if (fKey == 1) return (0);
    Clear();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  
    if (ReadCntAbsTariff(ibDig,i+1) == 0) return (0);

    for (j=0; j<4; j++)
      mpvaValue50[j].mpreSelf[i] = mpreChannelsB[j];
  }

  return (1);
}


void    MakeExtended5(void)
{ 
  if ((boExt5Flag == TRUE) && ((mpvaValue51[ibDig].boSelf == boFalse) || (boManual == TRUE)))
  {
    ShowHi(szExtended5); Clear();
   
    if (CoreExtended5() == 1)
    {
      LoadCurrDigital(ibDig);      
      for (ibCan=0; ibCan<bCANALS; ibCan++)
      {
        LoadPrevDigital(ibCan);
        if (CompareCurrPrevLines() == 1)
        {
          mpvaValue51[ibCan].cwOK++;
          mpvaValue51[ibCan].tiSelf = *PGetCurrTimeDate();
          mpvaValue51[ibCan].vaValue50 = mpvaValue50[diPrev.ibLine];
          mpvaValue51[ibCan].boSelf = TRUE;
        }
      }
    }
    else
    {
      LoadCurrDigital(ibDig);      
      for (ibCan=0; ibCan<bCANALS; ibCan++)
      {
        LoadPrevDigital(ibCan);
        if (CompareCurrPrevLines() == 1)
        {
          mpvaValue51[ibCan].cwError++;
        }
      } 
      Error(); DelayInf();
    }  

    ShowDigitalHi(); Clear();
  }
}


void    NextDayExtended5(void)
{
  for (ibCan=0; ibCan<bCANALS; ibCan++)
    mpvaValue51[ibCan].boSelf = boFalse;
}


#ifndef MODBUS

void    OutExtended50(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    wBuffD = 1;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
      {
        Push(&mpvaValue51[i], sizeof(value51));
        wBuffD += sizeof(value51);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}


void    OutExtended51(void)
{
uchar   i;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    wBuffD = 1;

    for (i=0; i<bCANALS; i++)
    {
      if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0) 
      {
        Push(&mpvaValue51[i].vaValue50, sizeof(value50));
        wBuffD += sizeof(value50);
        Push(&mpvaValue51[i].tiSelf, sizeof(time));
        wBuffD += sizeof(time);
      }
    }

    OutptrOutBuff(wBuffD);
  }
}

#endif
*/
