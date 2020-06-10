/*------------------------------------------------------------------------------
AUTOMATIC36*C


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
#include "device38.h"
#include "query_engmon_38.h"
#include "io39.h"
#include "monitor38.h"
#include "automatic38.h"


/*
bool    Automatic36(void)
{
  Clear();

  if (QueryConfig36_Full(50) == 0) return(0);

  dbKpulse = GetDivider36();            // K преобразования
  dbKtrans = 1;                         // K трансформации
  SetAllFactors(dbKpulse,dbKtrans);     // сохранение К преобразования и К трансформации

  return(1);
}
*/



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



double2 ReadCntMonCan36_(uchar  ibMon)
{
  Query38_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query38_SNRM();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  bNS++;
  QueryEngMon38(bNS, bNR, bInvokeId++, 4, 20);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();

  uint64_t ddw = ReadEngMon38();
  mpdwChannelsA[0] = ddw % 0x100000000;
  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
  mpboChannelsA[0] = true;

  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();

  Query38_DISC(); // TODO always close
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
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

