/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device36.h"
#include "io36.h"
#include "automatic36.h"



time2   ReadTimeCan36(void)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryTime36();
    if (Input36() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(25);

  time ti = ReadTime36();


  for (r=0; r<MaxRepeats(); r++)
  {
    QueryDate36();
    if (Input36() == SER_GOODCHECK) break;
  }

  if (r == MaxRepeats()) return GetTime2Error();
  ShowPercent(50);

  ti = ReadDate36(ti);


  QueryClose36();


  tiChannelC = ti;

  uchar i;
  for (i=0; i<4; i++) mpboChannelsA[i] = true;

  return GetTime2(ti, true);
}


time2   ReadTimeCan36_Short(void)
{
  QueryTime36();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  time ti = ReadTime36();

  QueryDate36();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  ti = ReadDate36(ti);

  QueryClose36();
  return GetTime2(ti, true);
}



double2 ReadCntCurr36(uchar  bMaxLines)
{
  Clear();

  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    if (SkipLine(ibDig, i) == true) { mpdbChannelsC[i] = 0; continue; }

    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      ShowPercent(50 + i);
      QueryEngAbs36(i);

      if (Input36() == SER_GOODCHECK) break;
      if (fKey == true) return GetDouble2Error();
    }

    if (r == MaxRepeats()) return GetDouble2Error();
    ReadEng36(i);
  }

  QueryClose36();


  for (i=0; i<bMaxLines; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan36(uchar  ibMon, uchar  bMaxLines)
{
  time2 ti2 = ReadTimeCan36();
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

    uchar i;
    for (i=0; i<bMaxLines; i++)
    {
      if (SkipLine(ibDig, i) == true) { mpdbChannelsC[i] = 0; continue; }

      uchar r;
      for (r=0; r<MaxRepeats(); r++)
      {
        ShowPercent(50 + i);
        QueryEngDay36(i, ti);

        if (Input36() == SER_GOODCHECK) break;
        if (IndexInBuff() == 3)
        {
          Clear();
          sprintf(szLo+0, "сутки %02u.%02u.%02u ?",ti.bDay,ti.bMonth,ti.bYear);
          Delay(1000);
          return GetDouble2Error();
        }
        if (fKey == true) return GetDouble2Error();
      }

      if (r == MaxRepeats()) return GetDouble2Error();
      ReadEng36(i);
    }

    QueryClose36();
  }
  else
  {
    ti.bYear = (ibMon+1 > ti.bMonth) ? ti.bYear-1 : ti.bYear;
    ti.bMonth = ibMon+1;

    uchar i;
    for (i=0; i<bMaxLines; i++)
    {
      if (SkipLine(ibDig, i) == true) { mpdbChannelsC[i] = 0; continue; }

      uchar r;
      for (r=0; r<MaxRepeats(); r++)
      {
        ShowPercent(50 + i);
        QueryEngMon36(i, ti);

        if (Input36() == SER_GOODCHECK) break;
        if (IndexInBuff() == 3)
        {
          Clear();
          sprintf(szLo+1, "мес€ц %02u.%02u ?",ti.bMonth,ti.bYear);
          Delay(1000);
          return GetDouble2Error();
        }
        if (fKey == true) return GetDouble2Error();
      }

      if (r == MaxRepeats()) return GetDouble2Error();
      ReadEng36(i);
    }

    QueryClose36();
  }


  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
