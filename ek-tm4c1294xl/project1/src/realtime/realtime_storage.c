/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../flash/files.h"



boolean SavePointersMnt(void)
{
  OpenOut(FLS_PTRMNT);

  if (Save(&ibSoftMnt, sizeof(uchar), FRM_DEFAULT) == FALSE)
    return FALSE;

  return CloseOut(FRM_DEFAULT);
}


boolean LoadPointersMnt(void)
{
  OpenIn(FLS_PTRMNT);
  return Load(&ibSoftMnt, sizeof(uchar));
}



boolean SavePointersHou(void)
{
  OpenOut(FLS_PTRHOU);

  if (Save(&ibSoftHou, sizeof(uchar), FRM_DEFAULT) == FALSE)
    return FALSE;

  if (Save(&iwHardHou, sizeof(uint), FRM_DEFAULT) == FALSE)
    return FALSE;

  return CloseOut(FRM_DEFAULT);
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

  if (Save(&ibSoftDay, sizeof(uchar), FRM_DEFAULT) == FALSE)
    return FALSE;

  if (Save(&ibHardDay, sizeof(uchar), FRM_DEFAULT) == FALSE)
    return FALSE;

  return CloseOut(FRM_DEFAULT);
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

  if (Save(&ibSoftMon, sizeof(uchar), FRM_DEFAULT) == FALSE)
    return FALSE;

  if (Save(&ibHardMon, sizeof(uchar), FRM_DEFAULT) == FALSE)
    return FALSE;

  return CloseOut(FRM_DEFAULT);
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
  return SaveBuff(FLS_TICURR, &tiCurr, sizeof(time), FRM_DEFAULT);
}


boolean LoadTimeCurr(void)
{
  return LoadBuff(FLS_TICURR, &tiCurr, sizeof(time));
}
