/*------------------------------------------------------------------------------
RECORDS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../memory/mem_settings.h"
#include "../time/rtc.h"
#include "../nvram/cache.h"
#include "files.h"
#include "record3.h"
#include "records.h"



cache const             chKeyRecord = {KEY_INDEX, &cdwKeyRecord, sizeof(ulong)};
cache const             chSysRecord = {SYS_INDEX, &cdwSysRecord, sizeof(ulong)};
cache const             chDigRecord = {DIG_INDEX, &cdwDigRecord, sizeof(ulong)};
cache const             chImpRecord = {IMP_INDEX, &cdwImpRecord, sizeof(ulong)};
cache const             chModRecord = {MOD_INDEX, &cdwModRecord, sizeof(ulong)};
cache const             chPh2Record = {PH2_INDEX, &cdwPh2Record, sizeof(ulong)};
cache const             chAuxRecord = {AUX_INDEX, &cdwAuxRecord, sizeof(ulong)};



void    InitRecords(void)
{
  LoadCache(&chKeyRecord);
  LoadCache(&chSysRecord);
  LoadCache(&chDigRecord);
  LoadCache(&chImpRecord);
  LoadCache(&chModRecord);
  LoadCache(&chPh2Record);
  LoadCache(&chAuxRecord);
}


void    ResetRecords(void)
{
  cdwKeyRecord = 0;
  SaveCache(&chKeyRecord);

  cdwSysRecord = 0;
  SaveCache(&chSysRecord);

  cdwDigRecord = 0;
  SaveCache(&chDigRecord);

  cdwImpRecord = 0;
  SaveCache(&chImpRecord);

  cdwModRecord = 0;
  SaveCache(&chModRecord);

  cdwPh2Record = 0;
  SaveCache(&chPh2Record);

  cdwAuxRecord = 0;
  SaveCache(&chAuxRecord);
}



bool    AddKeyRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwKeyRecord % wRECORDS);

  OpenIn(KEY_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, SIZEOF_RECORD);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwKeyRecord++; SaveCache(&chKeyRecord);
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
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*SIZEOF_RECORD, &reCurr, SIZEOF_RECORD);

  return CloseOut();
}


bool    AddSysRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwSysRecord % wRECORDS);

  OpenIn(SYS_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, SIZEOF_RECORD);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwSysRecord++; SaveCache(&chSysRecord);
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
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*SIZEOF_RECORD, &reCurr, SIZEOF_RECORD);

  return CloseOut();
}


bool    AddSysRecordReprogram(event  ev)
{
  return (enGlobal == GLB_REPROGRAM) ? AddSysRecord(ev) : 1;
}


bool    AddDigRecord(event  ev)
{
uint    i;

  if (IsRecordDisabled(ev)) return(1);

  i = (cdwAuxRecord % wRECORDS2);

  OpenIn(AUX_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr.mpbBuff, 0, sizeof(reCurr.mpbBuff));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwAuxRecord++; SaveCache(&chAuxRecord);
  reCurr.ev = ev;
/*
  memcpy(&reCurr.mpbBuff, &ibDig, sizeof(uchar));
  switch (ev)
  {
    case EVE_PROFILEOPEN:
    case EVE_SPECIALOPEN:   memcpy(&reCurr.mpbBuff+1, &mpdiDigital[ibDig], sizeof(digital)); break;

//    case EVE_ESC_V_DATA:    memcpy(&reCurr.mpbBuff+1, &reBuffA, sizeof(real)); break;
//    case EVE_ESC_S_DATA:    memcpy(&reCurr.mpbBuff+1, &reBuffA, sizeof(real)); break;
//    case EVE_ESC_U_DATA:    memcpy(&reCurr.mpbBuff+1, &moAlt.tiAlfa, sizeof(time)); break;

//    case EVE_PROFILE:       memcpy(&reCurr.mpbBuff+1, &mpcwStopCan[ibDig], sizeof(uint)); break;

    case EVE_PROFILE2:      memcpy(&reCurr.mpbBuff+0, &mpcwStopCan[ibDig], sizeof(uint));
                            memcpy(&reCurr.mpbBuff+2, &mpcwStopAuxCan[ibDig], sizeof(uint)); break;

//    case EVE_PROFILE_OK:    memcpy(&reCurr.mpbBuff+1, &cwHouRead, sizeof(uint));
//                            memcpy(&reCurr.mpbBuff+3, &mpcwStopCan[ibDig], sizeof(uint)); break;

    case EVE_PROFILE_OK2:   memcpy(&reCurr.mpbBuff+0, &cwHouRead, sizeof(uint));
                            memcpy(&reCurr.mpbBuff+2, &mpcwStopCan[ibDig], sizeof(uint));
                            memcpy(&reCurr.mpbBuff+4, &mpcwStopAuxCan[ibDig], sizeof(uint)); break;

    case EVE_PROFILE_ERROR2:memcpy(&reCurr.mpbBuff+1, &wCurr, sizeof(uint));
                            memcpy(&reCurr.mpbBuff+3, &mpSerial[ibPort], sizeof(uchar)); break;

    case EVE_PROFILECLOSE2: memcpy(&reCurr.mpbBuff+1, &cwHouLength, sizeof(uint)); break;

    case EVE_REFILL1:       memcpy(&reCurr.mpbBuff+1, &iwHardHou, sizeof(uint));
                            memcpy(&reCurr.mpbBuff+3, &iwBmin, sizeof(uint));
                            memcpy(&reCurr.mpbBuff+5, &iwBmax, sizeof(uint)); break;

    case EVE_PREVIOUS_TOP:  memcpy(&reCurr.mpbBuff+0, &iwMajor, sizeof(uint)); break;

    case EVE_CURRENT2_CANALS: memcpy(&reCurr.mpbBuff+0, &mpbCurrent2Buff, 8); break;

    case EVE_CURRENT2_VALUE:  memcpy(&reCurr.mpbBuff+1, &dwUpdate, sizeof(ulong));
                              memcpy(&reCurr.mpbBuff+5, &mpwCurrent2Mnt[ibCan], sizeof(uint)); break;

    case EVE_CHECKUP_START: memcpy(&reCurr.mpbBuff+0, &boCheckupReadonly, sizeof(uchar));
                            memcpy(&reCurr.mpbBuff+1, &mpbCheckupLimitD[ibDig], sizeof(uchar));
                            memcpy(&reCurr.mpbBuff+2, &mpbCheckupLimitM[ibDig], sizeof(uchar)); break;

    case EVE_CHECKUP_NEXT:  memcpy(&reCurr.mpbBuff+0, &cwHouRead, sizeof(uint)); break;

    case EVE_CHECKUP_VALUE: memcpy(&reCurr.mpbBuff+0, &dwBuffC, sizeof(ulong));
                            memcpy(&reCurr.mpbBuff+4, &mpdwChannelsA[diPrev.ibLine], sizeof(ulong)); break;

    case EVE_CHECKUP_DAY_SKIP:
    case EVE_CHECKUP_MON_SKIP:
    case EVE_CHECKUP_DAY_FAIL:
    case EVE_CHECKUP_MON_FAIL:
    case EVE_CHECKUP_DAY:
    case EVE_CHECKUP_MON:   memcpy(&reCurr.mpbBuff+0, &daAlt, sizeof(date)); break;

    case EVE_CHECKUP_CANAL: memcpy(&reCurr.mpbBuff+0, &ibCan, sizeof(uchar));
                            memcpy(&reCurr.mpbBuff+1, &diPrev, sizeof(digital)); break;

    case EVE_CHECKUP_DAY_NEXT:
    case EVE_CHECKUP_MON_NEXT: memcpy(&reCurr.mpbBuff+0, &daAlt, sizeof(date));
                               memcpy(&reCurr.mpbBuff+6, &ibGrp, sizeof(uchar)); break;

    case EVE_CHECKUP_INFO:  memcpy(&reCurr.mpbBuff+0, &cbCheckupDays, sizeof(uchar));
                            memcpy(&reCurr.mpbBuff+1, &cbCheckupErrorDay, sizeof(uchar));
                            memcpy(&reCurr.mpbBuff+2, &cbCheckupErrorMon, sizeof(uchar)); break;

    case EVE_DEVICE_P_DEFECT: memcpy(&reCurr.mpbBuff+0, &tiDig, sizeof(time)); break;

    case EVE_EXTENDED_0_ERROR: memcpy(&reCurr.mpbBuff+0, &x, sizeof(uchar));
                               memcpy(&reCurr.mpbBuff+1, &bExt0Counter, sizeof(uchar)); break;
  }
*/
  OpenOut(AUX_RECORD + i / bRECORD_BLOCK);
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*SIZEOF_RECORD, &reCurr, SIZEOF_RECORD);

  return( CloseOut() );
}


bool    AddImpRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwImpRecord % wRECORDS);

  OpenIn(IMP_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr.mpbBuff, 0, sizeof(reCurr.mpbBuff));

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwImpRecord++; SaveCache(&chImpRecord);
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
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*SIZEOF_RECORD, &reCurr, SIZEOF_RECORD);

  return CloseOut();
}


bool    AddModRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return(1);

  uint i = (cdwModRecord % wRECORDS);

  OpenIn(MOD_RECORD + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, SIZEOF_RECORD);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwModRecord++; SaveCache(&chModRecord);
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
  memcpy(&mpbPageOut + (i % bRECORD_BLOCK)*SIZEOF_RECORD, &reCurr, SIZEOF_RECORD);

  return CloseOut();
}
