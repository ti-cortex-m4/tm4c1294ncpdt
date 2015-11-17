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

  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryTimeK();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (i == bMINORREPEATS) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTimeK();


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryDateK();

    if (BccInput() == SER_GOODCHECK) break;
  }

  if (i == bMINORREPEATS) return GetTime2Error();
  ShowPercent(50);

  ti = ReadDateK(ti);


  QueryCloseK();


  tiChannelC = ti;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}



bool    ReadEnergyDayDatesK_Full(void)
{
  uchar ibZ;
  for (ibZ=0; ibZ<bMINORREPEATS; ibZ++)
  {
    QueryCloseK();
    QueryEnergyDayDatesK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (ibZ == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadEnergyDayDatesK();

  return(1);
}


bool    ReadEnergyMonDatesK_Full(void)
{
  uchar ibZ;
  for (ibZ=0; ibZ<bMINORREPEATS; ibZ++)
  {
    QueryCloseK();
    QueryEnergyMonDatesK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (ibZ == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadEnergyMonDatesK();

  return(1);
}



bool    ReadEnergyDayK_Full(uchar  bDay)
{
  uchar ibCan;
  for (ibCan=0; ibCan<4; ibCan++)
  {
    uchar ibZ;
    for (ibZ=0; ibZ<bMINORREPEATS; ibZ++)
    {
      QueryCloseK();
      QueryEnergyDayK(ibCan,bDay);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (ibZ == bMINORREPEATS) return(0);
    ShowPercent(70+ibCan);

    ReadEnergyK(ibCan);
  }

  return(1);
}


bool    ReadEnergyMonK_Full(uchar  bMon)
{
  uchar ibCan;
  for (ibCan=0; ibCan<4; ibCan++)
  {
    uchar ibZ;
    for (ibZ=0; ibZ<bMINORREPEATS; ibZ++)
    {
      QueryCloseK();
      QueryEnergyMonK(ibCan,bMon);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (ibZ == bMINORREPEATS) return(0);
    ShowPercent(70+ibCan);

    ReadEnergyK(ibCan);
  }

  return(1);
}


bool    ReadEnergyMonTariffK_Full(uchar  bMon, uchar  ibTariff)
{
  uchar ibCan;
  for (ibCan=0; ibCan<4; ibCan++)
  {
    uchar ibZ;
    for (ibZ=0; ibZ<bMINORREPEATS; ibZ++)
    {
      QueryCloseK();
      QueryEnergyMonK(ibCan,bMon);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (ibZ == bMINORREPEATS) return(0);
    ShowPercent(70+ibCan);

    ReadEnergyTariffK(ibCan,ibTariff);
  }

  return(1);
}



double2 ReadCntMonCanK2(uchar  ibMonth) // на конец мес€ца
{
  time2 ti2 = ReadTimeCanK();
  if (ti2.fValid == false) return GetDouble2Error();

  time tiAlt = ti2.tiValue;
  if (tiAlt.bMonth == ibMonth+1)
  {
    if (tiAlt.bDay > 1)
      tiAlt.bDay--;
    else
    {
      if (tiAlt.bMonth > 1)
        tiAlt.bMonth--;
      else
      {
        tiAlt.bMonth = 12;
        tiAlt.bYear--;
      }

      tiAlt.bDay = DaysInMonth();
    }

    if (ReadEnergyDayDatesK_Full() == 0) return GetDouble2Error();

    date daAlt;
    daAlt.bDay   = tiAlt.bDay;
    daAlt.bMonth = tiAlt.bMonth;
    daAlt.bYear  = tiAlt.bYear;
    uchar ibGrp = IsDayAddedK(daAlt);

    if (ibGrp == 0)
    {
      sprintf(szLo, "сутки %02u.%02u.%02u ?",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear);
      Delay(1000);
      return GetDouble2Error();
    }
    if (ReadEnergyDayK_Full(ibGrp) == 0) return GetDouble2Error();

    QueryCloseK();
  }
  else
  {
    tiAlt.bYear = (ibMonth+1 > tiAlt.bMonth) ? tiAlt.bYear-1 : tiAlt.bYear;
    tiAlt.bMonth = ibMonth+1;

    if (ReadEnergyMonDatesK_Full() == 0) return GetDouble2Error();

    date daAlt;
    daAlt.bDay   = tiAlt.bDay;
    daAlt.bMonth = tiAlt.bMonth;
    daAlt.bYear  = tiAlt.bYear;
    uchar ibGrp = IsMonAddedK(daAlt);

    if (ibGrp == 0)
    {
      sprintf(szLo, " мес€ц %02u.%02u ?  ",tiAlt.bMonth,tiAlt.bYear);
      Delay(1000);
      return GetDouble2Error();
    }
    if (ReadEnergyMonK_Full(ibGrp) == 0) return GetDouble2Error();

    QueryCloseK();
  }


  reBuffB = mpreTransCnt[ibDig];

  uchar ibCan;
  for (ibCan=0; ibCan<4; ibCan++)
  {
    reBuffA = mpreChannelsB[ibCan] * reBuffB;
    mpreChannelsB[ibCan] = reBuffA;
    mpboChannelsA[ibCan] = true;
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}


/*
status4 ReadCntMonCanTariffK(uchar  ibMonth, uchar  ibTariff) // на начало мес€ца
{
  if (ReadTimeDateK() == 0) return(ST4_BADDIGITAL);

  if (ibMonth == 0)
  {
    tiAlt.bMonth = 12;
    tiAlt.bYear--;
  }
  else
  {
    if (ibMonth+1 > tiAlt.bMonth) tiAlt.bYear--;
    tiAlt.bMonth = ibMonth;
  }

  if (ReadEnergyMonDatesK_Full() == 0) return (ST4_BADDIGITAL);

  daAlt.bDay   = tiAlt.bDay;
  daAlt.bMonth = tiAlt.bMonth;
  daAlt.bYear  = tiAlt.bYear;
  ibGrp = IsMonAddedK();

  if (ibGrp == 0)
  {
    sprintf(szLo, " мес€ц %02u.%02u ?  ",tiAlt.bMonth,tiAlt.bYear);
    Delay(1000);
    return(ST4_NOTPRESENTED);
  }
  if (ReadEnergyMonTariffK_Full(ibGrp,ibTariff) == 0) return (ST4_BADDIGITAL);

  QueryCloseK();


  reBuffB = mpreTransCnt[ibDig];

  for (ibCan=0; ibCan<4; ibCan++)
  {
    reBuffA = mpreChannelsB[ibCan] * reBuffB;
    mpreChannelsB[ibCan] = reBuffA;
    mpboChannelsA[ibCan] = true;
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(ST4_OK);
}
*/
