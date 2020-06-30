/*------------------------------------------------------------------------------
profile39_wrapper*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/tuples.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "include39.h"
#include "device39.h"
#include "device39_obis.h"
#include "caller39.h"
#include "time39.h"
#include "hdlc_address.h"
#include "hdlc_monitor.h"
#include "buffer_record_39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "query_register_39.h"
#include "profile39.h"
#include "profile39_wrapper.h"



static caller39         c;

static bool             fUseBlocks;
static bool             fLastBlock;

static uchar            bBlockNumber;



void    DISC_Profile39(void) {
#ifdef PROFILE_39_NAMES
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorString("\n\n DISC_Profile39");
#endif

  c = InitCaller39();
  Query39_DISC();
}


void    AARQ_Profile39(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n AARQ_Profile39");
#endif

  Query39_AARQ(c.bNS, c.bNR);
}


void    RR_Profile39(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n RR_Profile39");
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

  SetTime_Profile39(ReadTime39());
}



void    QueryScaler_Profile(void)
{
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n QueryScaler_Profile");
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterScalerDLMS(obisEngAbs, c);
}


bool    ReadScaler_Profile(void)
{
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n ReadScaler_Profile");
#endif

  double2 scaler = ReadRegisterScalerDLMS();
  SetScaler_Profile39(scaler.fValid ? scaler.dbValue : -1);
  return scaler.fValid;
}



void    InitProfile39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n InitProfile39_Profile");
#endif

  InitHeader39();
  InitRecord39_FragmentProfile39();
}


void    QueryProfile39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n QueryProfile39_Profile");
#endif

  InitRecord39();

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

  AddRecord39(fUseBlocks ? 20 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());
}


void    Read2_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read2_Profile");
#endif

  AddRecord39(6 + GetHdlcAddressesSize());
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

  AddRecord39(20 + GetHdlcAddressesSize());
}


void    Read5_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n Read5_Profile");
#endif

  AddRecord39(6 + GetHdlcAddressesSize());
}



bool    FinishProfile39_Profile(void) {
#ifdef PROFILE_39_NAMES
  MonitorString("\n\n FinishProfile39_Profile");
#endif

  FinishRecord39(); // TODO check result
  
  return ReadHeader39();
}
