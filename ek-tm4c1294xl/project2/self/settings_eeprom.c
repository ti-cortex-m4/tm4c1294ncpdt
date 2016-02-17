/*------------------------------------------------------------------------------
SETTINGS_EEPROM.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "driverlib/eeprom.h"
#include "kernel/entity.h"
#include "settings_eeprom.h"



uchar SaveChar(uchar *pb, ulong dwAddr)
{
  ulong dw = *pb;
  return EEPROMProgram(&dw, dwAddr, 4);
}

uchar SaveInt(uint *pw, ulong dwAddr)
{
  ulong dw = *pw;
  return EEPROMProgram(&dw, dwAddr, 4);
}

uchar SaveLong(ulong *pdw, ulong dwAddr)
{
  return EEPROMProgram(pdw, dwAddr, 4);
}

uchar SaveString(char *sz, ulong dwAddr)
{
  return EEPROMProgram((ulong *)sz, dwAddr, 4*3);
}

uchar SaveEntity(entity const *pen) // TODO min max def
{
  switch(pen->eType)
  {
    case CHAR: return SaveChar(pen->pbRAM, pen->dwEEPROM);
    case INT: return SaveInt(pen->pbRAM, pen->dwEEPROM);
    case LONG: return SaveLong(pen->pbRAM, pen->dwEEPROM);
    default: ASSERT(false); return 0x80;
  }
}


void LoadChar(uchar *pb, ulong dwAddr)
{
  ulong dw;
  EEPROMRead(&dw, dwAddr, 4);
  *pb = dw % 0x100;
}

void LoadInt(uint *pw, ulong dwAddr)
{
  ulong dw;
  EEPROMRead(&dw, dwAddr, 4);
  *pw = dw % 0x10000;
}

void LoadLong(ulong *pdw, ulong dwAddr)
{
  EEPROMRead(pdw, dwAddr, 4);
}

void LoadString(char *sz, ulong dwAddr)
{
  EEPROMRead((ulong *)sz, dwAddr, 4*3);
}

void LoadEntity(entity const *pen) // TODO min max def
{
  switch(pen->eType)
  {
    case CHAR: LoadChar(pen->pbRAM, pen->dwEEPROM); break;
    case INT: LoadInt(pen->pbRAM, pen->dwEEPROM); break;
    case LONG: LoadLong(pen->pbRAM, pen->dwEEPROM); break;
    default: ASSERT(false); break;
  }
}
