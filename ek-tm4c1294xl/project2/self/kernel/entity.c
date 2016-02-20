/*------------------------------------------------------------------------------
entity,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/storage.h"
#include "entity.h"



err_t SaveEntity(const entity * const pen)
{
  switch(pen->eType)
  {
    case CHAR: return LoadResult(SaveChar(pen->pbRam, pen->dwEepRom));
    case INT: return LoadResult(SaveInt(pen->pbRam, pen->dwEepRom));
    case IP: return LoadResult(SaveLong(pen->pbRam, pen->dwEepRom));
    case STRING: return LoadResult(SaveString(pen->pbRam, pen->dwEepRom));
    default: ASSERT(false); return ERR_ARG;
  }
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
