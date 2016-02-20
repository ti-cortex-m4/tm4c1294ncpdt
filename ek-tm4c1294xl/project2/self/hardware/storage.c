/*------------------------------------------------------------------------------
storage,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/eeprom.h"
#include "../kernel/entities.h"
#include "storage.h"



static ulong SaveChar(uchar *pb, ulong dwEepRom)
{
  ulong dw = *pb;
  return EEPROMProgram(&dw, dwEepRom, 4);
}

static ulong SaveInt(uint *pw, ulong dwEepRom)
{
  ulong dw = *pw;
  return EEPROMProgram(&dw, dwEepRom, 4);
}

ulong SaveLong(ulong *pdw, ulong dwEepRom)
{
  return EEPROMProgram(pdw, dwEepRom, 4);
}

static ulong SaveString(char *sz, ulong dwEepRom)
{
  return EEPROMProgram((ulong *)sz, dwEepRom, 4*3);
}


err_t SaveEntity(entity const *pen)
{
  switch(pen->eType)
  {
    case CHAR: return SaveChar(pen->pbRam, pen->dwEepRom);
    case INT: return SaveInt(pen->pbRam, pen->dwEepRom);
    case IP: return SaveLong(pen->pbRam, pen->dwEepRom);
    case STRING: return SaveString(pen->pbRam, pen->dwEepRom);
    default: ASSERT(false); return 0x80;
  }
}



static void LoadChar(uchar *pb, ulong dwEepRom)
{
  ulong dw;
  EEPROMRead(&dw, dwEepRom, 4);
  *pb = dw % 0x100;
}

static void LoadInt(uint *pw, ulong dwEepRom)
{
  ulong dw;
  EEPROMRead(&dw, dwEepRom, 4);
  *pw = dw % 0x10000;
}

void LoadLong(ulong *pdw, ulong dwEepRom)
{
  EEPROMRead(pdw, dwEepRom, 4);
}

static void LoadString(char *sz, ulong dwEepRom)
{
  EEPROMRead((ulong *)sz, dwEepRom, 4*3);
}


void LoadEntity(entity const *pen)
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
