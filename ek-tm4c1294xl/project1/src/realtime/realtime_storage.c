/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../flash/files.h"



boolean SavePointersMnt(void)
{
  OpenOut(PTRMNT);
  ClearOut();

  if (Save(&ibSoftMnt, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&ibHardMnt, sizeof(uchar)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersMnt(void)
{
  OpenIn(PTRMNT);

  if (Load(&ibSoftMnt, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&ibHardMnt, sizeof(uchar));
}



boolean SavePointersHou(void)
{
  OpenOut(PTRHOU);
  ClearOut();

  if (Save(&ibSoftHou, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&iwHardHou, sizeof(uint)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersHou(void)
{
  OpenIn(PTRHOU);

  if (Load(&ibSoftHou, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&iwHardHou, sizeof(uint));
}



boolean SavePointersDay(void)
{
  OpenOut(PTRDAY);
  ClearOut();

  if (Save(&ibSoftDay, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&ibHardDay, sizeof(uchar)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersDay(void)
{
  OpenIn(PTRDAY);

  if (Load(&ibSoftDay, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&ibHardDay, sizeof(uchar));
}



boolean SavePointersMon(void)
{
  OpenOut(PTRMON);
  ClearOut();

  if (Save(&ibSoftMon, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&ibHardMon, sizeof(uchar)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersMon(void)
{
  OpenIn(PTRMON);

  if (Load(&ibSoftMon, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&ibHardMon, sizeof(uchar));
}



boolean SavePointersTim(void)
{
  OpenOut(PTRTIM);
  ClearOut();

  if (Save(&ibSoftTim, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&iwHardTim, sizeof(uint)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersTim(void)
{
  OpenIn(PTRTIM);

  if (Load(&ibSoftTim, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&iwHardTim, sizeof(uint));
}



boolean SaveTimeCurr(void)
{
  OpenOut(REALTIME);
  ClearOut();

  if (Save(&tiCurr, sizeof(time)) == FALSE) return FALSE;
  if (Save(&tiPrev, sizeof(time)) == FALSE) return FALSE;

  if (Save(&cdwSeconds, sizeof(ulong)) == FALSE) return FALSE;
  if (Save(&cdwMinutes1, sizeof(ulong)) == FALSE) return FALSE;
  if (Save(&cdwMinutes3, sizeof(ulong)) == FALSE) return FALSE;
  if (Save(&cdwMinutes30, sizeof(ulong)) == FALSE) return FALSE;

  if (Save(&cwDays, sizeof(uint)) == FALSE) return FALSE;
  if (Save(&cwMonths, sizeof(uint)) == FALSE) return FALSE;
  if (Save(&cwYears, sizeof(uint)) == FALSE) return FALSE;

  return CloseOut();
}


boolean LoadTimeCurr(void)
{
  OpenIn(REALTIME);

  if (Load(&tiCurr, sizeof(time)) == FALSE) return FALSE;
  if (Load(&tiPrev, sizeof(time)) == FALSE) return FALSE;

  if (Load(&cdwSeconds, sizeof(ulong)) == FALSE) return FALSE;
  if (Load(&cdwMinutes1, sizeof(ulong)) == FALSE) return FALSE;
  if (Load(&cdwMinutes3, sizeof(ulong)) == FALSE) return FALSE;
  if (Load(&cdwMinutes30, sizeof(ulong)) == FALSE) return FALSE;

  if (Load(&cwDays, sizeof(uint)) == FALSE) return FALSE;
  if (Load(&cwMonths, sizeof(uint)) == FALSE) return FALSE;
  if (Load(&cwYears, sizeof(uint)) == FALSE) return FALSE;

  return TRUE;
}
