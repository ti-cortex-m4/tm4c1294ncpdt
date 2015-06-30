/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../flash/files.h"
#include "../nvram/23x1024.h"



bool    SavePointersMnt(void)
{
  tuple2 tp2 = GetTuple2(ibSoftMnt, iwHardMnt);
  return WriteNvramBuff(PTR_MNT, (uchar *) &tp2, sizeof(tuple2));
}


bool    LoadPointersMnt(void)
{
  tuple2 tp2;
  bool f = ReadNvramBuff(PTR_MNT, (uchar *) &tp2, sizeof(tuple2));
  ibSoftMnt = tp2.w1;
  iwHardMnt = tp2.w2;
  return f;
}



bool    SavePointersHou(void)
{
  tuple2 tp2 = GetTuple2(ibSoftHou, iwHardHou);
  return WriteNvramBuff(PTR_HHR, (uchar *) &tp2, sizeof(tuple2));
}


bool    LoadPointersHou(void)
{
  tuple2 tp2;
  bool f = ReadNvramBuff(PTR_HHR, (uchar *) &tp2, sizeof(tuple2));
  ibSoftHou = tp2.w1;
  iwHardHou = tp2.w2;
  return f;
}



bool    SavePointersDay(void)
{
  tuple2 tp2 = GetTuple2(ibSoftDay, ibHardDay);
  return WriteNvramBuff(PTR_DAY, (uchar *) &tp2, sizeof(tuple2));
}


bool    LoadPointersDay(void)
{
  tuple2 tp2;
  bool f = ReadNvramBuff(PTR_DAY, (uchar *) &tp2, sizeof(tuple2));
  ibSoftDay = tp2.w1;
  ibHardDay = tp2.w2;
  return f;
}



bool    SavePointersMon(void)
{
  tuple2 tp2 = GetTuple2(ibSoftMon, ibHardMon);
  return WriteNvramBuff(PTR_MON, (uchar *) &tp2, sizeof(tuple2));
}


bool    LoadPointersMon(void)
{
  tuple2 tp2;
  bool f = ReadNvramBuff(PTR_MON, (uchar *) &tp2, sizeof(tuple2));
  ibSoftMon = tp2.w1;
  ibHardMon = tp2.w2;
  return f;
}



bool    SavePointersTim(void)
{
  tuple2 tp2 = GetTuple2(ibSoftTim, iwHardTim);
  return WriteNvramBuff(PTR_TIM, (uchar *) &tp2, sizeof(tuple2));
}


bool    LoadPointersTim(void)
{
  tuple2 tp2;
  bool f = ReadNvramBuff(PTR_TIM, (uchar *) &tp2, sizeof(tuple2));
  ibSoftTim = tp2.w1;
  iwHardTim = tp2.w2;
  return f;
}



bool SaveTimeCurr(void)
{
  OpenOut(REALTIME);
  ClearOut();

  if (Save(&tiCurr, sizeof(time)) == false) return false;
  if (Save(&tiPrev, sizeof(time)) == false) return false;

  if (Save(&cdwSeconds, sizeof(ulong)) == false) return false;
  if (Save(&cdwMinutes1, sizeof(ulong)) == false) return false;
  if (Save(&cdwMinutes3, sizeof(ulong)) == false) return false;
  if (Save(&cdwMinutes30, sizeof(ulong)) == false) return false;

  if (Save(&cwDays, sizeof(uint)) == false) return false;
  if (Save(&cwMonths, sizeof(uint)) == false) return false;
  if (Save(&cwYears, sizeof(uint)) == false) return false;

  return CloseOut();
}


bool LoadTimeCurr(void)
{
  OpenIn(REALTIME);

  if (Load(&tiCurr, sizeof(time)) == false) return false;
  if (Load(&tiPrev, sizeof(time)) == false) return false;

  if (Load(&cdwSeconds, sizeof(ulong)) == false) return false;
  if (Load(&cdwMinutes1, sizeof(ulong)) == false) return false;
  if (Load(&cdwMinutes3, sizeof(ulong)) == false) return false;
  if (Load(&cdwMinutes30, sizeof(ulong)) == false) return false;

  if (Load(&cwDays, sizeof(uint)) == false) return false;
  if (Load(&cwMonths, sizeof(uint)) == false) return false;
  if (Load(&cwYears, sizeof(uint)) == false) return false;

  return true;
}
