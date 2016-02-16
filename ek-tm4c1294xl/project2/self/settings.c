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


#define SETTINGS_LABEL  5

ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;
uint                    wPort;

char                    szDeviceName[NAME_SIZE];
char                    szOwnerName[NAME_SIZE];

uchar                   bConnectionTimeout;
uchar                   bRoutingMode;
ulong                   dwDestIP;
uint                    wDestPort;

uchar                   mibBaud[UART_COUNT];

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


  if ((err = SaveEntity(&enConnectionTimeout)) != 0) return err;
  if ((err = SaveEntity(&enRoutingMode)) != 0) return err;
  if ((err = SaveEntity(&enDestIP)) != 0) return err;
  if ((err = SaveEntity(&enDestPort)) != 0) return err;

  if ((err = SaveEntity(&enBaud0)) != 0) return err;
  if ((err = SaveEntity(&enBaud1)) != 0) return err;


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

    LoadEntity(&enConnectionTimeout);
    LoadEntity(&enRoutingMode);
    LoadEntity(&enDestIP);
    LoadEntity(&enDestPort);

    LoadEntity(&enBaud0);
    LoadEntity(&enBaud1);
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

    bConnectionTimeout = DEFAULT_CONNECTION_TIMEOUT; // TODO LoadEntityDef
    bRoutingMode = DEFAULT_ROUTING_MODE;
    dwDestIP = DEFAULT_DEST_IP;
    wDestPort = DEFAULT_DEST_PORT;

    mibBaud[0] = DEFAULT_BAUD;
    mibBaud[1] = DEFAULT_BAUD;

    SaveSettings();
  }

  return 0;
}



ulong GetBaud(uchar ibPort)
{
  uchar ibBaud = mibBaud[ibPort] < BAUDS_SIZE ? mibBaud[ibPort] : DEFAULT_BAUD;
  ASSERT(ibBaud < BAUDS_SIZE);
  return mdwBAUDS[ibBaud];
}
