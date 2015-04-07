/*------------------------------------------------------------------------------
EXTENDED_5_C.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "delay.h"
#include        "ports.h"
#include        "engine.h"
#include        "energy.h"
#include        "keyboard.h"
#include        "device_c.h"
#include        "_automatic1.h"



void    QueryEnergyDayTariffC(uchar  bTariff)
{
  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(2);

  PushChar(0);
  PushChar(bTariff);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


void    QueryEnergyAbsTariffC(uchar  bTariff)
{
  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(3);
  PushChar(1);

  PushChar(0);
  PushChar(bTariff);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


bit     QueryEnergyDayTariffC_Full(uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyDayTariffC(bTariff);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyC();
  return(1);
}


bit     QueryEnergyAbsTariffC_Full(uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsTariffC(bTariff);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyC();
  return(1);
}


bit     ReadCntAbsTariffC(uchar  bTariff)                 
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceC() == 0) return(0);


  if (QueryEnergyDayTariffC_Full(bTariff) == 0) return(0);  
  ShowPercent(60+bTariff);
  for (i=0; i<4; i++)
  {
    dwBuffC = *PGetCanLong(mpdwChannelsA, i);
    SetCanLong(mpdwChannelsB, i);
  }

  if (QueryEnergyAbsTariffC_Full(bTariff) == 0) return(0);             
  ShowPercent(80+bTariff);
  for (i=0; i<4; i++)
  {
    dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
    dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

    SetCanLong(mpdwChannelsB, i);
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    reBuffA = *PGetCanLong(mpdwChannelsB, i) * reBuffB;

    SetCanReal(mpreChannelsB, i);
    mpboChannelsA[i] = boTrue;     
  }

  return(1);
}
*/
