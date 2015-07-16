/*------------------------------------------------------------------------------
RECORD3.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_records.h"



cache const             chRecordDsbl = {RECORDS_DSBL, &mpboRecordDsbl, sizeof(mpboRecordDsbl)};



void    ResetRecordDisable(void)
{
//  memset(&mpboRecordDsbl, 0, sizeof(mpboRecordDsbl));
//
//  mpboRecordDsbl[EVE_PROFILEOPEN] = boTrue;
//  mpboRecordDsbl[EVE_PROFILE_OK2] = boTrue;
//  mpboRecordDsbl[EVE_PROFILE2] = boTrue;
}


bool    IsRecordDisabled(uchar  ibCode)
{
  return false; //mpboRecordDsbl[ibCode] != boFalse;
}



void    OutRecordDisable(void)
{
//  InitPushCRC();
//  Push(&mpboRecordDsbl, sizeof(mpboRecordDsbl));
//  Output(sizeof(mpboRecordDsbl));
}
