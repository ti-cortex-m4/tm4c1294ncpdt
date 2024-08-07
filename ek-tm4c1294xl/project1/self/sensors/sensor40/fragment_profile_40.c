/*------------------------------------------------------------------------------
fragment_profile_40.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "dlms.h"
#include "error40.h"
#include "caller40.h"
#include "query_profile_40.h"
#include "query_next_block_40.h"
#include "io40.h"
#include "buffer_record_40.h"
#include "hdlc_address.h"
#include "fragment_open_40.h"
#include "fragment_profile_40.h"



#ifdef  MONITOR_40

static bool Fault(uchar  bError)
{
  Error40(bError);
  return false;
}



bool    FragmentProfile40(caller40  *pc, time  tm1, time  tm2)
{
  InitRecord40(); // step 40.2


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile40(*pc, tm1, tm2); // step 40.4
  if (Input40() != SER_GOODCHECK) return Fault(130+0);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(130+1);

  bool fUseBlocks = UseBlocksDMLS(); // step 40.5
  bool fLastBlock = LastBlockDMLS();

  AddRecord40(fUseBlocks ? 19 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize()); // step 40.6

  while (!LastSegmentDMLS()) { // true: step 40.7, false: step 40.11
    (*pc).bNR++;
    RR((*pc).bNR); // step 40.8
    if (Input40() != SER_GOODCHECK) return Fault(130+2);
    if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(130+3);

    AddRecord40(6 + GetHdlcAddressesSize()); // step 40.9
  } // repeat: step 40.10 -> step 40.7

  (*pc).bNR++;
  RR((*pc).bNR); // step 40.11
  if (Input40() != SER_GOODCHECK) return Fault(130+4);
  if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(130+5);


  uchar bBlockNumber = 0; // step 40.12

  while (fUseBlocks && (!fLastBlock)) { // true: steps 40.13 -> step 40.14, false: 40.16 -> step 40.24
    bBlockNumber++; // step 40.14

    (*pc).bNS++;
    QueryNextBlock40(*pc, bBlockNumber); // step 40.15
    if (Input40() != SER_GOODCHECK) return Fault(130+6);
    if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(130+7);

    fUseBlocks = UseBlocksDMLS(); // step 40.16
    fLastBlock = LastBlockDMLS();

    AddRecord40(19 + GetHdlcAddressesSize()); // step 40.17

    while (!LastSegmentDMLS()) { // true: step 40.18, false: step 40.22
      (*pc).bNR++;
      RR((*pc).bNR); // step 40.19
      if (Input40() != SER_GOODCHECK) return Fault(130+8);
      if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(130+9);

      AddRecord40(6 + GetHdlcAddressesSize()); // step 40.20
    } // repeat: step 40.21 -> step 40.18

    (*pc).bNR++;
    RR((*pc).bNR); // step 40.22
    if (Input40() != SER_GOODCHECK) return Fault(130+10);
    if (ValidateFrameHDLC((*pc).bNS, (*pc).bNR) != 0) return Fault(130+11);
  } // repeat: step 40.23 -> step 40.13


  return true;
}



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

  if (!FragmentProfile40(&c, tm1, tm2))
    return GetDouble2Error();

  if (!FinishRecord40_Monitor())
    return GetDouble2Error();

  return GetDouble0(0);
}

#endif
