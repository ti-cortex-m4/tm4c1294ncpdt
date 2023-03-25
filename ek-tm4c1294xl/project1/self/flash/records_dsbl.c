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

  mpfRecordDsbl[EVE_CANAL_DISABLED] = true; // 62
  mpfRecordDsbl[EVE_PROFILE_DISABLED] = true; // 63
  mpfRecordDsbl[EVE_PROFILEOPEN] = true; // 64

  mpfRecordDsbl[EVE_MODEMCONNECT1] = true; // 81
  mpfRecordDsbl[EVE_MODEMCONNECT2] = true; // 82
  mpfRecordDsbl[EVE_MODEMBREAK1] = true; // 83
  mpfRecordDsbl[EVE_MODEMBREAK2] = true; // 84

  mpfRecordDsbl[EVE_PROFILECLOSE2] = true; // 94
  mpfRecordDsbl[EVE_PROFILE_OK2] = true; // 97
  mpfRecordDsbl[EVE_PROFILE2] = true; // 99

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
