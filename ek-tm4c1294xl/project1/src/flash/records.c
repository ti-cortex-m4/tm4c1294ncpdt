/*------------------------------------------------------------------------------
RECORDS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../time/rtc.h"
#include "files.h"
#include "record3.h"
#include "records.h"



bool    AddKeyRecord(event  evCode)
{
  if (IsRecordDisabled(evCode)) return(1);

  uint i = (cdwKeyRecord % wRECORDS);

  OpenIn(KEY_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(record));

  reCurr.tiNow     = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwKeyRecord++;
  reCurr.evCode    = evCode;
/*
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
*/
  OpenOut(KEY_RECORD + i / bRECORD_BLOCK);
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



bool    GetRecord(class  clT, uint  iwRecord)
{
  uint wPage;
  switch (clT)
  {
    case CLA_KEYBOARD: wPage = KEY_RECORD; break;
    case CLA_SYSTEM:   wPage = SYS_RECORD; break;
    case CLA_DIGITAL:  wPage = DIG_RECORD; break;
    case CLA_IMPULSE:  wPage = IMP_RECORD; break;
    case CLA_MODEM:    wPage = MOD_RECORD; break;
    case CLA_PHONES2:  wPage = PH2_RECORD; break;
  }

  uint i = (iwRecord % wRECORDS);

  OpenIn(wPage + i / bRECORD_BLOCK);
  memcpy(&reCurr, &mpbPageIn + (i % bRECORD_BLOCK)*sizeof(record), sizeof(record));

  return(1);
}


ulong   GetRecordCount(class  clT)
{
  switch (clT)
  {
    case CLA_KEYBOARD: return(cdwKeyRecord);
    case CLA_SYSTEM:   return(cdwSysRecord);
    case CLA_DIGITAL:  return(cdwDigRecord);
    case CLA_IMPULSE:  return(cdwImpRecord);
    case CLA_MODEM:    return(cdwModRecord);
    case CLA_PHONES2:  return(cdwPh2Record);
  }
}


bool    GetRecordsBlock(class  clT, uchar  ibBlock)
{
  uint i = GetRecordCount(clT) % wRECORDS;
  ibBlock = (bRECORD_SIZE + i/bRECORD_BLOCK - ibBlock) % bRECORD_PAGES;

  switch (clT)
  {
    case CLA_KEYBOARD: return(OpenIn(KEY_RECORD + ibBlock));
    case CLA_SYSTEM:   return(OpenIn(SYS_RECORD + ibBlock));
    case CLA_DIGITAL:  return(OpenIn(DIG_RECORD + ibBlock));
    case CLA_IMPULSE:  return(OpenIn(IMP_RECORD + ibBlock));
    case CLA_MODEM:    return(OpenIn(MOD_RECORD + ibBlock));
    case CLA_PHONES2:  return(OpenIn(PH2_RECORD + ibBlock));
  }
}

