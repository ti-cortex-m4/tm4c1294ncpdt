/*------------------------------------------------------------------------------
PHONES21!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_flash.h"
#include "../../memory/mem_records.h"
//#include "../../memory/mem_settings.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_profile.h"
//#include "../../memory/mem_limits.h"
//#include "../../memory/mem_extended_0.h"
//#include "../../serial/ports.h"
//#include "../../devices/devices.h"
//#include "../../digitals/digitals_status.h"
//#include "../../digitals/profile/refill.h"
#include "../../time/rtc.h"
#include "../../nvram/cache.h"
#include "../../flash/files.h"
#include "../../flash/records_dsbl.h"
#include "phones2.h"
#include "phones21.h"



extern float                  reCurrPhones2;
extern float                  reMaxxPhones2;
extern uchar                  mpbBuffPhones2[PHONE2_RECORD];



bool    AddPh2Record(event  evCode)
{
uint    i;

  if (IsRecordDisabled(evCode)) return(1);

  i = (cdwPh2Record % wRECORDS);

  OpenIn(PH2_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(record));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwPh2Record++; SaveCache(&chPh2Record);
  reCurr.ev = evCode;

  switch (evCode)
  {
    case EVE_PH2_START: memcpy(&reCurr.mpbBuff+0, &reCurrPhones2, sizeof(float));
                        memcpy(&reCurr.mpbBuff+4, &reMaxxPhones2, sizeof(float)); break;

    case EVE_PH2_FINISH: memcpy(&reCurr.mpbBuff+0, &mpbBuffPhones2, 8); break;
  }

  OpenOut(wFLA_PH2RECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*sizeof(record), &reCurr, sizeof(record));

  return( CloseOut() );
}

