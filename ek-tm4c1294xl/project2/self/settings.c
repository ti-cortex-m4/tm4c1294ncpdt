/*------------------------------------------------------------------------------
SETTINGS.C

TODO
------------------------------------------------------------------------------*/

#include "main.h"
#include "driverlib/eeprom.h"
#include "driverlib/sysctl.h"
#include "lwip/inet.h"
#include "generated/eeprom.h"
#include "settings_eeprom.h"
#include "settings.h"



static const ulong      mdwBAUDS[BAUDS_SIZE] = {150,300,600,1200,2400,4800,9600,19200,28800,38400,57600,115200,230400,460800};


#define SETTINGS_LABEL  4

ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;
uint                    wPort;

char                    szDeviceName[NAME_SIZE];
char                    szOwnerName[NAME_SIZE];

uchar                   bConnectionTimeout;
uchar                   ibRoutingMode;
ulong                   dwDestIP;
uint                    wDestPort;

uchar                   ibBaud;

uchar                   pbMAC[6];



uchar   InitSettings(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

  uchar err = EEPROMInit();
  if (err != EEPROM_INIT_OK) return err;

  return LoadSettings();
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

uchar SavePort(void)
{
  return SaveInt(&wPort, EEPROM_PORT);
}


uchar SaveDeviceName(void)
{
  return SaveString(szDeviceName, EEPROM_DEVICE_NAME);
}

uchar SaveOwnerName(void)
{
  return SaveString(szOwnerName, EEPROM_OWNER_NAME);
}


uchar SaveConnectionTimeout(void)
{
  return SaveChar(&bConnectionTimeout, EEPROM_CONNECTION_TIMEOUT);
}

uchar SaveRoutingMode(void)
{
  return SaveChar(&ibRoutingMode, EEPROM_ROUTING_MODE);
}

uchar SaveDestIP(void)
{
  return SaveLong(&dwDestIP, EEPROM_DEST_IP);
}

uchar SaveDestPort(void)
{
  return SaveInt(&wDestPort, EEPROM_DEST_PORT);
}


uchar SaveBaud(void)
{
  return SaveChar(&ibBaud, EEPROM_BAUD);
}


uchar    SaveSettings(void)
{
  ulong dw = SETTINGS_LABEL;
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


  err = SaveChar(&bConnectionTimeout, EEPROM_CONNECTION_TIMEOUT);
  if (err != 0) return err;

  err = SaveChar(&ibRoutingMode, EEPROM_ROUTING_MODE);
  if (err != 0) return err;

  err = SaveLong(&dwDestIP, EEPROM_DEST_IP);
  if (err != 0) return err;

  err = SaveInt(&wDestPort, EEPROM_DEST_PORT);
  if (err != 0) return err;


  err = SaveChar(&ibBaud, EEPROM_BAUD);
  if (err != 0) return err;


  return 0;
}



uchar   LoadSettings(void)
{
  ulong dw = 0;
  LoadLong(&dw, EEPROM_LABEL);

  if (dw == SETTINGS_LABEL)
  {
    LoadLong(&dwIP, EEPROM_IP);
    LoadLong(&dwGateway, EEPROM_GATEWAY);
    LoadLong(&dwNetmask, EEPROM_NETMASK);
    LoadInt(&wPort, EEPROM_PORT);

    LoadString(szDeviceName, EEPROM_DEVICE_NAME);
    LoadString(szOwnerName, EEPROM_OWNER_NAME);

    LoadChar(&bConnectionTimeout, EEPROM_CONNECTION_TIMEOUT);
    LoadChar(&ibRoutingMode, EEPROM_ROUTING_MODE);
    LoadLong(&dwDestIP, EEPROM_DEST_IP);
    LoadInt(&wDestPort, EEPROM_DEST_PORT);

    LoadChar(&ibBaud, EEPROM_BAUD);
  }
  else
  {
    dwIP = inet_addr("100.1.168.192");
    dwGateway = inet_addr("0.255.255.255");
    dwNetmask = inet_addr("1.1.168.192");
    wPort = 100;

    memset(&szDeviceName,  0, sizeof(szDeviceName));
    sprintf(szDeviceName, "Device");

    memset(&szOwnerName,  0, sizeof(szOwnerName));
    sprintf(szOwnerName, "Owner");

    bConnectionTimeout = 0;
    ibRoutingMode = 0;
    dwDestIP = inet_addr("101.1.168.192");
    wDestPort = 101;

    ibBaud = DEFAULT_BAUD;

    SaveSettings();
  }

  return 0;
}



ulong GetBaud(void)
{
  return (ibBaud < BAUDS_SIZE) ? mdwBAUDS[ibBaud] : mdwBAUDS[DEFAULT_BAUD];
}
