/*------------------------------------------------------------------------------
entity,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/storage.h"
#include "entity.h"



static err_t Result(ulong dw)
{
  return (dw == 0) ? ERR_OK : ERR_VAL;
}

err_t SaveEntity(const entity * const pen)
{
  switch(pen->eType)
  {
    case CHAR: return Result(SaveChar(pen->pbRam, pen->dwEepRom));
    case INT: return Result(SaveInt(pen->pbRam, pen->dwEepRom));
    case IP: return Result(SaveLong(pen->pbRam, pen->dwEepRom));
    case STRING: return Result(SaveString(pen->pbRam, pen->dwEepRom));
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
