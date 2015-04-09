/*------------------------------------------------------------------------------
AUTOMATIC_C.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../time/delay.h"
#include        "../time/timedate.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "../devices/devices.h"
#include        "../digitals/digitals_messages.h"
#include        "../engine.h"
#include        "automatic1.h"
#include        "device_c.h"



#ifndef SKIP_C

bool    QueryIdC_Full(void)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryIdC();

    if ((RevInput() == SER_GOODCHECK) && (ReadIdC() == 1)) break;
    if (fKey == 1) return(0);

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == bMINORREPEATS) return(0);

  return(1);
}


bool    QueryEnergyDayC_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyDayC(bTime);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);

    if (QueryIdC_Full() == 0) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyC();
  return(1);
}


bool    QueryEnergyMonC_Full2(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyMonC(bTime);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);

    if (QueryIdC_Full() == 0) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyC();
  return(1);
}


bool    QueryEnergyAbsC_Full2(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsC();

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);

    if (QueryIdC_Full() == 0) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyC();
  return(1);
}


bool    QueryTimeC_Full(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeC();

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadTimeAltC();
  return(1);
}



bool    QueryCounterMonTariffC_Full(uchar  ibMonth, uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryCounterMonTariffC(ibMonth, bTariff);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyC();
  return(1);
}



status4 ReadCntMonCanTariffC(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
{ 
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceC() == 0) return(ST4_BADDIGITAL);

  if (QueryTimeC_Full() == 0) return(ST4_BADDIGITAL);  

  j = (ibMonth + 0)%12;
  if (QueryCounterMonTariffC_Full(-((12-1+tiAlt.bMonth-j)%12), ibTariff+1) == 0) return(ST4_BADDIGITAL);  

  ShowPercent(60+ibTariff);
  for (i=0; i<4; i++)
  {
    mpdwChannelsB[i] = mpdwChannelsA[i];
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    mpreChannelsB[i] = mpdwChannelsB[i] * reBuffB;
    mpboChannelsA[i] = TRUE;     
  }

  return(ST4_OK);
}

#endif
