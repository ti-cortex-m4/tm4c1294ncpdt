/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../flash/files.h"



bool SavePointersMnt(void)
{
  OpenOut(PTRMNT);
  ClearOut();

  if (Save(&ibSoftMnt, sizeof(uchar)) == false)
    return false;

  if (Save(&ibHardMnt, sizeof(uchar)) == false)
    return false;

  return CloseOut();
}


bool LoadPointersMnt(void)
{
  OpenIn(PTRMNT);

  if (Load(&ibSoftMnt, sizeof(uchar)) == false)
    return false;

  return Load(&ibHardMnt, sizeof(uchar));
}



bool SavePointersHou(void)
{
  OpenOut(PTRHOU);
  ClearOut();

  if (Save(&ibSoftHou, sizeof(uchar)) == false)
    return false;

  if (Save(&iwHardHou, sizeof(uint)) == false)
    return false;

  return CloseOut();
}


bool LoadPointersHou(void)
{
  OpenIn(PTRHOU);

  if (Load(&ibSoftHou, sizeof(uchar)) == false)
    return false;

  return Load(&iwHardHou, sizeof(uint));
}



bool SavePointersDay(void)
{
  OpenOut(PTRDAY);
  ClearOut();

  if (Save(&ibSoftDay, sizeof(uchar)) == false)
    return false;

  if (Save(&ibHardDay, sizeof(uchar)) == false)
    return false;

  return CloseOut();
}


bool LoadPointersDay(void)
{
  OpenIn(PTRDAY);

  if (Load(&ibSoftDay, sizeof(uchar)) == false)
    return false;

  return Load(&ibHardDay, sizeof(uchar));
}



bool SavePointersMon(void)
{
  OpenOut(PTRMON);
  ClearOut();

  if (Save(&ibSoftMon, sizeof(uchar)) == false)
    return false;

  if (Save(&ibHardMon, sizeof(uchar)) == false)
    return false;

  return CloseOut();
}


bool LoadPointersMon(void)
{
  OpenIn(PTRMON);

  if (Load(&ibSoftMon, sizeof(uchar)) == false)
    return false;

  return Load(&ibHardMon, sizeof(uchar));
}



bool SavePointersTim(void)
{
  OpenOut(PTRTIM);
  ClearOut();

  if (Save(&ibSoftTim, sizeof(uchar)) == false)
    return false;

  if (Save(&iwHardTim, sizeof(uint)) == false)
    return false;

  return CloseOut();
}


bool LoadPointersTim(void)
{
  OpenIn(PTRTIM);

  if (Load(&ibSoftTim, sizeof(uchar)) == false)
    return false;

  return Load(&iwHardTim, sizeof(uint));
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
