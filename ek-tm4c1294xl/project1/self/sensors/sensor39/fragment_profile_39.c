/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "device39.h"
#include "query_profile_38.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_profile_39.h"



uchar   FragmentProfile39(runner39  *pr, time  ti1, time  ti2)
{
  InitBuffRecord39();


  (*pr).bNS++;
  (*pr).bInvokeId++;
  QueryProfile38((*pr).bNS, (*pr).bNR, (*pr).bInvokeId, ti1, ti2);
  if (Input39() != SER_GOODCHECK) return 1;
  DelayOff();

  bool fUseBlocks1 = UseBlocksDMLS();
  bool fLastBlock1 = LastBlockDMLS();

  if (fUseBlocks1)
    AddBuffRecord39(22, IndexInBuff()-22-3); // TODO GetHdlcAddressesSize
  else
    AddBuffRecord39(15, IndexInBuff()-15-3);

  while (!LastSegmentDMLS()) {
    (*pr).bNR++;
    Query38_RR((*pr).bNR);
    if (Input39() != SER_GOODCHECK) return 2;
    AddBuffRecord39(8, IndexInBuff()-8-3);
    DelayOff();
  }

  (*pr).bNR++;
  Query38_RR((*pr).bNR);
  if (Input39() != SER_GOODCHECK) return 3;
  DelayOff();



  uchar bBlockNumber = 0;

  while (fUseBlocks1 && (!fLastBlock1)) {
    bBlockNumber++;

    (*pr).bNS++;
//  uchar bBlockNumber = 1;
    QueryNextBlock39((*pr).bNS, (*pr).bNR, (*pr).bInvokeId, bBlockNumber);
    if (Input39() != SER_GOODCHECK) return 4;

    fUseBlocks1 = UseBlocksDMLS();
    fLastBlock1 = LastBlockDMLS();

    AddBuffRecord39(22, IndexInBuff()-22-3);
    DelayOff();

    while (!LastSegmentDMLS()) {
      (*pr).bNR++;
      Query38_RR((*pr).bNR);
      if (Input39() != SER_GOODCHECK) return 5;
      AddBuffRecord39(8, IndexInBuff()-8-3);
      DelayOff();
    }

    (*pr).bNR++;
    Query38_RR((*pr).bNR);
    if (Input39() != SER_GOODCHECK) return 6;
    DelayOff();
  }


  FinishBuffRecord39();
  return 0;
}
