/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "settings.h"



#define EEPROM_ADDR_IP      0
#define EEPROM_ADDR_GATEWAY 4
#define EEPROM_ADDR_NETMASK 8
#define EEPROM_ADDR_PORT    12



ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;

uint                    wPort;

uchar                   pbMAC[6];



uchar   InitSettings(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

  uchar err = EEPROMInit();
  if (err != EEPROM_INIT_OK) return err;

  return LoadSettings();
}



static uchar SaveLong(ulong *pdw, ulong dwAddr)
{
  return EEPROMProgram(pdw, dwAddr, 4);
}


static uchar SaveInt(uint *pw, ulong dwAddr)
{
  ulong dw = *pw;
  return EEPROMProgram(&dw, dwAddr, 4);
}


uchar    SaveSettings(void)
{
  uchar err = SaveLong(&dwIP, EEPROM_ADDR_IP);
  if (err != 0) return err;

  err = SaveLong(&dwGateway, EEPROM_ADDR_GATEWAY);
  if (err != 0) return err;

  err = SaveLong(&dwNetmask, EEPROM_ADDR_NETMASK);
  if (err != 0) return err;

  err = SaveInt(&wPort, EEPROM_ADDR_PORT);
  if (err != 0) return err;

  return 0;
}



static void LoadLong(ulong *pdw, ulong dwAddr)
{
  EEPROMRead(pdw, dwAddr, 4);
}


static void LoadInt(uint *pw, ulong dwAddr)
{
  ulong dw;
  EEPROMRead(&dw, dwAddr, 4);
  *pw = dw % 0x10000;
}


uchar   LoadSettings(void)
{
  LoadLong(&dwIP, EEPROM_ADDR_IP);

  LoadLong(&dwGateway, EEPROM_ADDR_GATEWAY);

  LoadLong(&dwNetmask, EEPROM_ADDR_NETMASK);

  LoadInt(&wPort, EEPROM_ADDR_PORT);

  return 0;
}
