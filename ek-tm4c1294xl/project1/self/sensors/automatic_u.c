/*------------------------------------------------------------------------------
AUTOMATIC_U.C


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
#include "../digitals/digitals.h"
#include "automatic1.h"
#include "device_u.h"
#include "automatic_k.h"
#include "automatic_u.h"



#ifndef SKIP_U


time2   ReadTimeCanU(void)
{
  return ReadTimeCanK();
}


double2 ReadCntCurrU(void)
{
uchar   i,j;

  Clear();

  for (j=0; j<2; j++)
  {
    if (SkipLine(ibDig, j) == 1) { mpdbChannelsC[j] = 0; continue; }

    for (i=0; i<bMINORREPEATS; i++)
    {
      ShowPercent(50 + j);
      QueryCloseU();
      QueryEnergyAbsU(j);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == 1) return GetDouble2(0, false);
    }

    if (i == bMINORREPEATS) return GetDouble2(0, false);
    ReadEnergyU(j);
  }

  QueryCloseU();


  for (i=0; i<2; i++) 
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;     
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCanU(uchar  ibMonth)
{
uchar   i,j;

  time2 ti2 = ReadTimeCanK();
  if (ti2.fValid == false) return GetDouble2(0, false);

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

    for (j=0; j<2; j++)
    {
      if (SkipLine(ibDig, j) == 1) { mpdbChannelsC[j] = 0; continue; }

      for (i=0; i<bMINORREPEATS; i++)
      {
        ShowPercent(50 + j);
        QueryCloseU();
        QueryEnergyDayU(j, ti);

        if (BccInput() == SER_GOODCHECK) break;
        if (IndexInBuff() == 10) 
        { 
          sprintf(szLo, "сутки %02u.%02u.%02u ?",ti.bDay,ti.bMonth,ti.bYear);
          Delay(1000); 
          return GetDouble2(0, false);
        }
        if (fKey == 1) return GetDouble2(0, false);
      }

      if (i == bMINORREPEATS) return GetDouble2(0, false);
      ReadEnergyU(j);
    }

    QueryCloseU();
  }
  else
  {
    ti.bYear = (ibMonth+1 > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    ti.bMonth = ibMonth+1;

    for (j=0; j<2; j++)
    {
      if (SkipLine(ibDig, j) == 1) { mpdbChannelsC[j] = 0; continue; }

      for (i=0; i<bMINORREPEATS; i++)
      {
        ShowPercent(50 + j);
        QueryCloseU();
        QueryEnergyMonU(j, ti);

        if (BccInput() == SER_GOODCHECK) break;
        if (IndexInBuff() == 10) 
        { 
          sprintf(szLo, " мес€ц %02u.%02u ?  ",ti.bMonth,ti.bYear);
          Delay(1000); 
          return GetDouble2(0, false);
        }
        if (fKey == 1) return GetDouble2(0, false);
      }

      if (i == bMINORREPEATS) return GetDouble2(0, false);
      ReadEnergyU(j);
    }

    QueryCloseU();
  }


  for (i=0; i<2; i++) 
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;     
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif

