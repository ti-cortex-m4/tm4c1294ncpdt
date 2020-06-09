/*------------------------------------------------------------------------------
fragment_profile_38.c


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
#include "device38.h"
#include "query_profile_38.h"
#include "query_next_block_38.h"
#include "io38.h"
#include "monitor38.h"
#include "fragment_profile_38.h"



uchar                   bNS;
uchar                   bNR;
uchar                   bInvokeId;



schar   FragmentProfile38(time  ti1, time  ti2)
{
  bNS++;
  bInvokeId++;
  QueryProfile38(bNS, bNR, bInvokeId, ti1, ti2);
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
