/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "device39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_open_39.h"
#include "hdlc_address.h"
#include "fragment_profile_39.h"



record39 FragmentProfile39(caller39  *pc, time  ti1, time  ti2)
{
  InitBuffRecord39();


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, ti1, ti2);
  if (Input39() != SER_GOODCHECK) return GetBuffRecordError(1);
  DelayOff();

  bool fUseBlocks1 = UseBlocksDMLS();
  bool fLastBlock1 = LastBlockDMLS();

  AddBuffRecord39(fUseBlocks1 ? 20 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());

//  if (fUseBlocks1)
//    AddBuffRecord39(22/*, IndexInBuff()-22-3*/); // TODO GetHdlcAddressesSize
//  else
//    AddBuffRecord39(15/*, IndexInBuff()-15-3*/);

  while (!LastSegmentDMLS()) {
    (*pc).bNR++;
    Query39_RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return GetBuffRecordError(2);

    AddBuffRecord39(6 + GetHdlcAddressesSize()/*, IndexInBuff()-8-3*/);
    DelayOff();
  }

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetBuffRecordError(3);
  DelayOff();



  uchar bBlockNumber = 0;

  while (fUseBlocks1 && (!fLastBlock1)) {
    bBlockNumber++;

    (*pc).bNS++;
//  uchar bBlockNumber = 1;
    QueryNextBlock39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bBlockNumber);
    if (Input39() != SER_GOODCHECK) return GetBuffRecordError(4);

    fUseBlocks1 = UseBlocksDMLS();
    fLastBlock1 = LastBlockDMLS();

    AddBuffRecord39(20 + GetHdlcAddressesSize()/*, IndexInBuff()-22-3*/);
    DelayOff();

    while (!LastSegmentDMLS()) {
      (*pc).bNR++;
      Query39_RR((*pc).bNR);
      if (Input39() != SER_GOODCHECK) return GetBuffRecordError(5);
      
      AddBuffRecord39(6 + GetHdlcAddressesSize()/*, IndexInBuff()-8-3*/);
      DelayOff();
    }

    (*pc).bNR++;
    Query39_RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return GetBuffRecordError(6);
    DelayOff();
  }


  return FinishBuffRecord39();
}



#ifdef  MONITOR_39

double2 TestFragmentProfile39(void)
{
//  fMonitorLogBasic = false;
//  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller();

  if (FragmentOpen39(&c) != 0) return GetDouble2Error();

  time ti1;
  ti1.bYear = 20;
  ti1.bMonth = 4;
  ti1.bDay = 1;
  ti1.bHour = 0;
  ti1.bMinute = 0;
  ti1.bSecond = 0;

  time ti2;
  ti2.bYear = 20;
  ti2.bMonth = 4;
  ti2.bDay = 15;
  ti2.bHour = 0;
  ti2.bMinute = 0;
  ti2.bSecond = 0;

  if (FragmentProfile39(&c, ti1, ti2).bError != 0) return GetDouble2Error();

  return GetDouble2(0, true);
}

#endif
