/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "device38.h"
#include "query_profile_38.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "monitor38.h"
#include "buffer_y.h"
#include "fragment_profile_39.h"



uchar   FragmentProfile39(runner39  *runner, time  ti1, time  ti2)
{
  StartBufferY();


  (*runner).bNS++;
  (*runner).bInvokeId++;
  QueryProfile38((*runner).bNS, (*runner).bNR, (*runner).bInvokeId, ti1, ti2);
  if (Input39() != SER_GOODCHECK) return 1;
  DelayOff();

  bool fUseBlocks1 = UseBlocksDMLS();
  bool fLastBlock1 = LastBlockDMLS();

  if (fUseBlocks1)
    AddBufferY(22, IndexInBuff()-22-3); // TODO GetHdlcAddressesSize
  else
    AddBufferY(15, IndexInBuff()-15-3);

  while (!LastSegmentDMLS()) {
    (*runner).bNR++;
    Query38_RR((*runner).bNR);
    if (Input39() != SER_GOODCHECK) return 2;
    AddBufferY(8, IndexInBuff()-8-3);
    DelayOff();
  }

  (*runner).bNR++;
  Query38_RR((*runner).bNR);
  if (Input39() != SER_GOODCHECK) return 3;
  DelayOff();



  uchar bBlockNumber = 0;

  while (fUseBlocks1 && (!fLastBlock1)) {
    bBlockNumber++;

    (*runner).bNS++;
//  uchar bBlockNumber = 1;
    QueryNextBlock39((*runner).bNS, (*runner).bNR, (*runner).bInvokeId, bBlockNumber);
    if (Input39() != SER_GOODCHECK) return 4;

    fUseBlocks1 = UseBlocksDMLS();
    fLastBlock1 = LastBlockDMLS();

    AddBufferY(22, IndexInBuff()-22-3);
    DelayOff();

    while (!LastSegmentDMLS()) {
      (*runner).bNR++;
      Query38_RR((*runner).bNR);
      if (Input39() != SER_GOODCHECK) return 5;
      AddBufferY(8, IndexInBuff()-8-3);
      DelayOff();
    }

    (*runner).bNR++;
    Query38_RR((*runner).bNR);
    if (Input39() != SER_GOODCHECK) return 6;
    DelayOff();
  }


  FinishBufferY();
  return 0;
}
