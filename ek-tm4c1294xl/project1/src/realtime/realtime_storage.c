/*------------------------------------------------------------------------------
REALTIME_STORAGE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../flash/files.h"



boolean SavePointersMnt(void)
{
  OpenOut(DF_PTRMNT);

  if (Save(ibSoftMnt, sizeof(uchar), FOR_DEFAULT) == FALSE)
    return FALSE;

  return CloseOut(FOR_DEFAULT);
}


boolean LoadBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenIn(wPage);
  return Load(pbBuff, wSize);
}
