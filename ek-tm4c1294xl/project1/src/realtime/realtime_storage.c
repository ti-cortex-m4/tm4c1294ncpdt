/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../flash/files.h"



boolean SavePointersMnt(void)
{
  OpenOut(FLS_PTRMNT);
  ClearOut();

  if (Save(&ibSoftMnt, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&ibHardMnt, sizeof(uchar)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersMnt(void)
{
  OpenIn(FLS_PTRMNT);

  if (Load(&ibSoftMnt, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&ibHardMnt, sizeof(uchar));
}



boolean SavePointersHou(void)
{
  OpenOut(FLS_PTRHOU);
  ClearOut();

  if (Save(&ibSoftHou, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&iwHardHou, sizeof(uint)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersHou(void)
{
  OpenIn(FLS_PTRHOU);

  if (Load(&ibSoftHou, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&iwHardHou, sizeof(uint));
}



boolean SavePointersDay(void)
{
  OpenOut(FLS_PTRDAY);
  ClearOut();

  if (Save(&ibSoftDay, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&ibHardDay, sizeof(uchar)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersDay(void)
{
  OpenIn(FLS_PTRDAY);

  if (Load(&ibSoftDay, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&ibHardDay, sizeof(uchar));
}



boolean SavePointersMon(void)
{
  OpenOut(FLS_PTRMON);
  ClearOut();

  if (Save(&ibSoftMon, sizeof(uchar)) == FALSE)
    return FALSE;

  if (Save(&ibHardMon, sizeof(uchar)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadPointersMon(void)
{
  OpenIn(FLS_PTRMON);

  if (Load(&ibSoftMon, sizeof(uchar)) == FALSE)
    return FALSE;

  return Load(&ibHardMon, sizeof(uchar));
}



boolean SaveTimeCurr(void)
{
  OpenOut(FLS_TICURR);
  ClearOut();

  if (Save(&tiCurr, sizeof(time)) == FALSE)
    return FALSE;

  if (Save(&tiPrev, sizeof(time)) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadTimeCurr(void)
{
  OpenIn(FLS_TICURR);

  if (Load(&tiCurr, sizeof(time)) == FALSE)
    return FALSE;

  return Load(&tiPrev, sizeof(time));
}
