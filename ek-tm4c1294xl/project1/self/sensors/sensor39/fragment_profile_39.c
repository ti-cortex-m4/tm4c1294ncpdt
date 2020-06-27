/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "device39.h"
#include "error39.h"
#include "caller39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_open_39.h"
#include "hdlc_address.h"
#include "fragment_profile_39.h"



static record39 Fault(uchar  bError)
{
  return GetBuffRecordError(Error39(bError));
}



record39 FragmentProfile39(caller39  *pc, time  tm1, time  tm2)
{
  InitBuffRecord39();


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, tm1, tm2);
  if (Input39() != SER_GOODCHECK) return Fault(180+0);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(180+1);

  bool fUseBlocks = UseBlocksDMLS();
  bool fLastBlock = LastBlockDMLS();

  AddBuffRecord39(fUseBlocks ? 20 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());

  while (!LastSegmentDMLS()) {
    (*pc).bNR++;
    Query39_RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return Fault(180+2);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(180+3);

    AddBuffRecord39(6 + GetHdlcAddressesSize());
  }

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Fault(180+4);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(180+5);


  uchar bBlockNumber = 0;

  while (fUseBlocks && (!fLastBlock)) {
    bBlockNumber++;

    (*pc).bNS++;
    QueryNextBlock39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bBlockNumber);
    if (Input39() != SER_GOODCHECK) return Fault(180+6);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(180+7);

    fUseBlocks = UseBlocksDMLS();
    fLastBlock = LastBlockDMLS();

    AddBuffRecord39(20 + GetHdlcAddressesSize());

    while (!LastSegmentDMLS()) {
      (*pc).bNR++;
      Query39_RR((*pc).bNR);
      if (Input39() != SER_GOODCHECK) return Fault(180+8);
      if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(180+9);

      AddBuffRecord39(6 + GetHdlcAddressesSize());
    }

    (*pc).bNR++;
    Query39_RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return Fault(180+10);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(180+11);
  }


  return FinishBuffRecord39();
}



#ifdef  MONITOR_39

double2 TestFragmentProfile39(void)
{
//  fMonitorLogBasic = false;
//  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller39();

  if (FragmentOpen39(&c) != 0) return GetDouble2Error();

  time tm1;
  tm1.bYear = 20;
  tm1.bMonth = 6;
  tm1.bDay = 1;
  tm1.bHour = 0;
  tm1.bMinute = 0;
  tm1.bSecond = 0;

  time tm2;
  tm2.bYear = 20;
  tm2.bMonth = 6;
  tm2.bDay = 14;
  tm2.bHour = 0;
  tm2.bMinute = 0;
  tm2.bSecond = 0;

  InitBuffRecord39_FragmentProfile39();

  uchar bError = FragmentProfile39(&c, tm1, tm2).bError;
  if (bError != 0)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif
