/*------------------------------------------------------------------------------
entity.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/storage.h"
#include "settings.h"
#include "entity.h"



static ulong SaveEntityInner(const entity * const pen)
{
  switch(pen->eType)
  {
    case CHAR: return SaveChar(pen->pbRam, pen->dwEepRom);
    case INT: return SaveInt(pen->pbRam, pen->dwEepRom);
    case IP: return SaveLong(pen->pbRam, pen->dwEepRom);
    case STRING: return SaveString(pen->pbRam, pen->dwEepRom);
    default: ASSERT(false); return MAX_LONG;
  }
}

ulong SaveEntity(const entity * const pen)
{
  const ulong code = SaveEntityInner(pen);
  if (code != 0)
    cwErrSettingsSaveEntity++;

  return code;
}



void LoadEntity(const entity * const pen)
{
  switch(pen->eType)
  {
    case CHAR: LoadChar(pen->pbRam, pen->dwEepRom); break;
    case INT: LoadInt(pen->pbRam, pen->dwEepRom); break;
    case IP: LoadLong(pen->pbRam, pen->dwEepRom); break;
    case STRING: LoadString(pen->pbRam, pen->dwEepRom); break;
    default: ASSERT(false); break;
  }
}


void LoadEntityDef(const entity * const pen)
{
  switch(pen->eType)
  {
    case CHAR: *(uchar *)pen->pbRam = pen->dwDef; break;
    case INT: *(uint *)pen->pbRam = pen->dwDef; break;
    case IP: *(ulong *)pen->pbRam = pen->dwDef; break;
    case STRING: memset(pen->pbRam, 0, NAME_SIZE); break;
    default: ASSERT(false); break;
  }
}


#if false
bool TODO CheckEntity(const entity * const pen)
{
  switch(pen->eType)
  {
    case CHAR:
    {
      uchar *pb = (uchar *)pen->pbRam;
      if ((*pb >= pen->dwMin) && (*pb <= pen->dwMin))
        return true;
      else
      {
        *pb = pen->dwDef;
        return false;
      }
    }
    case INT:
    {
      uint *pw = (uint *)pen->pbRam;
      if ((*pw >= pen->dwMin) && (*pw <= pen->dwMin))
        return true;
      else
      {
        *pw = pen->dwDef;
        return false;
      }
    }
    case IP:
    {
      ulong *pdw = (ulong *)pen->pbRam;
      if ((*pdw >= pen->dwMin) && (*pdw <= pen->dwMin))
        return true;
      else
      {
        *pdw = pen->dwDef;
        return false;
      }
    }
    case STRING: return true;
    default: ASSERT(false); return true;
  }
}
#endif
