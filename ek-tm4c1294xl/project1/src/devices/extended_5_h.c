/*------------------------------------------------------------------------------
EXTENDED_5_H.C


------------------------------------------------------------------------------*/
/*
#include "main.h"
#include "xdata.h"
#include "display.h"
#include "delay.h"
#include "ports.h"
#include "engine.h"
#include "energy.h"
#include "general.h"
#include "nexttime.h"
#include "keyboard.h"
#include "digitals.h"
#include "device_h.h"
#include "_automatic1.h"



bit     ReadOpenH_X5(uchar  bTariff)
{     
  InitPop(3);

  bVersionCod = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  if (bTariff == 1)
  {
    sprintf(szLo,"   версия: %2bu   ",bVersionCod);
    DelayInf(); Clear();
  }

  if ((bVersionCod == 23) || (bVersionCod == 45) ||
      (bVersionCod == 25) || (bVersionCod == 47) ||
      (bVersionCod == 16) ||
      (bVersionCod == 30) || 
      (bVersionCod == 43)) return(1);

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return(0);
}


bit     QueryOpenDeviceH_X5(uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  if (ReadOpenH_X5(bTariff) == 0) return(0);

  return(1);
}


bit     QueryEnergyAbsTariffH_Full(uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsH(bTariff-1);

    if (CodInput() == SER_GOODCHECK) break;  
    if (fKey == true) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  if (ChecksumH(14) == 0) { sprintf(szLo," ошибка CRC: H8 "); Delay(1000); return(0); }

  InitPop(3);
  PopLongH();
  mpreChannelsB[0] = (real)dwBuffC/1000;

  return(1);
}


bit     ReadCntAbsTariffH(uchar  bTariff)
{ 
uchar   i;

  if (QueryOpenDeviceH_X5(bTariff) == 0) return(0);

  if (QueryEnergyAbsTariffH_Full(bTariff) == 0) return(0);  

  ShowPercent(60+bTariff);
  DelayInf();

 
  // энергия за текущие сутки рассчитывается, а не запрашивается со счётчика (как должно быть) !
  LoadImpDay(ibHardDay);

  i = 0x01 << (bTariff-1);
  reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,i);      // по тарифам
  reBuffA = reBuffA / mpreTransEng[ibDig];

  reBuffA = mpreChannelsB[0] * mpreTransCnt[ibDig] - reBuffA;
  mpreChannelsB[0] = reBuffA;
  mpboChannelsA[0] = TRUE;     


  return(1);
}
*/
