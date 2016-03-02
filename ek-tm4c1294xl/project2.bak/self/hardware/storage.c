/*------------------------------------------------------------------------------
storage.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "storage.h"



ulong InitStorage(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
  return EEPROMInit();
}



ulong SaveChar(uchar *pb, ulong dwEepRom)
{
  ulong dw = *pb;
  return EEPROMProgram(&dw, dwEepRom, 4);
}

ulong SaveInt(uint *pw, ulong dwEepRom)
{
  ulong dw = *pw;
  return EEPROMProgram(&dw, dwEepRom, 4);
}

ulong SaveLong(ulong *pdw, ulong dwEepRom)
{
  return EEPROMProgram(pdw, dwEepRom, 4);
}

ulong SaveString(char *sz, ulong dwEepRom)
{
  return EEPROMProgram((ulong *)sz, dwEepRom, 4*3);
}



void LoadChar(uchar *pb, ulong dwEepRom)
{
  ulong dw;
  EEPROMRead(&dw, dwEepRom, 4);
  *pb = dw % 0x100;
}

void LoadInt(uint *pw, ulong dwEepRom)
{
  ulong dw;
  EEPROMRead(&dw, dwEepRom, 4);
  *pw = dw % 0x10000;
}

void LoadLong(ulong *pdw, ulong dwEepRom)
{
  EEPROMRead(pdw, dwEepRom, 4);
}

void LoadString(char *sz, ulong dwEepRom)
{
  EEPROMRead((ulong *)sz, dwEepRom, 4*3);
}
