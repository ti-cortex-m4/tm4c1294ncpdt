/*------------------------------------------------------------------------------
automatic_get_cntmon_38*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "query_engmon_38.h"
#include "query_profile_38.h"
#include "query_next_block_39.h"
#include "buffer_y.h"
#include "io39.h"
#include "automatic_get_cntmon_39.h"



ulong64_ QueryCntMon38_Full(uchar  ibMon)
{
  Query38_DISC();
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  DelayOff();

  Query38_SNRM();
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error(1);
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateSframe(bNR)) return GetLong64Error(1);
  DelayOff();


  bNS++;
  bInvokeId++;
  QueryTime38(bNS, bNR, bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error(1);
  time ti = ReadTime38();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  if (!ValidateSframe(bNR)) return GetLong64Error(1);
  DelayOff();


  uint64_t ddw;
  if (ti.bMonth != ibMon+1)
  {
    uchar bMonth = (ibMon+1) % 12 + 1; // TODO check all months
    uchar bYear = (bMonth > ti.bMonth) ? ti.bYear-1 : ti.bYear;

    bNS++;
    QueryEngMon38(bNS, bNR, bInvokeId++, bMonth, bYear);
    if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
    if (!ValidateIframe(bNS, bNR)) return GetLong64Error(1);
    ddw = ReadEngMon38();
    DelayOff();

    bNR++;
    Query38_RR(bNR);
    if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
    if (!ValidateSframe(bNR)) return GetLong64Error(1);
    DelayOff();
  }
  else
  {
    StartBufferY();

    time ti1;
    ti1.bYear = ti.bYear;
    ti1.bMonth = ti.bMonth;
    ti1.bDay = ti.bDay;
    ti1.bHour = 0;
    ti1.bMinute = 0;
    ti1.bSecond = 0;

    time ti2;
    ti2.bYear = ti.bYear;
    ti2.bMonth = ti.bMonth;
    ti2.bDay = ti.bDay;
    ti2.bHour = 23;
    ti2.bMinute = 59;
    ti2.bSecond = 59;



    bNS++;
    bInvokeId++;
    QueryProfile38(bNS, bNR, bInvokeId, ti1, ti2);
    if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
    DelayOff();

    bool fUseBlocks1 = UseBlocksDMLS();
    bool fLastBlock1 = LastBlockDMLS();

    if (fUseBlocks1)
      AddBufferY(22, IndexInBuff()-22-3); // TODO GetHdlcAddressesSize
    else
      AddBufferY(15, IndexInBuff()-15-3);

    while (!LastSegmentDMLS()) {
      bNR++;
      Query38_RR(bNR);
      if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
      AddBufferY(8, IndexInBuff()-8-3);
      DelayOff();
    }

    bNR++;
    Query38_RR(bNR);
    if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
    DelayOff();



    uchar bBlockNumber = 0;

    while (fUseBlocks1 && (!fLastBlock1)) {
      bBlockNumber++;

      bNS++;
  //  uchar bBlockNumber = 1;
      QueryNextBlock39(bNS, bNR, bInvokeId, bBlockNumber);
      if (Input39() != SER_GOODCHECK) return GetLong64Error(1);

      fUseBlocks1 = UseBlocksDMLS();
      fLastBlock1 = LastBlockDMLS();

      AddBufferY(22, IndexInBuff()-22-3);
      DelayOff();

      while (!LastSegmentDMLS()) {
        bNR++;
        Query38_RR(bNR);
        if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
        AddBufferY(8, IndexInBuff()-8-3);
        DelayOff();
      }

      bNR++;
      Query38_RR(bNR);
      if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
      DelayOff();
    }


    buff_y by = FinishBufferY();
    if (by.bError != 0)
    {
      MonitorString("\n Error="); MonitorCharDec(by.bError);
      return GetLong64Error(1);
    }
    if (by.fFirst == false)
    {
      MonitorString("\n No Data");
      return GetLong64Error(1);
    }

    ddw = by.ddwValue;
  }


  Query38_DISC();
  if (Input39() != SER_GOODCHECK) return GetLong64Error(1);
  DelayOff();

  return GetLong64(ddw, true, 0);
}



double2 ReadCntMonCan39(uchar  ibMon)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    ulong64_ ddw2 = QueryCntMon38_Full(ibMon);
    if (fKey == true) break;
    if (ddw2.fValid)
    {
      ShowPercent(50);

      mpdwChannelsA[0] = ddw2.ddwValue % 0x100000000;
      mpdbChannelsC[0] = (double)mpdwChannelsA[0] / 1000;
      mpboChannelsA[0] = true;

      return GetDouble2(mpdbChannelsC[0], true);
    }
  }

  Query38_DISC();
  if (Input39() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2Error();
}