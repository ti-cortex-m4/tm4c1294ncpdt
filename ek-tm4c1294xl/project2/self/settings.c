/*------------------------------------------------------------------------------
SETTINGS.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "generated/eeprom.h"
#include "settings.h"



ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;

char                    szDeviceName[NAME_SIZE];
char                    szOwnerName[NAME_SIZE];

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


static uchar SaveString(char *sz, ulong dwAddr)
{
  return EEPROMProgram((ulong *)sz, dwAddr, 4*3);
}


uchar SaveDeviceName(void) // TODO
{
  uchar err = SaveString(szDeviceName, EEPROM_DEVICE_NAME);
  if (err != 0) return err;

  return 0;
}


uchar SaveOwnerName(void) // TODO
{
  uchar err = SaveString(szOwnerName, EEPROM_OWNER_NAME);
  if (err != 0) return err;

  return 0;
}


uchar    SaveSettings(void)
{
  uchar err = SaveLong(&dwIP, EEPROM_IP);
  if (err != 0) return err;

  err = SaveLong(&dwGateway, EEPROM_GATEWAY);
  if (err != 0) return err;

  err = SaveLong(&dwNetmask, EEPROM_NETMASK);
  if (err != 0) return err;


  err = SaveInt(&wPort, EEPROM_PORT);
  if (err != 0) return err;


  err = SaveString(szDeviceName, EEPROM_DEVICE_NAME);
  if (err != 0) return err;

  err = SaveString(szOwnerName, EEPROM_OWNER_NAME);
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


static void LoadString(char *sz, ulong dwAddr)
{
  EEPROMRead((ulong *)sz, dwAddr, 4*3);
}



uchar   LoadSettings(void)
{
  LoadLong(&dwIP, EEPROM_IP);
  LoadLong(&dwGateway, EEPROM_GATEWAY);
  LoadLong(&dwNetmask, EEPROM_NETMASK);

  LoadInt(&wPort, EEPROM_PORT);

  LoadString(szDeviceName, EEPROM_DEVICE_NAME);
  LoadString(szOwnerName, EEPROM_OWNER_NAME);

  return 0;
}
