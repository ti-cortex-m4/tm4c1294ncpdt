/*------------------------------------------------------------------------------
AUTOMATIC_C.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../digitals/digitals_messages.h"
#include "../engine.h"
#include "automatic1.h"
#include "device_c.h"



#ifndef SKIP_C

bool    QueryIdC_Full(void)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryIdC();

    if ((RevInput() == SER_GOODCHECK) && (ReadIdC() == 1)) break;
    if (fKey == true) return false;

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (i == bMINORREPEATS) return false;

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
    if (fKey == true) return false;

    if (QueryIdC_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
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
    if (fKey == true) return false;

    if (QueryIdC_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
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
    if (fKey == true) return false;

    if (QueryIdC_Full() == 0) return false;
  }

  if (i == bMINORREPEATS) return false;
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
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadTimeAltC();
  return(1);
}



static void QueryCntMonTariffC(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);
  PushChar(43);

  PushChar(ibMon);
  PushChar(bTrf);
  PushChar(0);

  RevQueryIO(4+16+2, 3+3+2);
}


static bool QueryCntMonTariffC_Full(uchar  ibMon, uchar  bTrf) // на начало мес€ца
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryCntMonTariffC(ibMon, bTrf);

    if (RevInput() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyC();
  return true;
}


status ReadCntMonCanTariffC(uchar  ibMon, uchar  ibTrf) // на начало мес€ца
{ 
  Clear();
  if (ReadKoeffDeviceC() == 0) return ST4_BADDIGITAL;

  float flK = reKtrans/reKpulse;


  if (QueryTimeC_Full() == 0) return ST4_BADDIGITAL;

  uchar m = (ibMon + 0)%12;
  if (QueryCntMonTariffC_Full(-((12-1+tiAlt.bMonth-m)%12), ibTrf+1) == 0) return ST4_BADDIGITAL;

  ShowPercent(60+ibTrf);


  uchar i;
  for (i=0; i<4; i++) 
  {
  	mpdbChannelsC[i] = mpdwChannelsA[i] * flK;
    mpboChannelsA[i] = TRUE;     
  }

  return ST4_OK;
}

#endif
