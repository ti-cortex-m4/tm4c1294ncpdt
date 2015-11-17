/*------------------------------------------------------------------------------
AUTOMATIC_K!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "device_k.h"
#include "device_k2.h"
#include "automatic_k.h"



time2   ReadTimeCanK(void)
{
  Clear();

  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseK();
    QueryTimeK();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (r == bMINORREPEATS) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTimeK();


  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseK();
    QueryDateK();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (r == bMINORREPEATS) return GetTime2Error();
  ShowPercent(50);

  ti = ReadDateK(ti);


  QueryCloseK();


  tiChannelC = ti;

  uchar i;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}



bool    ReadEnergyDayDatesK_Full(void)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseK();
    QueryEnergyDayDatesK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (r == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadEnergyDayDatesK();

  return(1);
}


bool    ReadEnergyMonDatesK_Full(void)
{
  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseK();
    QueryEnergyMonDatesK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (r == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadEnergyMonDatesK();

  return(1);
}



bool    ReadEnergyDayK_Full(uchar  bDay)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseK();
      QueryEnergyDayK(i,bDay);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(70+i);

    ReadEnergyK(i);
  }

  return(1);
}


bool    ReadEnergyMonK_Full(uchar  bMon)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseK();
      QueryEnergyMonK(i,bMon);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(70+i);

    ReadEnergyK(i);
  }

  return(1);
}


bool    ReadEnergyMonTariffK_Full(uchar  bMon, uchar  ibTariff)
{
  uchar i;
  for (i=0; i<4; i++)
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseK();
      QueryEnergyMonK(i,bMon);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == true) return(0);
    }

    if (r == bMINORREPEATS) return(0);
    ShowPercent(70+i);

    ReadEnergyTariffK(i,ibTariff);
  }

  return(1);
}



double2 ReadCntMonCanK2(uchar  ibMonth) // на конец мес€ца
{
  time2 ti2 = ReadTimeCanK();
  if (ti2.fValid == false) return GetDouble2Error();

  time ti = ti2.tiValue;
  if (ti.bMonth == ibMonth+1)
  {
    if (ti.bDay > 1)
      ti.bDay--;
    else
    {
      if (ti.bMonth > 1)
        ti.bMonth--;
      else
      {
        ti.bMonth = 12;
        ti.bYear--;
      }

      ti.bDay = GetDaysInMonthYM(ti.bYear, ti.bMonth);
    }

    if (ReadEnergyDayDatesK_Full() == 0) return GetDouble2Error();

    date dt;
    dt.bDay   = ti.bDay;
    dt.bMonth = ti.bMonth;
    dt.bYear  = ti.bYear;
    uchar bDay = IsDayAddedK(dt);

    if (bDay == 0)
    {
      Clear();
      sprintf(szLo+0, "сутки %02u.%02u.%02u ?",ti.bDay,ti.bMonth,ti.bYear);
      Delay(1000);
      return GetDouble2Error();
    }
    if (ReadEnergyDayK_Full(bDay) == 0) return GetDouble2Error();

    QueryCloseK();
  }
  else
  {
    ti.bYear = (ibMonth+1 > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    ti.bMonth = ibMonth+1;

    if (ReadEnergyMonDatesK_Full() == 0) return GetDouble2Error();

    date dt;
    dt.bDay   = ti.bDay;
    dt.bMonth = ti.bMonth;
    dt.bYear  = ti.bYear;
    uchar bMon = IsMonAddedK(dt);

    if (bMon == 0)
    {
      Clear();
      sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
      Delay(1000);
      return GetDouble2Error();
    }
    if (ReadEnergyMonK_Full(bMon) == 0) return GetDouble2Error();

    QueryCloseK();
  }


  double dbKtrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= dbKtrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



status  ReadCntMonCanTariffK(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
{
  time2 ti2 = ReadTimeCanK();
  if (ti2.fValid == 0) return ST4_BADDIGITAL;

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

  if (ReadEnergyMonDatesK_Full() == 0) return ST4_BADDIGITAL;

  date dt;
  dt.bDay   = ti.bDay;
  dt.bMonth = ti.bMonth;
  dt.bYear  = ti.bYear;
  uchar bMon = IsMonAddedK(dt);

  if (bMon == 0)
  {
    Clear();
    sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
    Delay(1000);
    return(ST4_NOTPRESENTED);
  }
  if (ReadEnergyMonTariffK_Full(bMon,ibTariff) == 0) return ST4_BADDIGITAL;

  QueryCloseK();


  double dbKtrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= dbKtrans;
    mpboChannelsA[i] = true;
  }

  return ST4_OK;
}

