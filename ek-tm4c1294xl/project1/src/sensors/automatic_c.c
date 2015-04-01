/*------------------------------------------------------------------------------
AUTOMATIC_CS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../time/delay.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "../devices/devices.h"
#include        "../digitals/digitals_messages.h"
#include        "device_c.h"



bool    QueryIdC_Full(void)
{
  for (x=0; x<bMINORREPEATS; x++)
  {
    DelayOff();
    QueryIdC();

    if ((RevInput() == SER_GOODCHECK) && (ReadIdC() == 1)) break;
    if (fKey == 1) return(0);

    ShowLo(szFailure20); Delay(1000);
    mpcwFailure2[ibDig]++;
  }

  Clear();
  if (x == bMINORREPEATS) return(0);

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

/*
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
*/
