/*------------------------------------------------------------------------------
RECORDS_DSBL!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_records.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "records_dsbl.h"



cache const             chRecordDsbl = {RECORDS_DSBL, &mpfRecordDsbl, sizeof(mpfRecordDsbl)};



void    InitRecordsDsbl(void)
{
  LoadCache(&chRecordDsbl);
}


void    ResetRecordsDsbl(void)
{
  memset(&mpfRecordDsbl, 0, sizeof(mpfRecordDsbl));

  mpfRecordDsbl[EVE_PROFILEOPEN] = true;
  mpfRecordDsbl[EVE_PROFILE_OK2] = true;
  mpfRecordDsbl[EVE_PROFILE2] = true;

//  —писок наиболее частых событий (количество/код)
//  806       63
//  216       62
//  67        82
//  67        83
//  67        84
//  66        81
//  31        94
//  6         93

  SaveCache(&chRecordDsbl);
}


bool    IsRecordDisabled(uchar  ibCode)
{
  return mpfRecordDsbl[ibCode] != false;
}



void    OutRecordsDsbl(void)
{
  InitPushCRC();
  Push(&mpfRecordDsbl, sizeof(mpfRecordDsbl));
  Output(sizeof(mpfRecordDsbl));
}
