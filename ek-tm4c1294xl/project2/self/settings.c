/*------------------------------------------------------------------------------
SETTINGS.C

TODO
------------------------------------------------------------------------------*/

#include "main.h"
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "lwip/inet.h"
#include "generated/eeprom.h"
#include "settings.h"



#define LABEL           0xC0FEBABE

ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;

char                    szDeviceName[NAME_SIZE];
char                    szOwnerName[NAME_SIZE];

uint                    wPort;

uchar                   ibBaud;

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


uchar SaveIP(void)
{
  return SaveLong(&dwIP, EEPROM_IP);
}

uchar SaveGateway(void)
{
  return SaveLong(&dwGateway, EEPROM_GATEWAY);
}

uchar SaveNetmask(void)
{
  return SaveLong(&dwNetmask, EEPROM_NETMASK);
}

uchar SaveDeviceName(void)
{
  return SaveString(szDeviceName, EEPROM_DEVICE_NAME);
}

uchar SaveOwnerName(void)
{
  return SaveString(szOwnerName, EEPROM_OWNER_NAME);
}


uchar    SaveSettings(void)
{
  ulong dw = LABEL;
  uchar err = SaveLong(&dw, EEPROM_LABEL);
  if (err != 0) return err;


  err = SaveLong(&dwIP, EEPROM_IP);
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
  ulong dw = 0;
  LoadLong(&dw, EEPROM_LABEL);

  if (dw == LABEL)
  {
    LoadLong(&dwIP, EEPROM_IP);
    LoadLong(&dwGateway, EEPROM_GATEWAY);
    LoadLong(&dwNetmask, EEPROM_NETMASK);

    LoadInt(&wPort, EEPROM_PORT);

    LoadString(szDeviceName, EEPROM_DEVICE_NAME);
    LoadString(szOwnerName, EEPROM_OWNER_NAME);
  }
  else
  {
    dwIP = inet_addr("100.1.168.192");
    dwGateway = inet_addr("0.255.255.255");
    dwNetmask = inet_addr("1.1.168.192");

    wPort = 1001;

    memset(&szDeviceName,  0, sizeof(szDeviceName));
    sprintf(szDeviceName, "Device");

    memset(&szOwnerName,  0, sizeof(szOwnerName));
    sprintf(szOwnerName, "Owner");

    SaveSettings();
  }

  return 0;
}
