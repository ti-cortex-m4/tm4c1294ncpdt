/*------------------------------------------------------------------------------
RECORDS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_records.h"
#include "files.h"
#include "records.h"



bool    AddKeyRecord(event  ev)
{
  if (IsRecordDisabled(evCode)) return(1);

  uint i = (cdwKeyRecord % wRECORDS);

  OpenIn(wFLA_KEYRECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wFREEPAGE_SIZE);

  memset(&reCurr, 0, sizeof(record));

  reCurr.tiNow     = *PGetCurrTimeDate();
  reCurr.cdwRecord = cdwKeyRecord++;
  reCurr.evCode    = evCode;

  switch (evCode)
  {
    case EVE_GPS_GOODLINK:  memcpy(&reCurr.mpbBuff+0, &tiGPS, sizeof(time)); break;

    case EVE_GPS_BADGPS:    memcpy(&reCurr.mpbBuff+0, &bStatusGPS, sizeof(uchar)); break;

    case EVE_GPS_GOODGPS_1: memcpy(&reCurr.mpbBuff+0, &tiAlt, sizeof(time));
                            memcpy(&reCurr.mpbBuff+6, &bGMT, sizeof(uchar)); break;

    case EVE_GPS_GOODGPS_2: memcpy(&reCurr.mpbBuff+0, &bSeasonCurr, sizeof(uchar));
                            memcpy(&reCurr.mpbBuff+1, &boSeasonGPS, sizeof(uchar)); break;

    case EVE_EXT_CORRECT2:  memcpy(&reCurr.mpbBuff+0, &tiAlt, sizeof(time)); break;

    case EVE_ESC_K:
    case EVE_ESC_k:
    case EVE_INQ_CORRECT1:
    case EVE_INQ_CORRECT2:
    case EVE_INQ_CORRECT4:
    case EVE_PROGRAM_2:     memcpy(&reCurr.mpbBuff+0, &tiSetRTC, sizeof(time));

    case EVE_SMK_GOODLINK:  memcpy(&reCurr.mpbBuff+0, &tiSMK, sizeof(time)); break;
    case EVE_SMK_GOODSMK_1: memcpy(&reCurr.mpbBuff+0, &tiAlt, sizeof(time)); break;
  }

  OpenOut(wFLA_KEYRECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*sizeof(record), &reCurr, sizeof(record));

  return( CloseOut() );
}


bool AddSysRecord(event  ev) {
	return false;
}


bool AddSysRecordReprogram(event  ev) {
	return false;
}


bool AddDigRecord(event  ev) {
	return false;
}


bool AddImpRecord(event  ev) {
	return false;
}


bool AddModRecord(event  ev) {
	return false;
}
