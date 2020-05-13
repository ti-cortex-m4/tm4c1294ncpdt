/*------------------------------------------------------------------------------
AUTOMATIC36!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../digitals/digitals.h"
#include "device36.h"
#include "io36.h"
#include "monitor36.h"
#include "automatic36.h"


/*
bool    QueryConfig36_Full(uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryConfig36();

    if (Input36() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadConfig36();
  return(1);
}


bool    Automatic36(void)
{
  Clear();

  if (QueryConfig36_Full(50) == 0) return(0);

  dbKpulse = GetDivider36();            // K ��������������
  dbKtrans = 1;                         // K �������������
  SetAllFactors(dbKpulse,dbKtrans);     // ���������� � �������������� � � �������������

  return(1);
}
*/


time2   QueryTime36_Full(uchar  bPercent)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateIframe(bNS, bNR)) return GetTime2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateSframe(bNR)) return GetTime2Error();
  DelayOff();

  bNS++;
  QueryTime36(bNS, bNR, bInvokeId++);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateIframe(bNS, bNR)) return GetTime2Error();
  time ti = ReadTime36();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  if (!ValidateSframe(bNR)) return GetTime2Error();
  DelayOff();

  Query36_DISC(); // TODO always close
  if (Input36() != SER_GOODCHECK) return GetTime2Error();
  DelayOff();

/*
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryTime36();

    if (Input36() == SER_GOODCHECK) break;
    if (fKey == true) return GetTime2Error();
  }

  if (i == MaxRepeats()) return GetTime2Error();
  ShowPercent(bPercent);
*/
  return GetTime2(ti, true);
}

/*
bool    QueryEngDay36_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngDay36(bTime);

    if (Input36() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy36();
  return(1);
}


bool    QueryEngMon36_Full(uchar  bTime, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngMon36(bTime);

    if (Input36() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy36();
  return(1);
}
*/


time2   ReadTimeCan36(void)
{
  Clear();

  time2 ti2 = QueryTime36_Full(50);
  if (ti2.fValid == false) return GetTime2Error();

  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;

  return GetTime2(ti2.tiValue, true);
}

/*
time2   ReadTimeCan36_Short(void)
{
  DelayOff();
  QueryTime36();

  if (Input36() != SER_GOODCHECK) return GetTime2Error();


  return GetTime2(ReadTime36(), true);
}
*/

double2 ReadCntCurr36(void)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  uchar i;
  for (i=0; i<4; i++) {
    bNS++;
    QueryEngAbs36(bNS, bNR, bInvokeId++, i);
    if (Input36() != SER_GOODCHECK) return GetDouble2Error();
    if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();

    uint64_t ddw = ReadEngAbs36();
    mpdwChannelsA[i] = ddw % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 1000;
    mpboChannelsA[i] = true;

    DelayOff();

    bNR++;
    Query36_RR(bNR);
    if (Input36() != SER_GOODCHECK) return GetDouble2Error();
    if (!ValidateSframe(bNR)) return GetDouble2Error();
    DelayOff();
  }

  Query36_DISC(); // TODO always close
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
/*
  Clear();

  if (QueryConfig36_Full(50) == 0) return GetDouble2Error();

  if (QueryEngMon36_Full(0, 75) == 0) return GetDouble2Error();

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider36();
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
*/
}


double2 ReadCntMonCan36(uchar  ibMon)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  bNS++;
  QueryEngMon36(bNS, bNR, bInvokeId++, 4, 20);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();

  uint64_t ddw = ReadEngMon36();
  mpdwChannelsA[0] = ddw % 0x100000000;
  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
  mpboChannelsA[0] = true;

  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  Query36_DISC(); // TODO always close
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
/*
  Clear();

  if (QueryConfig36_Full(25) == 0) return GetDouble2Error();

  time2 ti2 = QueryTime36_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMon+1)
  {
    if (QueryEngMon36_Full((bMONTHS+ti.bMonth-1-ibMon) % bMONTHS, 75) == 0) return GetDouble2Error();
  }
  else
  {
    if (QueryEngDay36_Full(1, 75) == 0) return GetDouble2Error();
  }

  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider36();
  mpboChannelsA[0] = true;

  return GetDouble2(mpdbChannelsC[0], true);
*/
}
