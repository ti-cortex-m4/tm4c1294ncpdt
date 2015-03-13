/*------------------------------------------------------------------------------
AUTOMATIC_B.C


------------------------------------------------------------------------------*/
/*
#include        "main.h" 
#include        "xdata.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "delay.h"
#include        "engine.h"
#include        "energy.h"
#include        "ports.h"
#include        "device_b.h"
#include        "_automatic1.h"



void    QueryCounterMonTariffB(uchar  ibMonth, uchar  bTariff) // на начало мес€ца
{
uint    i;

  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(6);
  PushChar(2);

  i = 0x2BB + 0x55*ibMonth + 0x11*bTariff;
  PushChar(i / 0x100);
  PushChar(i % 0x100);
  PushChar(16);

  QueryIO(1+16+2, 3+3+2);
}


bit     QueryCounterMonTariffB_Full(uchar  ibMonth, uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryCounterMonTariffB(ibMonth, bTariff);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyB();
  return(1);
}


status4 ReadCntMonCanTariffB(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceB() == 0) return(ST4_BADDIGITAL);

  if (QueryCounterMonTariffB_Full(ibMonth, ibTariff) == 0) return(ST4_BADDIGITAL);  

  ShowPercent(60+ibTariff);
  for (i=0; i<4; i++)
  {
    dwBuffC = *PGetCanLong(mpdwChannelsA, i);
    SetCanLong(mpdwChannelsB, i);
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    reBuffA = *PGetCanLong(mpdwChannelsB, i) * reBuffB;

    SetCanReal(mpreChannelsB, i);
    mpboChannelsA[i] = boTrue;     
  }

  return(ST4_OK);
}
*/
