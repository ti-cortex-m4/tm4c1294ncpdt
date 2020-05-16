/*------------------------------------------------------------------------------
automatic_get_cntmon_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device36.h"
#include "query_engmon_38.h"
#include "query_profile_38.h"
#include "query_next_block_38.h"
#include "buffer_y.h"
#include "io36.h"
#include "monitor36.h"
#include "automatic_get_cntmon_38.h"



ulong64_ QueryCntMon38_Full(uchar  ibMon)
{
  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateSframe(bNR)) return GetLong64Error();
  DelayOff();


  bNS++;
  bInvokeId++;
  QueryTime38(bNS, bNR, bInvokeId);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateIframe(bNS, bNR)) return GetLong64Error();
  time ti = ReadTime38();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  if (!ValidateSframe(bNR)) return GetLong64Error();
  DelayOff();


  uint64_t ddw;
  if (ti.bMonth != ibMon+1)
  {
    uchar bMonth = (ibMon+1) % 12 + 1;
    uchar bYear = (bMonth > ti.bMonth) ? ti.bYear-1 : ti.bYear;

    bNS++;
    QueryEngMon38(bNS, bNR, bInvokeId++, bMonth, bYear);
    if (Input38() != SER_GOODCHECK) return GetLong64Error();
    if (!ValidateIframe(bNS, bNR)) return GetLong64Error();
    ddw = ReadEngMon38();
    DelayOff();

    bNR++;
    Query38_RR(bNR);
    if (Input38() != SER_GOODCHECK) return GetLong64Error();
    if (!ValidateSframe(bNR)) return GetLong64Error();
    DelayOff();
  }
  else
  {
    StartBufferY();

    time ti1;
    ti1.bYear = 20;
    ti1.bMonth = 4;
    ti1.bDay = 14;
    ti1.bHour = 0;
    ti1.bMinute = 0;
    ti1.bSecond = 0;

    time ti2;
    ti2.bYear = 20;
    ti2.bMonth = 4;
    ti2.bDay = 15;
    ti2.bHour = 23;
    ti2.bMinute = 59;
    ti2.bSecond = 59;



    bNS++;
    bInvokeId++;
    QueryEngCurrDay36(bNS, bNR, bInvokeId, ti1, ti2);
    if (Input38() != SER_GOODCHECK) return GetLong64Error();

    bool fUseBlocks1 = UseBlocksDMLS();
    bool fLastBlock1 = LastBlockDMLS();

    AddBufferY(22, IndexInBuff()-22-3); // TODO GetHdlcAddressesSize
    DelayOff();

    while (!LastSegmentDMLS()) {
      bNR++;
      Query38_RR(bNR);
      if (Input38() != SER_GOODCHECK) return GetLong64Error();
      AddBufferY(8, IndexInBuff()-8-3);
      DelayOff();
    }

    bNR++;
    Query38_RR(bNR);
    if (Input38() != SER_GOODCHECK) return GetLong64Error();
    DelayOff();



    uchar bBlockNumber = 0;

    while (fUseBlocks1 && (!fLastBlock1)) {
      bBlockNumber++;

      bNS++;
  //  uchar bBlockNumber = 1;
      QueryNextBlock36(bNS, bNR, bInvokeId, bBlockNumber);
      if (Input38() != SER_GOODCHECK) return GetLong64Error();

      fUseBlocks1 = UseBlocksDMLS();
      fLastBlock1 = LastBlockDMLS();

      AddBufferY(22, IndexInBuff()-22-3);
      DelayOff();

      while (!LastSegmentDMLS()) {
        bNR++;
        Query38_RR(bNR);
        if (Input38() != SER_GOODCHECK) return GetLong64Error();
        AddBufferY(8, IndexInBuff()-8-3);
        DelayOff();
      }

      bNR++;
      Query38_RR(bNR);
      if (Input38() != SER_GOODCHECK) return GetLong64Error();
      DelayOff();
    }


    buff_y byValue = FinishBufferY();
    ddw = byValue.ddwValue;
  }


  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return GetLong64Error();
  DelayOff();

  return GetLong64(ddw, true);
}



double2 ReadCntMonCan38(uchar  ibMon)
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
  if (Input38() != SER_GOODCHECK) return GetDouble2Error();
  DelayOff();

  return GetDouble2Error();
}
