/*------------------------------------------------------------------------------
AUTOMATIC_U2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../automatic1.h"
#include "device_u.h"
#include "device_u2.h"
#include "automatic_u.h"
#include "automatic_u2.h"



#ifndef SKIP_U

bool    ReadEnergyDayDatesU_Full(void)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseU();
    QueryEnergyDayDatesU();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (r == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadEnergyDayDatesU();

  return(1);
}


bool    ReadEnergyMonDatesU_Full(void)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseU();
    QueryEnergyMonDatesU();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (r == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadEnergyMonDatesU();

  return(1);
}



bool    ReadEnergyMonTariffU_Full(time  ti, uchar  ibTariff, uchar  bMaxLines)
{
  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseU();
      QueryEngMonU(i,ti);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(70+i);

    ReadEnergyTariffU(i,ibTariff);
  }

  return(1);
}



status  ReadCntMonCanTariffU(uchar  ibMonth, uchar  ibTariff, uchar  bMaxLines) // на начало мес€ца
{
  time2 ti2 = ReadTimeCanU();
  if (ti2.fValid == 0) return ST_BADDIGITAL;

  time ti = ti2.tiValue;
  if (ibMonth == 0)
  {
    ti.bMonth = 12;
    ti.bYear--;
  }
  else
  {
    if (ibMonth+1 > ti.bMonth) ti.bYear--;
    ti.bMonth = ibMonth;
  }

  if (ReadEnergyMonDatesU_Full() == 0) return ST_BADDIGITAL;

  date dt;
  dt.bDay   = ti.bDay;
  dt.bMonth = ti.bMonth;
  dt.bYear  = ti.bYear;
  uchar bMon = IsMonAddedU(dt);

  if (bMon == 0)
  {
    Clear();
    sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
    Delay(1000);
    return(ST_NOTPRESENTED);
  }
  if (ReadEnergyMonTariffU_Full(ti,ibTariff,bMaxLines) == 0) return ST_BADDIGITAL;

  QueryCloseU();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}

#endif

