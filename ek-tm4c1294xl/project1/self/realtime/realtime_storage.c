/*------------------------------------------------------------------------------
REALTIME_STORAGE!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../flash/files.h"
#include "../nvram/23x1024.h"
#include "realtime_storage.h"



cache const             chRealtimeValues = {REALTIME_VALUES, &Realtime1, sizeof(Realtime1)};



bool    SavePointersMnt(void)
{
  t2uint tp = GetTuple2Int(ibSoftMnt, iwHardMnt);
  return WriteNvramBuff(PTR_MNT, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersMnt(void)
{
  t2uint tp;
  bool f = ReadNvramBuff(PTR_MNT, (uchar *) &tp, sizeof(tp));
  ibSoftMnt = tp.w1;
  iwHardMnt = tp.w2;
  return f;
}



bool    SavePointersHou(void)
{
  t2uint tp = GetTuple2Int(ibSoftHou, iwHardHou);
  return WriteNvramBuff(PTR_HHR, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersHou(void)
{
  t2uint tp;
  bool f = ReadNvramBuff(PTR_HHR, (uchar *) &tp, sizeof(tp));
  ibSoftHou = tp.w1;
  iwHardHou = tp.w2;
  return f;
}



bool    SavePointersDay(void)
{
  t2uint tp = GetTuple2Int(ibSoftDay, ibHardDay);
  return WriteNvramBuff(PTR_DAY, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersDay(void)
{
  t2uint tp;
  bool f = ReadNvramBuff(PTR_DAY, (uchar *) &tp, sizeof(tp));
  ibSoftDay = tp.w1;
  ibHardDay = tp.w2;
  return f;
}



bool    SavePointersMon(void)
{
  t2uint tp = GetTuple2Int(ibSoftMon, ibHardMon);
  return WriteNvramBuff(PTR_MON, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersMon(void)
{
  t2uint tp;
  bool f = ReadNvramBuff(PTR_MON, (uchar *) &tp, sizeof(tp));
  ibSoftMon = tp.w1;
  ibHardMon = tp.w2;
  return f;
}



bool    SavePointersTim(void)
{
  t2uint tp = GetTuple2Int(ibSoftTim, iwHardTim);
  return WriteNvramBuff(PTR_TIM, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersTim(void)
{
  t2uint tp;
  bool f = ReadNvramBuff(PTR_TIM, (uchar *) &tp, sizeof(tp));
  ibSoftTim = tp.w1;
  iwHardTim = tp.w2;
  return f;
}



bool    SavePointersDgr(void)
{
  t2uint tp = GetTuple2Int(ibSoftDgr, iwHardDgr);
  return WriteNvramBuff(PTR_DIAGRAM, (uchar *) &tp, sizeof(tp));
}


bool    LoadPointersDgr(void)
{
  t2uint tp;
  bool f = ReadNvramBuff(PTR_DIAGRAM, (uchar *) &tp, sizeof(tp));
  ibSoftDgr = tp.w1;
  iwHardDgr = tp.w2;
  return f;
}



bool    SaveRealtimeTimes(void)
{
  t2time tp = GetTuple2Time(tiCurr, tiPrev);
  return WriteNvramBuff(REALTIME_TIMES, (uchar *) &tp, sizeof(tp));
}


bool    LoadRealtimeTimes(void)
{
	t2time tp;
  bool f = ReadNvramBuff(REALTIME_TIMES, (uchar *) &tp, sizeof(tp));
  tiCurr = tp.ti1;
  tiPrev = tp.ti2;
  return f;
}
