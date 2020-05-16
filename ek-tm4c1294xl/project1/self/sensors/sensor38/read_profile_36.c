/*------------------------------------------------------------------------------
read_profile_36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../serial/monitor.h" // TODO
#include "../../digitals/digitals.h"
#include "device36.h"
#include "query_profile_38.h"
#include "query_next_block_38.h"
#include "io36.h"
#include "monitor36.h"
#include "buffer_y.h"
#include "read_profile_36.h"




schar   y(void)
{
  StartBufferY();



  Query38_DISC();
  if (Input38() != SER_GOODCHECK) return -15;//GetDouble2Error();
  DelayOff();

  Query38_SNRM();
  if (Input38() != SER_GOODCHECK) return -16;//GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query38_Open2(bNS, bNR);
  if (Input38() != SER_GOODCHECK) return -17;//GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return -18;//GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



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
  ti2.bDay = 14;
  ti2.bHour = 11;
  ti2.bMinute = 0;
  ti2.bSecond = 0;



  bNS++;
  bInvokeId++;
  QueryEngCurrDay36(bNS, bNR, bInvokeId, ti1, ti2);
  if (Input38() != SER_GOODCHECK) return -19;
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
    if (Input38() != SER_GOODCHECK) return -20;
    AddBufferY(8, IndexInBuff()-8-3);
    DelayOff();
  }

  bNR++;
  Query38_RR(bNR);
  if (Input38() != SER_GOODCHECK) return -21;
  DelayOff();



  uchar bBlockNumber = 0;

  while (fUseBlocks1 && (!fLastBlock1)) {
    bBlockNumber++;

    bNS++;
//  uchar bBlockNumber = 1;
    QueryNextBlock36(bNS, bNR, bInvokeId, bBlockNumber);
    if (Input38() != SER_GOODCHECK) return -22;

    fUseBlocks1 = UseBlocksDMLS();
    fLastBlock1 = LastBlockDMLS();

    AddBufferY(22, IndexInBuff()-22-3);
    DelayOff();

    while (!LastSegmentDMLS()) {
      bNR++;
      Query38_RR(bNR);
      if (Input38() != SER_GOODCHECK) return -23;
      AddBufferY(8, IndexInBuff()-8-3);
      DelayOff();
    }

    bNR++;
    Query38_RR(bNR);
    if (Input38() != SER_GOODCHECK) return -24;
    DelayOff();
  }

/*
  bNS++;
  bBlockNumber = 2;
  QueryNextBlock36(bNS, bNR, bInvokeId, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return -25;

  bool fUseBlocks3 = UseBlocksDMLS();
  bool fLastBlock3 = LastBlockDMLS();

  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  while (!LastSegmentDMLS()) {
    bNR++;
    Query36_RR(bNR);
    if (Input36() != SER_GOODCHECK) return -26;
    AddBuffer1(8, IndexInBuff()-8-3);
    DelayOff();
  }

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -27;
  DelayOff();
*/


  FinishBufferY();
  return 0;
}


time2   ReadProfile36(void)
{
  y();
  return GetTime2(tiZero, true);
}
