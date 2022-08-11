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



static record39 Fault(uchar  bError)
{
  return GetRecordError39(Error39(bError));
}



record39 FragmentProfile39(caller39  *pc, time  tm1, time  tm2, bool  fProfile)
{
  InitRecord39();


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, tm1, tm2);
  if (Input39() != SER_GOODCHECK) return Fault(130+0);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+1);

  bool fUseBlocks = UseBlocksDMLS();
  bool fLastBlock = LastBlockDMLS();

  AddRecord39(fUseBlocks ? 19 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());

  while (!LastSegmentDMLS()) {
    (*pc).bNR++;
    RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return Fault(130+2);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+3);

    AddRecord39(6 + GetHdlcAddressesSize());
  }

  (*pc).bNR++;
  RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return Fault(130+4);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+5);


  uchar bBlockNumber = 0;

  while (fUseBlocks && (!fLastBlock)) {
    bBlockNumber++;

    (*pc).bNS++;
    QueryNextBlock39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bBlockNumber);
    if (Input39() != SER_GOODCHECK) return Fault(130+6);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+7);

    fUseBlocks = UseBlocksDMLS();
    fLastBlock = LastBlockDMLS();

    AddRecord39(19 + GetHdlcAddressesSize());

    while (!LastSegmentDMLS()) {
      (*pc).bNR++;
      RR((*pc).bNR);
      if (Input39() != SER_GOODCHECK) return Fault(130+8);
      if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+9);

      AddRecord39(6 + GetHdlcAddressesSize());
    }

    (*pc).bNR++;
    RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return Fault(130+10);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+11);
  }


  if (fProfile)
    return FinishRecordProfile39();
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

  uchar bError = FragmentProfile39(&c, tm1, tm2, false).bError;
  if (bError != 0)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif
