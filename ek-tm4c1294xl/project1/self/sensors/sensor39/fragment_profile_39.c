/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "dlms.h"
#include "error39.h"
#include "caller39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_open_39.h"
#include "hdlc_address.h"
#include "fragment_profile_39.h"



static bool Fault(uchar  bError)
{
  Error39(bError);
  return false;
}



bool    FragmentProfile39(caller39  *pc, time  tm1, time  tm2, bool  fProfile)
{
  InitRecord39(); // step 39.2


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, tm1, tm2); // step 39.4
  if (Input39() != SER_GOODCHECK) return Fault(130+0);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+1);

  bool fUseBlocks = UseBlocksDMLS(); // step 39.5
  bool fLastBlock = LastBlockDMLS();

  AddRecord39(fUseBlocks ? 19 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize()); // step 39.6

  while (!LastSegmentDMLS()) { // true: step 39.7, false: step 39.11
    (*pc).bNR++;
    RR((*pc).bNR); // step 39.8
    if (Input39() != SER_GOODCHECK) return Fault(130+2);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+3);

    AddRecord39(6 + GetHdlcAddressesSize()); // step 39.9
  } // repeat: step 39.10

  (*pc).bNR++;
  RR((*pc).bNR); // step 39.11
  if (Input39() != SER_GOODCHECK) return Fault(130+4);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+5);


  uchar bBlockNumber = 0; // step 39.12

  while (fUseBlocks && (!fLastBlock)) { // true: steps 39.13 -> step 39.14, false 12a -> step 22
    bBlockNumber++; // step 39.14

    (*pc).bNS++;
    QueryNextBlock39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bBlockNumber); // step step 39.15
    if (Input39() != SER_GOODCHECK) return Fault(130+6);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+7);

    fUseBlocks = UseBlocksDMLS(); // step 15
    fLastBlock = LastBlockDMLS();

    AddRecord39(19 + GetHdlcAddressesSize()); // step 16

    while (!LastSegmentDMLS()) { // step 17
      (*pc).bNR++;
      RR((*pc).bNR); // step 18
      if (Input39() != SER_GOODCHECK) return Fault(130+8);
      if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+9);

      AddRecord39(6 + GetHdlcAddressesSize()); // step 19
    } // step 19a

    (*pc).bNR++;
    RR((*pc).bNR); // step 20
    if (Input39() != SER_GOODCHECK) return Fault(130+10);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+11);
  } // step 21 -> step 12


  if (fProfile) // step 22
    return FinishRecordProfile39(); // step 23
  else
    return FinishRecord39();
}



#ifdef  MONITOR_39

double2 TestFragmentProfile39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller39();

  if (FragmentOpen39(&c) != 0) return GetDouble2Error();

  time tm1;
  tm1.bYear = 22;
  tm1.bMonth = 7;
  tm1.bDay = 25;
  tm1.bHour = 0;
  tm1.bMinute = 0;
  tm1.bSecond = 0;

  time tm2;
  tm2.bYear = 22;
  tm2.bMonth = 7;
  tm2.bDay = 26;
  tm2.bHour = 0;
  tm2.bMinute = 0;
  tm2.bSecond = 0;

  bool success = FragmentProfile39(&c, tm1, tm2, false);
  if (!success)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif
