/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../flash/files.h"
#include "../nvram/23x1024.h"



bool    SavePointersMnt(void)
{
  tuple2uint tp = GetTuple2(ibSoftMnt, iwHardMnt);
  return WriteNvramBuff(PTR_MNT, (uchar *) &tp, sizeof(tuple2uint));
}


bool    LoadPointersMnt(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_MNT, (uchar *) &tp, sizeof(tuple2uint));
  ibSoftMnt = tp.w1;
  iwHardMnt = tp.w2;
  return f;
}



bool    SavePointersHou(void)
{
  tuple2uint tp = GetTuple2(ibSoftHou, iwHardHou);
  return WriteNvramBuff(PTR_HHR, (uchar *) &tp, sizeof(tuple2uint));
}


bool    LoadPointersHou(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_HHR, (uchar *) &tp, sizeof(tuple2uint));
  ibSoftHou = tp.w1;
  iwHardHou = tp.w2;
  return f;
}



bool    SavePointersDay(void)
{
  tuple2uint tp = GetTuple2(ibSoftDay, ibHardDay);
  return WriteNvramBuff(PTR_DAY, (uchar *) &tp, sizeof(tuple2uint));
}


bool    LoadPointersDay(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_DAY, (uchar *) &tp, sizeof(tuple2uint));
  ibSoftDay = tp.w1;
  ibHardDay = tp.w2;
  return f;
}



bool    SavePointersMon(void)
{
  tuple2uint tp = GetTuple2(ibSoftMon, ibHardMon);
  return WriteNvramBuff(PTR_MON, (uchar *) &tp, sizeof(tuple2uint));
}


bool    LoadPointersMon(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_MON, (uchar *) &tp, sizeof(tuple2uint));
  ibSoftMon = tp.w1;
  ibHardMon = tp.w2;
  return f;
}



bool    SavePointersTim(void)
{
  tuple2uint tp = GetTuple2(ibSoftTim, iwHardTim);
  return WriteNvramBuff(PTR_TIM, (uchar *) &tp, sizeof(tuple2uint));
}


bool    LoadPointersTim(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_TIM, (uchar *) &tp, sizeof(tuple2uint));
  ibSoftTim = tp.w1;
  iwHardTim = tp.w2;
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
