/*------------------------------------------------------------------------------
entity.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/storage.h"
#include "entity.h"



ulong SaveEntity(const entity * const pen)
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
