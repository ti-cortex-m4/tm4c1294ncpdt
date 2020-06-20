/*------------------------------------------------------------------------------
profile39_caller.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../kernel/tuples.h"
// #include "io39.h"
#include "device39.h"
#include "time39.h"
#include "hdlc_address.h"
#include "hdlc_monitor.h"
#include "buffer_record_39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "profile39.h"
#include "profile39_caller.h"



static caller39         c;

static bool             fUseBlocks;
static bool             fLastBlock;

static uchar            bBlockNumber;



wbool    ValidateSframe_Profile(void) {
  return ValidateSframe(c.bNR);
}


bool    ValidateIframe_Profile(void) {
  return ValidateIframe(c.bNS, c.bNR);
};



void    Query39_DISC_Profile(void) {
  caller39 c = InitCaller();

  Query39_DISC();
}


void    Query39_AARQ_Profile(void) {
  Query39_AARQ(c.bNS, c.bNR);
}


void    Query39_RR_Profile(void) {
  c.bNR++;
  Query39_RR(c.bNR);
}


void    QueryTime39_Profile(void) {
  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c.bNS, c.bNR, c.bInvokeId);
}


void    ReadTime39_Profile(void) {
}



void    InitProfile39_Profile(void) {
  InitHeader39();
  InitBuffRecord39_All();
}


void    QueryProfile39_Profile(void) {
  InitBuffRecord39();

  t2time t2 = QueryHeader39();

  c.bNS++;
  c.bInvokeId++;
  QueryProfile39(c.bNS, c.bNR, c.bInvokeId, t2.ti1, t2.ti2);
}


void    Read1_Profile(void) {
  fUseBlocks = UseBlocksDMLS();
  fLastBlock = LastBlockDMLS();

  AddBuffRecord39(fUseBlocks ? 20 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());
}


void    Read2_Profile(void) {
   AddBuffRecord39(6 + GetHdlcAddressesSize());
}


void    Read3_Profile(void) {
  bBlockNumber = 0;
}


bool    UseBlocks_Profile(void) {
  return fUseBlocks && (!fLastBlock);
}


void    QueryNextBlock39_Profile(void) {  
  bBlockNumber++;

  c.bNS++;
  QueryNextBlock39(c.bNS, c.bNR, c.bInvokeId, bBlockNumber);  
}



void    Read4_Profile(void) {
  fUseBlocks = UseBlocksDMLS();
  fLastBlock = LastBlockDMLS();

  AddBuffRecord39(20 + GetHdlcAddressesSize());
}


void    Read5_Profile(void) {
  AddBuffRecord39(6 + GetHdlcAddressesSize());
}



bool    FinishProfile39_Profile(void) {
  FinishBuffRecord39(); // TODO check result
  
  return ReadHeader39();
}
