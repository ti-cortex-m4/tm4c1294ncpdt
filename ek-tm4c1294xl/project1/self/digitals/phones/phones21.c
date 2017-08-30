/*------------------------------------------------------------------------------
PHONES21!C


------------------------------------------------------------------------------*/
/*
#include        <string.h>
#include        "main.h"
#include        "xdata.h"
#include        "rtc.h"
#include        "files.h"
#include        "record3.h"



bit     AddPh2Record(event  evCode)
{
uint    i;

  if (IsRecordDisabled(evCode)) return(1);

  i = (cdwPh2Record % wRECORDS);

  OpenIn(wFLA_PH2RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);

  memset(&reCurr, 0, sizeof(record));

  reCurr.tiNow     = *PGetCurrTimeDate();
  reCurr.cdwRecord = cdwPh2Record++;
  reCurr.evCode    = evCode;

  switch (evCode)
  {
    case EVE_PH2_START: memcpy(&reCurr.mpbBuff+0, &reCurrPhones2, sizeof(real));
                        memcpy(&reCurr.mpbBuff+4, &reMaxxPhones2, sizeof(real)); break;

    case EVE_PH2_FINISH: memcpy(&reCurr.mpbBuff+0, &mpbBuffPhones2, 8); break;
  }

  OpenOut(wFLA_PH2RECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*sizeof(record), &reCurr, sizeof(record));

  return( CloseOut() );
}
*/
