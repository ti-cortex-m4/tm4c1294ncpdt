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
#include "../../serial/monitor.h" //
#include "../../digitals/digitals.h"
#include "device36.h"
#include "device36_2.h"
#include "io36.h"
#include "monitor36.h"
#include "buffers36.h"
#include "automatic36_2.h"



double2 ReadCntMonCan36_2(void)
{
  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 10; // TODO 0

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();


/*
  bNS++;
  QueryTime36(bNS, bNR, bInvokeId++);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  time ti = ReadTime36();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();
*/


  bNS++; MonitorString("\n\n step1");
  QueryEngCurrDay36(bNS, bNR, bInvokeId++);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  PrintInBuff(22, IndexInBuff()-22-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step2");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  PrintInBuff(8, IndexInBuff()-8-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step3");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



  uchar bBlockNumber = 1;



  bNS++; MonitorString("\n\n step4");
  QueryNextBlock36(bNS, bNR, bInvokeId++, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  PrintInBuff(22, IndexInBuff()-22-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step5");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  PrintInBuff(8, IndexInBuff()-8-3); // input...
  DelayOff();

  bNR++; MonitorString("\n\n step6");
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



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

