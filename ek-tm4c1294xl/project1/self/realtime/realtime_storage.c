/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../flash/files.h"
#include "../nvram/23x1024.h"
#include "realtime_storage.h"



cache const             chRealtimeValues = {REALTIME_VALUES, &Realtime1, sizeof(Realtime1)};



bool    SavePointersMnt(void)
{
  tuple2uint tp = GetTuple2Uint(ibSoftMnt, iwHardMnt);
  return WriteNvramBuff(PTR_MNT, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersMnt(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_MNT, (uchar *) &tp, sizeof(tp));
  ibSoftMnt = tp.w1;
  iwHardMnt = tp.w2;
  return f;
}



bool    SavePointersHou(void)
{
  tuple2uint tp = GetTuple2Uint(ibSoftHou, iwHardHou);
  return WriteNvramBuff(PTR_HHR, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersHou(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_HHR, (uchar *) &tp, sizeof(tp));
  ibSoftHou = tp.w1;
  iwHardHou = tp.w2;
  return f;
}



bool    SavePointersDay(void)
{
  tuple2uint tp = GetTuple2Uint(ibSoftDay, ibHardDay);
  return WriteNvramBuff(PTR_DAY, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersDay(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_DAY, (uchar *) &tp, sizeof(tp));
  ibSoftDay = tp.w1;
  ibHardDay = tp.w2;
  return f;
}



bool    SavePointersMon(void)
{
  tuple2uint tp = GetTuple2Uint(ibSoftMon, ibHardMon);
  return WriteNvramBuff(PTR_MON, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersMon(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_MON, (uchar *) &tp, sizeof(tp));
  ibSoftMon = tp.w1;
  ibHardMon = tp.w2;
  return f;
}



bool    SavePointersTim(void)
{
  tuple2uint tp = GetTuple2Uint(ibSoftTim, iwHardTim);
  return WriteNvramBuff(PTR_TIM, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersTim(void)
{
  tuple2uint tp;
  bool f = ReadNvramBuff(PTR_TIM, (uchar *) &tp, sizeof(tp));
  ibSoftTim = tp.w1;
  iwHardTim = tp.w2;
  return f;
}



bool    SaveRealtimeTimes(void)
{
  tuple2time tp = GetTuple2Time(tiCurr, tiPrev);
  return WriteNvramBuff(REALTIME_TIMES, (uchar *) &tp, sizeof(tp));
}


bool    LoadRealtimeTimes(void)
{
	tuple2time tp;
  bool f = ReadNvramBuff(REALTIME_TIMES, (uchar *) &tp, sizeof(tp));
  tiCurr = tp.ti1;
  tiPrev = tp.ti2;
  return f;
}
