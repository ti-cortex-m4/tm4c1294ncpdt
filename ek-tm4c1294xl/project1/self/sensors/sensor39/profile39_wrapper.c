/*------------------------------------------------------------------------------
profile39_wrapper*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/tuples.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "device39.h"
#include "caller39.h"
#include "time39.h"
#include "hdlc_address.h"
#include "hdlc_monitor.h"
#include "buffer_record_39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "profile39.h"
#include "profile39_wrapper.h"



//#define PROFILE_39_NAMES    1



#include "../../time/calendar.h"
extern  time                    tiValue39;
extern  ulong                   dwValue39;


static caller39         c;

static bool             fUseBlocks;
static bool             fLastBlock;

static uchar            bBlockNumber;



bool    ValidateSframe_Profile(void) {
  return ValidateSframe(c.bNR);
}


bool    ValidateIframe_Profile(void) {
  return ValidateIframe(c.bNS, c.bNR);
};



void    Query39_DISC_Profile(void) {
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Query39_DISC_Profile");
#endif

  c = InitCaller39();
  Query39_DISC();
}


void    Query39_AARQ_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Query39_AARQ_Profile");
#endif

  Query39_AARQ(c.bNS, c.bNR);
}


void    Query39_RR_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Query39_RR_Profile");
#endif

  c.bNR++;
  Query39_RR(c.bNR);
}



bool    ValidateFrame_Profile(void)
{
  return ValidateFrame(c.bNS, c.bNR) == 0;
};



void    QueryTime39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n QueryTime39_Profile");
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c.bNS, c.bNR, c.bInvokeId);
}


void    ReadTime39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n ReadTime39_Profile");
#endif

  tiValue39 = ReadTime39();
  dwValue39 = DateToHouIndex(tiValue39);
}



void    InitProfile39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n InitProfile39_Profile");
#endif

  InitHeader39();
  InitBuffRecord39_All();
}


void    QueryProfile39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n QueryProfile39_Profile");
#endif

  InitBuffRecord39();

  t2time t2 = QueryHeader39();

  c.bNS++;
  c.bInvokeId++;
  QueryProfile39(c.bNS, c.bNR, c.bInvokeId, t2.ti1, t2.ti2);
}


void    Read1_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read1_Profile");
#endif

  fUseBlocks = UseBlocksDMLS();
  fLastBlock = LastBlockDMLS();

  AddBuffRecord39(fUseBlocks ? 20 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());
}


void    Read2_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read2_Profile");
#endif

  AddBuffRecord39(6 + GetHdlcAddressesSize());
}


void    Read3_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read3_Profile");
#endif

  bBlockNumber = 0;
}


bool    UseBlocks_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n UseBlocks_Profile");
#endif

  return fUseBlocks && (!fLastBlock);
}


void    QueryNextBlock39_Profile(void) {  
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n QueryNextBlock39_Profile");
#endif

  bBlockNumber++;

  c.bNS++;
  QueryNextBlock39(c.bNS, c.bNR, c.bInvokeId, bBlockNumber);  
}



void    Read4_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read4_Profile");
#endif

  fUseBlocks = UseBlocksDMLS();
  fLastBlock = LastBlockDMLS();

  AddBuffRecord39(20 + GetHdlcAddressesSize());
}


void    Read5_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read5_Profile");
#endif

  AddBuffRecord39(6 + GetHdlcAddressesSize());
}



bool    FinishProfile39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n FinishProfile39_Profile");
#endif

  FinishBuffRecord39(); // TODO check result
  
  return ReadHeader39();
}
