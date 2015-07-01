/*------------------------------------------------------------------------------
RECORDS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../memory/mem_settings.h"
#include "../time/rtc.h"
#include "files.h"
#include "record3.h"
#include "records.h"



bool    AddKeyRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwKeyRecord % wRECORDS);

  OpenIn(KEY_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(record));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwKeyRecord++;
  reCurr.ev = ev;
/*
  switch (ev)
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

  return CloseOut();
}


bool    AddSysRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwSysRecord % wRECORDS);

  OpenIn(SYS_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(record));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwSysRecord++;
  reCurr.ev = ev;
/*
  switch (ev)
  {
    case EVE_CONTACTS3_START:
    case EVE_CONTACTS3_COUNTER: memcpy(&reCurr.mpbBuff+0, &cbContact, sizeof(uchar));
                                memcpy(&reCurr.mpbBuff+1, &cbContactMax, sizeof(uchar)); break;

    case EVE_VALUE3_DOWN:     memcpy(&reCurr.mpbBuff+0, &reContactDown, sizeof(real)); break;
    case EVE_VALUE3_UP:       memcpy(&reCurr.mpbBuff+0, &reContactUp, sizeof(real)); break;
    case EVE_VALUE3_COUNTER:  memcpy(&reCurr.mpbBuff+0, &cbContactMax, sizeof(uchar)); break;

    case EVE_CONTACTS3_0_ON:  memcpy(&reCurr.mpbBuff+0, &reContactRec, sizeof(real));
                              memcpy(&reCurr.mpbBuff+4, &reContactUp, sizeof(real)); break;

    case EVE_CONTACTS3_0_OFF: memcpy(&reCurr.mpbBuff+0, &reContactRec, sizeof(real));
                              memcpy(&reCurr.mpbBuff+4, &reContactDown, sizeof(real)); break;

    case EVE_CONTACTSMODE:
    case EVE_CONTACTS1:
    case EVE_CONTACTS2: memcpy(&reCurr.mpbBuff+0, &bContactRec, sizeof(uchar)); break;

    case EVE_PREVNEXTTIME2:   memcpy(&reCurr.mpbBuff+0, &tiCurr, sizeof(time)); break;

    case EVE_EDIT_DIGITAL1:
    case EVE_EDIT_DIGITAL2:   memcpy(&reCurr.mpbBuff+0, &ibX, sizeof(uchar));
                              memcpy(&reCurr.mpbBuff+1, &mpdiDigital[ibX], sizeof(digital)); break;

    case EVE_EDIT_KEY10:
    case EVE_EDIT_KEY20:      memcpy(&reCurr.mpbBuff+0, &ibX, sizeof(uchar));
                              memcpy(&reCurr.mpbBuff+1, &mpphKeys[ibX].szNumber+0, 7); break;

    case EVE_EDIT_KEY11:
    case EVE_EDIT_KEY21:      memcpy(&reCurr.mpbBuff+0, &mpphKeys[ibX].szNumber+7, 6); break;

    case EVE_EDIT_ADDRESS10:
    case EVE_EDIT_ADDRESS11:  memcpy(&reCurr.mpbBuff+0, &ibX, sizeof(uchar));
                              memcpy(&reCurr.mpbBuff+1, &mpdwAddress1[ibX], sizeof(ulong)); break;

    case EVE_EDIT_ADDRESS20:
    case EVE_EDIT_ADDRESS21:  memcpy(&reCurr.mpbBuff+0, &ibX, sizeof(uchar));
                              memcpy(&reCurr.mpbBuff+1, &mpdwAddress2[ibX], sizeof(ulong)); break;
  }
*/
  OpenOut(SYS_RECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*sizeof(record), &reCurr, sizeof(record));

  return CloseOut();
}


bool    AddSysRecordReprogram(event  ev)
{
  return (enGlobal == GLB_REPROGRAM) ? AddSysRecord(ev) : 1;
}


bool    AddDigRecord(event  ev)
{
  return false;
}


bool    AddImpRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwImpRecord % wRECORDS);

  OpenIn(IMP_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr.mpbBuff, 0, sizeof(reCurr.mpbBuff));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwImpRecord++;
  reCurr.ev = ev;
/*
  memcpy(&reCurr.mpbBuff, &ibDig, sizeof(uchar));

  switch (ev)
  {
    case EVE_EVENTS_BADLINK:  memcpy(&reCurr.mpbBuff+1, &mpSerial[ibPort], sizeof(uchar));
                              memcpy(&reCurr.mpbBuff+2, &bEventCode, sizeof(uchar));
                              break;

    case EVE_EVENTS_BADDATA:  break;

    case EVE_EVENTS_OMISSION: memcpy(&reCurr.mpbBuff+1, &bEventCode, sizeof(uchar));
                              break;

    case EVE_EVENTS_A:
    case EVE_EVENTS_B:        memcpy(&reCurr.mpbBuff+1, &tiAlt, sizeof(time));
                              memcpy(&reCurr.mpbBuff+7, &bEventCode, sizeof(uchar));
                              break;
  }
*/
  OpenOut(IMP_RECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*sizeof(record), &reCurr, sizeof(record));

  return CloseOut();
}


bool    AddModRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwModRecord % wRECORDS);

  OpenIn(MOD_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(record));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwModRecord++;
  reCurr.ev = ev;
/*
  memcpy(&reCurr.mpbBuff, &ibDig, sizeof(uchar));

  switch (ev)
  {
    case EVE_MODEM_PROFILEOPEN:
    case EVE_MODEM_SPECIALOPEN:  memcpy(&reCurr.mpbBuff+1, &mpdiDigital[ibDig], sizeof(digital)); break;

    case EVE_MODEM_PROFILE:      memcpy(&reCurr.mpbBuff+1, &mpcwStopCan[ibDig], sizeof(uint)); break;

    case EVE_MODEM_PROFILEOK:    memcpy(&reCurr.mpbBuff+1, &cwHouRead, sizeof(uint));
                                 memcpy(&reCurr.mpbBuff+3, &mpcwStopCan[ibDig], sizeof(uint)); break;

    case EVE_MODEM_PROFILEERROR2:memcpy(&reCurr.mpbBuff+1, &wCurr, sizeof(uint));
                                 memcpy(&reCurr.mpbBuff+3, &mpSerial[ibPort], sizeof(uchar)); break;
  }
*/
  OpenOut(MOD_RECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*sizeof(record), &reCurr, sizeof(record));

  return CloseOut();
}
