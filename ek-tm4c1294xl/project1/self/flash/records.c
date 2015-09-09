/*------------------------------------------------------------------------------
RECORDS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_flash.h"
#include "../memory/mem_records.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_current.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../memory/mem_extended_0.h"
#include "../serial/ports.h"
#include "../devices/devices.h"
#include "../digitals/digitals_status.h"
#include "../digitals/profile/refill.h"
#include "../time/rtc.h"
#include "../nvram/cache.h"
#include "files.h"
#include "records_dsbl.h"
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

  InitRecordsDsbl();
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

  ResetRecordsDsbl();
}



void    RecordToBuff(uchar*  pBuff)
{
  memcpy(pBuff + 0,  &reCurr.ti, 6);

  static combo32 co;
  co.dwBuff = reCurr.cdwRecord;
  memcpy(pBuff + 6,  &co.mpbBuff[3], 1);
  memcpy(pBuff + 7,  &co.mpbBuff[2], 1);
  memcpy(pBuff + 8,  &co.mpbBuff[1], 1);
  memcpy(pBuff + 9,  &co.mpbBuff[0], 1);

  memcpy(pBuff + 10, &reCurr.ev, 1);

  memcpy(pBuff + 11, &reCurr.mpbBuff[0], 1);
  memcpy(pBuff + 12, &reCurr.mpbBuff[1], 1);
  memcpy(pBuff + 13, &reCurr.mpbBuff[2], 1);
  memcpy(pBuff + 14, &reCurr.mpbBuff[3], 1);
  memcpy(pBuff + 15, &reCurr.mpbBuff[4], 1);
  memcpy(pBuff + 16, &reCurr.mpbBuff[5], 1);
  memcpy(pBuff + 17, &reCurr.mpbBuff[6], 1);
  memcpy(pBuff + 18, &reCurr.mpbBuff[7], 1);
}


void    BuffToRecord(uchar*  pBuff)
{
  memcpy(&reCurr.ti, pBuff + 0, 6);

  static combo32 co;
  memcpy(&co.mpbBuff[3], pBuff + 6, 1);
  memcpy(&co.mpbBuff[2], pBuff + 7, 1);
  memcpy(&co.mpbBuff[1], pBuff + 8, 1);
  memcpy(&co.mpbBuff[0], pBuff + 9, 1);
  reCurr.cdwRecord = co.dwBuff;

  memcpy(&reCurr.ev, pBuff + 10, 1);

  memcpy(&reCurr.mpbBuff[0], pBuff + 11, 1);
  memcpy(&reCurr.mpbBuff[1], pBuff + 12, 1);
  memcpy(&reCurr.mpbBuff[2], pBuff + 13, 1);
  memcpy(&reCurr.mpbBuff[3], pBuff + 14, 1);
  memcpy(&reCurr.mpbBuff[4], pBuff + 15, 1);
  memcpy(&reCurr.mpbBuff[5], pBuff + 16, 1);
  memcpy(&reCurr.mpbBuff[6], pBuff + 17, 1);
  memcpy(&reCurr.mpbBuff[7], pBuff + 18, 1);
}



static uint OpenRecord(uint  wPage, ulong  cdwRecord)
{
  uint i = (cdwRecord % wRECORDS);

  OpenIn(wPage + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(reCurr));
  return i;
}


static uint OpenRecord2(uint  wPage, ulong  cdwRecord)
{
  uint i = (cdwRecord % wRECORDS2);

  OpenIn(wPage + i / bRECORD_BLOCK);
  memcpy(mpbPageOut, mpbPageIn, wLEAF_BYTES);

  memset(&reCurr, 0, sizeof(reCurr));
  return i;
}


static void CloseRecord(uint  wPage, uint  i)
{
  OpenOut(wPage + i / bRECORD_BLOCK);
  RecordToBuff((uchar *) &mpbPageOut + (i % bRECORD_BLOCK)*SIZEOF_RECORD);
}



static void PutChar(uchar  i, uchar  b)
{
  reCurr.mpbBuff[i]  = b;
}


static void PutInt(uchar  i, uint  w)
{
  PutChar(i + 0, w / 0x100);
  PutChar(i + 1, w % 0x100);
}


static void PutLong(uchar  i, ulong  dw)
{
	PutInt(i + 0, dw / 0x10000);
	PutInt(i + 2, dw % 0x10000);
}


static void Put(uchar  i, uchar  *pbBuff,  uint  wSize)
{
  uchar j;
  for (j=0; j<wSize; j++)
  {
    PutChar(i++, *(pbBuff++));
  }
}



bool    AddKeyRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return true;

  uint i = OpenRecord(KEY_RECORD, cdwKeyRecord);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwKeyRecord++; SaveCache(&chKeyRecord);
  reCurr.ev = ev;

  switch (ev)
  {
    case EVE_GPS_GOODLINK:  Put(0, (uchar *) &tiGps, sizeof(time)); break;

    case EVE_GPS_BADGPS:    PutChar(0, bStatusGps); break;

    case EVE_GPS_GOODGPS_1: Put(0, (uchar *) &tiRecordTime, sizeof(time));
                            PutChar(6, bGmtGps); break;

    case EVE_GPS_GOODGPS_2: PutChar(0, bSeasonCurr);
                            PutChar(1, boSeasonGps ? 0xFF : 0x00); break;

    case EVE_EXT_CORRECT2:
    case EVE_ESC_K:
    case EVE_ESC_k:
    case EVE_INQ_CORRECT1:
    case EVE_INQ_CORRECT2:
    case EVE_INQ_CORRECT4:
    case EVE_PROGRAM_2:     Put(0, (uchar *) &tiRecordTime, sizeof(time));
  }

  CloseRecord(KEY_RECORD, i);

  return CloseOut();
}


bool    AddSysRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return true;

  uint i = OpenRecord(SYS_RECORD, cdwSysRecord);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwSysRecord++; SaveCache(&chSysRecord);
  reCurr.ev = ev;

  switch (ev)
  {
//    case EVE_CONTACTS3_START:
//    case EVE_CONTACTS3_COUNTER: memcpy(&reCurr.mpbBuff+0, &cbContact, sizeof(uchar));
//                                memcpy(&reCurr.mpbBuff+1, &cbContactMax, sizeof(uchar)); break;
//
//    case EVE_VALUE3_DOWN:     memcpy(&reCurr.mpbBuff+0, &reContactDown, sizeof(float)); break;
//    case EVE_VALUE3_UP:       memcpy(&reCurr.mpbBuff+0, &reContactUp, sizeof(float)); break;
//    case EVE_VALUE3_COUNTER:  memcpy(&reCurr.mpbBuff+0, &cbContactMax, sizeof(uchar)); break;
//
//    case EVE_CONTACTS3_0_ON:  memcpy(&reCurr.mpbBuff+0, &reContactRec, sizeof(float));
//                              memcpy(&reCurr.mpbBuff+4, &reContactUp, sizeof(float)); break;
//
//    case EVE_CONTACTS3_0_OFF: memcpy(&reCurr.mpbBuff+0, &reContactRec, sizeof(float));
//                              memcpy(&reCurr.mpbBuff+4, &reContactDown, sizeof(float)); break;
//
//    case EVE_CONTACTSMODE:
//    case EVE_CONTACTS1:
//    case EVE_CONTACTS2: memcpy(&reCurr.mpbBuff+0, &bContactRec, sizeof(uchar)); break;

    case EVE_PREVNEXTTIME2:   Put(0, (uchar *) &tiCurr, sizeof(time)); break;

    case EVE_EDIT_DIGITAL1:
    case EVE_EDIT_DIGITAL2:   PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpdiDigital[ibRecordCan], sizeof(digital)); break;

    case EVE_EDIT_KEY10:
    case EVE_EDIT_KEY20:      PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpphKeys[ibRecordCan].szLine+0, 7); break;

    case EVE_EDIT_KEY11:
    case EVE_EDIT_KEY21:      Put(0, (uchar *) &mpphKeys[ibRecordCan].szLine+7, 6); break;

    case EVE_EDIT_ADDRESS10:
    case EVE_EDIT_ADDRESS11:  PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpdwAddress1[ibRecordCan], sizeof(ulong)); break;

    case EVE_EDIT_ADDRESS20:
    case EVE_EDIT_ADDRESS21:  PutChar(0, ibRecordCan);
                              Put(1, (uchar *) &mpdwAddress2[ibRecordCan], sizeof(ulong)); break;
  }

  CloseRecord(SYS_RECORD, i);

  return CloseOut();
}


bool    AddSysRecordReprogram(event  ev)
{
  return (enGlobal == GLB_REPROGRAM) ? AddSysRecord(ev) : true;
}


bool    AddDigRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return true;

  uint i = OpenRecord2(AUX_RECORD, cdwAuxRecord);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwAuxRecord++; SaveCache(&chAuxRecord);
  reCurr.ev = ev;

  PutChar(0, ibDig);

  switch (ev)
  {
    case EVE_PROFILEOPEN:
    case EVE_SPECIALOPEN:   Put(1, (uchar *)&mpdiDigital[ibDig], sizeof(digital)); break;

//    case EVE_PROFILE:       memcpy(&reCurr.mpbBuff+1, &mpcwStopCan[ibDig], sizeof(uint)); break;

    case EVE_PROFILE2:      PutInt(0, mpcwStopCan[ibDig]);
                            PutInt(2, mpcwStopAuxCan[ibDig]); break;

//    case EVE_PROFILE_OK:    memcpy(&reCurr.mpbBuff+1, &cwHouRead, sizeof(uint));
//                            memcpy(&reCurr.mpbBuff+3, &mpcwStopCan[ibDig], sizeof(uint)); break;

    case EVE_PROFILE_OK2:   PutInt(0, cwHouRead);
                            PutInt(2, mpcwStopCan[ibDig]);
                            PutInt(4, mpcwStopAuxCan[ibDig]); break;

    case EVE_PROFILE_ERROR2:PutInt(1, GetCurr());
                            PutInt(3, mpSerial[ibPort]); break;

    case EVE_PROFILECLOSE2: PutInt(1, cwHouLength); break;

    case EVE_REFILL1:       PutInt(1, iwHardHou);
                            PutInt(3, iwBmin);
                            PutInt(5, iwBmax); break;

    case EVE_PREVIOUS_TOP:  PutInt(0, iwMajor); break;

    case EVE_CURRENT2_CANALS: Put(0, (uchar *)&mpbCurrent2Buff, 8); break;

    case EVE_CURRENT2_VALUE:  PutLong(1, dwRecord);
                              PutInt(5, wRecord); break;

//    case EVE_CHECKUP_START: memcpy(&reCurr.mpbBuff+0, &boCheckupReadonly, sizeof(uchar));
//                            memcpy(&reCurr.mpbBuff+1, &mpbCheckupLimitD[ibDig], sizeof(uchar));
//                            memcpy(&reCurr.mpbBuff+2, &mpbCheckupLimitM[ibDig], sizeof(uchar)); break;
//
//    case EVE_CHECKUP_NEXT:  memcpy(&reCurr.mpbBuff+0, &cwHouRead, sizeof(uint)); break;
//
//    case EVE_CHECKUP_VALUE: memcpy(&reCurr.mpbBuff+0, &dwBuffC, sizeof(ulong));
//                            memcpy(&reCurr.mpbBuff+4, &mpdwChannelsA[diPrev.ibLine], sizeof(ulong)); break;
//
//    case EVE_CHECKUP_DAY_SKIP:
//    case EVE_CHECKUP_MON_SKIP:
//    case EVE_CHECKUP_DAY_FAIL:
//    case EVE_CHECKUP_MON_FAIL:
//    case EVE_CHECKUP_DAY:
//    case EVE_CHECKUP_MON:   memcpy(&reCurr.mpbBuff+0, &daAlt, sizeof(date)); break;
//
//    case EVE_CHECKUP_CANAL: memcpy(&reCurr.mpbBuff+0, &ibCan, sizeof(uchar));
//                            memcpy(&reCurr.mpbBuff+1, &diPrev, sizeof(digital)); break;
//
//    case EVE_CHECKUP_DAY_NEXT:
//    case EVE_CHECKUP_MON_NEXT: memcpy(&reCurr.mpbBuff+0, &daAlt, sizeof(date));
//                               memcpy(&reCurr.mpbBuff+6, &ibGrp, sizeof(uchar)); break;
//
//    case EVE_CHECKUP_INFO:  memcpy(&reCurr.mpbBuff+0, &cbCheckupDays, sizeof(uchar));
//                            memcpy(&reCurr.mpbBuff+1, &cbCheckupErrorDay, sizeof(uchar));
//                            memcpy(&reCurr.mpbBuff+2, &cbCheckupErrorMon, sizeof(uchar)); break;
//
//    case EVE_DEVICE_P_DEFECT: memcpy(&reCurr.mpbBuff+0, &tiDig, sizeof(time)); break;

    case EVE_EXTENDED_0_ERROR: PutChar(0, bRecord);
                               PutChar(1, bExt0Counter);
                               PutChar(2, bExt0Limit); break;
  }

  CloseRecord(AUX_RECORD, i);

  return CloseOut();
}


bool    AddImpRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return true;

  uint i = OpenRecord(IMP_RECORD, cdwImpRecord);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwImpRecord++; SaveCache(&chImpRecord);
  reCurr.ev = ev;

  PutChar(0, ibDig);

  switch (ev)
  {
    case EVE_EVENTS_BADLINK:  PutChar(1, mpSerial[ibPort]);
                              PutChar(2, bEventCode);
                              break;

    case EVE_EVENTS_OMISSION: PutChar(1, bEventCode);
                              break;

    case EVE_EVENTS_A:
    case EVE_EVENTS_B:        Put(1, (uchar *) &tiRecordTime, sizeof(time));
                              PutChar(7, bEventCode);
                              break;
  }

  CloseRecord(IMP_RECORD, i);

  return CloseOut();
}


bool    AddModRecord(event  ev)
{
  if (IsRecordDisabled(ev)) return true;

  uint i = OpenRecord(MOD_RECORD, cdwModRecord);

  reCurr.ti = *GetCurrTimeDate();
  reCurr.cdwRecord = cdwModRecord++; SaveCache(&chModRecord);
  reCurr.ev = ev;

  PutChar(0, ibDig);

  switch (ev)
  {
    case EVE_MODEM_PROFILEOPEN:
    case EVE_MODEM_SPECIALOPEN:  Put(1, (uchar *) &mpdiDigital[ibDig], sizeof(digital)); break;

    case EVE_MODEM_PROFILE:      PutInt(1, mpcwStopCan[ibDig]); break;

    case EVE_MODEM_PROFILEOK:    PutInt(1, cwHouRead);
                                 PutInt(3, mpcwStopCan[ibDig]); break;

    case EVE_MODEM_PROFILEERROR2:PutInt(1, GetCurr());
                                 PutChar(3, mpSerial[ibPort]); break;
  }

  CloseRecord(MOD_RECORD, i);

  return CloseOut();
}
