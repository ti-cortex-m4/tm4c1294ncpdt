/*------------------------------------------------------------------------------
profile39_wrapper.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/tuples.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "include40.h"
#include "dlms.h"
#include "dlms_obis.h"
#include "caller40.h"
#include "time40.h"
#include "hdlc_address.h"
#include "hdlc_monitor.h"
#include "buffer_record_39.h"
#include "query_profile_40.h"
#include "query_next_block_40.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "query_register_39.h"
#include "profile39.h"
#include "profile39_wrapper.h"



static caller40         c;

static sint             wDeltaSeconds;

static bool             fUseBlocks;
static bool             fLastBlock;

static uchar            bBlockNumber;



void    DISC_Profile39(void) {
#ifdef PROFILE_40_NAMES
  fMonitorLogBasic = true;
  fMonitorLogHex = true;

  MonitorString("\n DISC_Profile39");
#endif

  c = InitCaller40();
  DISC();
}


void    SNRM_Profile39(void)
{
#ifdef PROFILE_40_NAMES
  MonitorString("\n SNRM_Profile39");
#endif

  SNRM();
}


void    AARQ_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n AARQ_Profile39");
#endif

  AARQ(c.bNS, c.bNR);
}


void    RR_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n RR_Profile39");
#endif

  c.bNR++;
  RR(c.bNR);
}



bool    ValidateFrame_Profile39(void)
{
  return ValidateFrame(c.bNS, c.bNR) == 0;
};



void    QueryTime_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n QueryTime_Profile39");
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryTime40(c);
}


void    ReadTime_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n ReadTime_Profile39");
#endif

  SetTime_Profile40(ReadTime40());
}



void    SetCorrectSecond39(sint  ddw)
{
  wDeltaSeconds = ddw;
}


void    QueryCorrect_Profile39(void)
{
#ifdef PROFILE_40_NAMES
  MonitorString("\n QueryCorrect_Profile39 "); MonitorSignedLongDec(wDeltaSeconds);
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryCorrectTime40(c, wDeltaSeconds);
}



void    QueryScaler_Profile39(void)
{
#ifdef PROFILE_40_NAMES
  MonitorString("\n QueryScaler_Profile39");
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterScalerDLMS(obisScalerForProfile1, c);
}


bool    ReadScaler_Profile39(void)
{
#ifdef PROFILE_40_NAMES
  MonitorString("\n ReadScaler_Profile39");
#endif

  double2 scaler = ReadRegisterScalerDLMS();
  SetScaler_Profile40(scaler.fValid ? scaler.dbValue : -1);
  return scaler.fValid;
}



void    InitProfile_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n InitProfile_Profile39");
#endif

  InitHeader40(); // step 40.1
}


void    QueryProfile_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n QueryProfile_Profile39");
#endif

  InitRecord39(); // step 40.2

  t2time t2 = QueryHeader40(); // step 40.3

  c.bNS++;
  c.bInvokeId++;
  QueryProfile40(c, t2.ti1, t2.ti2); // step 40.4
}


void    Read1_Profile(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n Read1_Profile");
#endif

  fUseBlocks = UseBlocksDMLS(); // step 40.5
  fLastBlock = LastBlockDMLS();

  AddRecord39(fUseBlocks ? 19 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize()); // step 40.6
}


void    Read2_Profile(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n Read2_Profile");
#endif

  AddRecord39(6 + GetHdlcAddressesSize()); // step 40.9
}


void    Read3_Profile(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n Read3_Profile");
#endif

  bBlockNumber = 0; // step 40.12
}


bool    UseBlocks_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n UseBlocks_Profile39");
#endif

  return fUseBlocks && (!fLastBlock); // step 40.13
}


void    QueryNextBlock_Profile39(void) {  
#ifdef PROFILE_40_NAMES
  MonitorString("\n QueryNextBlock_Profile39");
#endif

  bBlockNumber++; // step 40.14

  c.bNS++;
  QueryNextBlock40(c, bBlockNumber); // step 40.15
}



void    Read4_Profile(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n Read4_Profile");
#endif

  fUseBlocks = UseBlocksDMLS(); // step 40.16
  fLastBlock = LastBlockDMLS();

  AddRecord39(19 + GetHdlcAddressesSize()); // step 40.17
}


void    Read5_Profile(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n Read5_Profile");
#endif

  AddRecord39(6 + GetHdlcAddressesSize()); // step 40.20
}



bool2   FinishProfile_Profile39(void) {
#ifdef PROFILE_40_NAMES
  MonitorString("\n FinishProfile_Profile39");
#endif

  bool success = FinishRecordProfile39(); // step 40.25

  if (success)
    return GetBool2(ReadHeader40(), true); // step 40.26
  else
    return GetBool2Error(); 
}
