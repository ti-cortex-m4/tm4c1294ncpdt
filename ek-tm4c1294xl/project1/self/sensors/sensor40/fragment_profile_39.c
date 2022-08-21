/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "dlms.h"
#include "error40.h"
#include "caller40.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_open_39.h"
#include "hdlc_address.h"
#include "fragment_profile_39.h"



static bool Fault(uchar  bError)
{
  Error40(bError);
  return false;
}



bool    FragmentProfile39(caller40  *pc, time  tm1, time  tm2, bool  fProfile)
{
  InitRecord39(); // step 40.2


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile40(*pc, tm1, tm2); // step 40.4
  if (Input39() != SER_GOODCHECK) return Fault(130+0);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+1);

  bool fUseBlocks = UseBlocksDMLS(); // step 40.5
  bool fLastBlock = LastBlockDMLS();

  AddRecord39(fUseBlocks ? 19 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize()); // step 40.6

  while (!LastSegmentDMLS()) { // true: step 40.7, false: step 40.11
    (*pc).bNR++;
    RR((*pc).bNR); // step 40.8
    if (Input39() != SER_GOODCHECK) return Fault(130+2);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+3);

    AddRecord39(6 + GetHdlcAddressesSize()); // step 40.9
  } // repeat: step 40.10 -> step 40.7

  (*pc).bNR++;
  RR((*pc).bNR); // step 40.11
  if (Input39() != SER_GOODCHECK) return Fault(130+4);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+5);


  uchar bBlockNumber = 0; // step 40.12

  while (fUseBlocks && (!fLastBlock)) { // true: steps 40.13 -> step 40.14, false: 40.16 -> step 40.24
    bBlockNumber++; // step 40.14

    (*pc).bNS++;
    QueryNextBlock39(*pc, bBlockNumber); // step 40.15
    if (Input39() != SER_GOODCHECK) return Fault(130+6);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+7);

    fUseBlocks = UseBlocksDMLS(); // step 40.16
    fLastBlock = LastBlockDMLS();

    AddRecord39(19 + GetHdlcAddressesSize()); // step 40.17

    while (!LastSegmentDMLS()) { // true: step 40.18, false: step 40.22
      (*pc).bNR++;
      RR((*pc).bNR); // step 40.19
      if (Input39() != SER_GOODCHECK) return Fault(130+8);
      if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+9);

      AddRecord39(6 + GetHdlcAddressesSize()); // step 40.20
    } // repeat: step 40.21 -> step 40.18

    (*pc).bNR++;
    RR((*pc).bNR); // step 40.22
    if (Input39() != SER_GOODCHECK) return Fault(130+10);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+11);
  } // repeat: step 40.23 -> step 40.13


  if (fProfile) // step 40.24
    return FinishRecordProfile39(); // step 40.25
  else
    return FinishRecord39();
}



#ifdef  MONITOR_40

double2 TestFragmentProfile39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller40 c = InitCaller40();

  if (FragmentOpen40(&c) != 0) return GetDouble2Error();

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
