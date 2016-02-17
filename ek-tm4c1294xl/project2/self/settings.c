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



static const ulong      mdwBAUDS[BAUD_RATE_COUNT] = {150,300,600,1200,2400,4800,9600,19200,28800,38400,57600,115200,230400,460800};


#define SETTINGS_LABEL  8

ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;

char                    szDeviceName[NAME_SIZE];
char                    szOwnerName[NAME_SIZE];

uchar                   bConnectionTimeout;
uchar                   mbRoutingMode[UART_COUNT];
uint                    mwPort[UART_COUNT];
ulong                   dwDestIP;
uint                    wDestPort;

uchar                   mibBaudRate[UART_COUNT];

bool                    fUdpDebugFlag;
uint                    wUdpDebugPort;

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


  err = SaveString(szDeviceName, EEPROM_DEVICE_NAME);
  if (err != 0) return err;

  err = SaveString(szOwnerName, EEPROM_OWNER_NAME);
  if (err != 0) return err;


  if ((err = SaveEntity(&enConnectionTimeout)) != 0) return err;

  if ((err = SaveEntity(&enRoutingMode0)) != 0) return err;
  if ((err = SaveEntity(&enRoutingMode1)) != 0) return err;

  if ((err = SaveEntity(&enPort0)) != 0) return err;
  if ((err = SaveEntity(&enPort1)) != 0) return err;

  if ((err = SaveEntity(&enDestIP)) != 0) return err;
  if ((err = SaveEntity(&enDestPort)) != 0) return err;

  if ((err = SaveEntity(&enBaudRate0)) != 0) return err;
  if ((err = SaveEntity(&enBaudRate1)) != 0) return err;

  if ((err = SaveEntity(&enUdpDebugFlag)) != 0) return err;
  if ((err = SaveEntity(&enUdpDebugPort)) != 0) return err;

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

    LoadString(szDeviceName, EEPROM_DEVICE_NAME);
    LoadString(szOwnerName, EEPROM_OWNER_NAME);

    LoadEntity(&enConnectionTimeout);

    LoadEntity(&enRoutingMode0);
    LoadEntity(&enRoutingMode1);

    LoadEntity(&enPort0);
    LoadEntity(&enPort1);

    LoadEntity(&enDestIP);
    LoadEntity(&enDestPort);

    LoadEntity(&enBaudRate0);
    LoadEntity(&enBaudRate1);

    LoadEntity(&enUdpDebugFlag);
    LoadEntity(&enUdpDebugPort);
  }
  else
  {
    dwIP = inet_addr("100.1.168.192");
    dwGateway = inet_addr("0.255.255.255");
    dwNetmask = inet_addr("1.1.168.192");

    memset(&szDeviceName,  0, sizeof(szDeviceName));
    sprintf(szDeviceName, "Device");

    memset(&szOwnerName,  0, sizeof(szOwnerName));
    sprintf(szOwnerName, "Owner");

    bConnectionTimeout = DEFAULT_CONNECTION_TIMEOUT; // TODO LoadEntityDef

    mbRoutingMode[0] = enRoutingMode0.dwDef;
    mbRoutingMode[1] = enRoutingMode1.dwDef;

    mwPort[0] = enPort0.dwDef;
    mwPort[1] = enPort1.dwDef;

    dwDestIP = DEFAULT_DEST_IP;
    wDestPort = DEFAULT_DEST_PORT;

    mibBaudRate[0] = DEFAULT_BAUD_RATE;
    mibBaudRate[1] = DEFAULT_BAUD_RATE;

    fUdpDebugFlag = enUdpDebugFlag.dwDef;
    wUdpDebugPort = enUdpDebugPort.dwDef;

    SaveSettings();
  }

  return 0;
}



ulong GetBaud(uchar ibPort)
{
  uchar ibBaud = mibBaudRate[ibPort] < BAUD_RATE_COUNT ? mibBaudRate[ibPort] : DEFAULT_BAUD_RATE;
  ASSERT(ibBaud < BAUD_RATE_COUNT);
  return mdwBAUDS[ibBaud];
}
