/*------------------------------------------------------------------------------
AUTOMATIC_Q.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
//#include "../time/delay.h"
#include "../time/timedate.h"
//#include "../time/calendar.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
//#include "../digitals/digitals.h"
//#include "automatic1.h"
#include "device_q.h"
#include "automatic_k.h"
#include "automatic_q.h"



#ifndef SKIP_Q

time2   ReadTimeCanK(void);



time2   ReadTimeCanQ(void)
{
  return ReadTimeCanK();
}



double2 ReadCntCurrQ(void)
{
  Clear();

  uchar r;
  for (r=0; r<bMINORREPEATS; r++)
  {
    QueryCloseQ();
    QueryEnergyAbsQ();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == true) GetDouble2Error();
  }

  if (r == bMINORREPEATS) GetDouble2Error();

  ReadEnergyQ();
  QueryCloseQ();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_Q; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCanQ(uchar  ibMon)
{
  time2 ti2 = ReadTimeCanK();
  if (ti2.fValid == false) return GetDouble2Error();

  time ti = ti2.tiValue;

  if (ti.bMonth == ibMon+1)
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

    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseQ();
      QueryEnergyDayQ(ti);

      if (BccInput() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+0, "сутки %02u.%02u.%02u ?",ti.bDay,ti.bMonth,ti.bYear);
        Delay(1000);
        return GetDouble2Error();
      }
      if (fKey == true) return GetDouble2Error();
    }

    if (r == bMINORREPEATS) return GetDouble2Error();

    ReadEnergyQ();
    QueryCloseQ();
  }
  else
  {
    ti.bYear = (ibMon+1 > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    ti.bMonth = ibMon+1;

    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      QueryCloseQ();
      QueryEnergyMonQ(ti);

      if (BccInput() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        Clear();
        sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
        Delay(1000);
        return GetDouble2Error();
      }
      if (fKey == true) return GetDouble2Error();
    }

    if (r == bMINORREPEATS) return GetDouble2Error();

    ReadEnergyQ();
    QueryCloseQ();
  }


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_Q; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif

