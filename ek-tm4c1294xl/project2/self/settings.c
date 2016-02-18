/*------------------------------------------------------------------------------
SETTINGS,C

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


#define SETTINGS_LABEL  3

ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;

char                    szDeviceName[NAME_SIZE];
char                    szOwnerName[NAME_SIZE];

uchar                   mbConnectionTimeout[UART_COUNT];
uchar                   mbRoutingMode[UART_COUNT];
uint                    mwPort[UART_COUNT];
uchar                   mbConnectionMode[UART_COUNT];
ulong                   mdwDestinationIP[UART_COUNT];
uint                    mwDestinationPort[UART_COUNT];

uchar                   mibBaudRate[UART_COUNT];

bool                    fUdpDebugFlag;
ulong                   dwUdpDebugIP;
uint                    wUdpDebugPort;

uint                    wSerialNumber;

bool                    fUartDebugFlag;
uchar                   bUartDebugPort;

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


  if ((err = SaveEntity(&enConnectionTimeout0)) != 0) return err;
  if ((err = SaveEntity(&enConnectionTimeout1)) != 0) return err;
  if ((err = SaveEntity(&enConnectionTimeout2)) != 0) return err;

  if ((err = SaveEntity(&enRoutingMode0)) != 0) return err;
  if ((err = SaveEntity(&enRoutingMode1)) != 0) return err;
  if ((err = SaveEntity(&enRoutingMode2)) != 0) return err;

  if ((err = SaveEntity(&enPort0)) != 0) return err;
  if ((err = SaveEntity(&enPort1)) != 0) return err;
  if ((err = SaveEntity(&enPort2)) != 0) return err;

  if ((err = SaveEntity(&enConnectionMode0)) != 0) return err;
  if ((err = SaveEntity(&enConnectionMode1)) != 0) return err;
  if ((err = SaveEntity(&enConnectionMode2)) != 0) return err;

  if ((err = SaveEntity(&enDestinationIP0)) != 0) return err;
  if ((err = SaveEntity(&enDestinationIP1)) != 0) return err;
  if ((err = SaveEntity(&enDestinationIP2)) != 0) return err;

  if ((err = SaveEntity(&enDestinationPort0)) != 0) return err;
  if ((err = SaveEntity(&enDestinationPort1)) != 0) return err;
  if ((err = SaveEntity(&enDestinationPort2)) != 0) return err;

  if ((err = SaveEntity(&enBaudRate0)) != 0) return err;
  if ((err = SaveEntity(&enBaudRate1)) != 0) return err;
  if ((err = SaveEntity(&enBaudRate2)) != 0) return err;

  if ((err = SaveEntity(&enUdpDebugFlag)) != 0) return err;
  if ((err = SaveEntity(&enUdpDebugIP)) != 0) return err;
  if ((err = SaveEntity(&enUdpDebugPort)) != 0) return err;

  if ((err = SaveEntity(&enSerialNumber)) != 0) return err;

  if ((err = SaveEntity(&enUartDebugFlag)) != 0) return err;
  if ((err = SaveEntity(&enUartDebugPort)) != 0) return err;

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

    LoadEntity(&enConnectionTimeout0);
    LoadEntity(&enConnectionTimeout1);
    LoadEntity(&enConnectionTimeout2);

    LoadEntity(&enRoutingMode0);
    LoadEntity(&enRoutingMode1);
    LoadEntity(&enRoutingMode2);

    LoadEntity(&enPort0);
    LoadEntity(&enPort1);
    LoadEntity(&enPort2);

    LoadEntity(&enConnectionMode0);
    LoadEntity(&enConnectionMode1);
    LoadEntity(&enConnectionMode2);

    LoadEntity(&enDestinationIP0);
    LoadEntity(&enDestinationIP1);
    LoadEntity(&enDestinationIP2);

    LoadEntity(&enDestinationPort0);
    LoadEntity(&enDestinationPort1);
    LoadEntity(&enDestinationPort2);

    LoadEntity(&enBaudRate0);
    LoadEntity(&enBaudRate1);
    LoadEntity(&enBaudRate2);

    LoadEntity(&enUdpDebugFlag);
    LoadEntity(&enUdpDebugIP);
    LoadEntity(&enUdpDebugPort);

    LoadEntity(&enSerialNumber);

    LoadEntity(&enUartDebugFlag);
    LoadEntity(&enUartDebugPort);
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

    mbConnectionTimeout[0] = enConnectionTimeout0.dwDef; // TODO LoadEntityDef
    mbConnectionTimeout[1] = enConnectionTimeout1.dwDef;
    mbConnectionTimeout[2] = enConnectionTimeout2.dwDef;

    mbRoutingMode[0] = enRoutingMode0.dwDef;
    mbRoutingMode[1] = enRoutingMode1.dwDef;
    mbRoutingMode[2] = enRoutingMode2.dwDef;

    mwPort[0] = enPort0.dwDef;
    mwPort[1] = enPort1.dwDef;
    mwPort[2] = enPort2.dwDef;

    mbConnectionMode[0] = enConnectionMode0.dwDef;
    mbConnectionMode[1] = enConnectionMode1.dwDef;
    mbConnectionMode[2] = enConnectionMode2.dwDef;

    mdwDestinationIP[0] = enDestinationIP0.dwDef;
    mdwDestinationIP[1] = enDestinationIP1.dwDef;
    mdwDestinationIP[2] = enDestinationIP2.dwDef;

    mwDestinationPort[0] = enDestinationPort0.dwDef;
    mwDestinationPort[1] = enDestinationPort1.dwDef;
    mwDestinationPort[2] = enDestinationPort2.dwDef;

    mibBaudRate[0] = enBaudRate0.dwDef;
    mibBaudRate[1] = enBaudRate1.dwDef;
    mibBaudRate[2] = enBaudRate2.dwDef;

    fUdpDebugFlag = enUdpDebugFlag.dwDef;
    dwUdpDebugIP = enUdpDebugIP.dwDef;
    wUdpDebugPort = enUdpDebugPort.dwDef;

    wSerialNumber = enSerialNumber.dwDef;

    fUartDebugFlag = enUartDebugFlag.dwDef;
    bUartDebugPort = enUartDebugPort.dwDef;

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
