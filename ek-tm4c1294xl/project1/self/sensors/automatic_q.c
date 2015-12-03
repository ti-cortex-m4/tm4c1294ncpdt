/*------------------------------------------------------------------------------
AUTOMATIC_Q.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
//#include "../time/delay.h"
//#include "../time/timedate.h"
//#include "../time/calendar.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
//#include "../digitals/digitals.h"
//#include "automatic1.h"
#include "device_q.h"
#include "automatic_q.h"



#ifndef SKIP_Q

time2   ReadTimeDateK(void);



time2   ReadTimeDateQ(void)
{
  return ReadTimeDateK();
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


  reBuffB = mpreTransCnt[ibDig];

  for (r=0; r<Q_LINES; r++)
  {
    reBuffA = mpreChannelsB[r] * reBuffB;
    mpreChannelsB[r] = reBuffA;
    mpboChannelsA[r] = true;
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}


/*
bool    ReadCntMonCanQ(uchar  ibMonth)
{
uchar   i;

  if (ReadTimeDateK() == 0) return(0);

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

    for (i=0; i<bMINORREPEATS; i++)
    {
      QueryCloseQ();
      QueryEnergyDayQ();

      if (BccInput() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        sprintf(szLo, "сутки %02bu.%02bu.%02bu ?",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear);
        Delay(1000);
        return(0);
      }
      if (fKey == true) return(0);
    }

    if (i == bMINORREPEATS) return(0);

    ReadEnergyQ();
    QueryCloseQ();
  }
  else
  {
    tiAlt.bYear = (ibMonth+1 > tiAlt.bMonth) ? tiAlt.bYear-1 : tiAlt.bYear;
    tiAlt.bMonth = ibMonth+1;

    for (i=0; i<bMINORREPEATS; i++)
    {
      QueryCloseQ();
      QueryEnergyMonQ();

      if (BccInput() == SER_GOODCHECK) break;
      if (IndexInBuff() == 10)
      {
        sprintf(szLo, " мес€ц %02bu.%02bu ?  ",tiAlt.bMonth,tiAlt.bYear);
        Delay(1000);
        return(0);
      }
      if (fKey == true) return(0);
    }

    if (i == bMINORREPEATS) return(0);

    ReadEnergyQ();
    QueryCloseQ();
  }


  reBuffB = mpreTransCnt[ibDig];

  for (i=0; i<Q_LINES; i++)
  {
    reBuffA = mpreChannelsB[i] * reBuffB;
    mpreChannelsB[i] = reBuffA;
    mpboChannelsA[i] = true;
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}
*/
#endif

