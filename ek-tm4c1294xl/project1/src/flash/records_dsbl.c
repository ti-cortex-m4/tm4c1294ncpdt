/*------------------------------------------------------------------------------
RECORDS_DSBL.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_records.h"
#include "../nvram/cache.h"
#include "records_dsbl.h"



cache const             chRecordDsbl = {RECORDS_DSBL, &mpboRecordDsbl, sizeof(mpboRecordDsbl)};

InitRecordsDsbl();

void    ResetRecordsDsbl(void)
{
//  memset(&mpboRecordDsbl, 0, sizeof(mpboRecordDsbl));
//
//  mpboRecordDsbl[EVE_PROFILEOPEN] = boTrue;
//  mpboRecordDsbl[EVE_PROFILE_OK2] = boTrue;
//  mpboRecordDsbl[EVE_PROFILE2] = boTrue;
}


bool    IsRecordsDsbld(uchar  ibCode)
{
  return false; //mpboRecordDsbl[ibCode] != boFalse;
}



void    OutRecordsDsbl(void)
{
//  InitPushCRC();
//  Push(&mpboRecordDsbl, sizeof(mpboRecordDsbl));
//  Output(sizeof(mpboRecordDsbl));
}
