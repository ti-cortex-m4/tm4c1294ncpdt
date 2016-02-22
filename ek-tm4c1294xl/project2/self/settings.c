/*------------------------------------------------------------------------------
SETTINGS,C

TODO
------------------------------------------------------------------------------*/

#include "main.h"
#include "lwip/inet.h"
#include "generated/eeprom.h"
#include "hardware/storage.h"
#include "kernel/entity.h"
#include "kernel/log.h"
#include "settings.h"



static const ulong      mdwBAUDS[BAUD_RATE_COUNT] = {150,300,600,1200,2400,4800,9600,19200,28800,38400,57600,115200,230400,460800};


#define SETTINGS_LABEL  5



uchar                   pbMAC[6];

uint                    wSerialNumber;

ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;

char                    szOwnerName[NAME_SIZE];
char                    szDeviceName[NAME_SIZE];

uchar                   mbConnectionTimeout[UART_COUNT];
uchar                   mbRoutingMode[UART_COUNT];
uint                    mwPort[UART_COUNT];
uchar                   mbConnectionMode[UART_COUNT];
ulong                   mdwDestinationIP[UART_COUNT];
uint                    mwDestinationPort[UART_COUNT];

uchar                   mibBaudRate[UART_COUNT];

bool                    ibDebugMode;

ulong                   dwUdpDebugIP;
uint                    wUdpDebugPort;

bool                    fLwIpDebugFlag;
uint                    wLwIpDebugTimeout;


uint                    cwErrStorageInit;
uint                    cwErrEntitySave;



static void LoadSettings(void)
{
  uchar e;
  for (e = 0; e < bEntitiesSize; e++)
  {
    LoadEntity(mpenEntities[e]);
  }
}


static void LoadSettingsDef(void)
{
  uchar e;
  for (e = 0; e < bEntitiesSize; e++)
  {
    LoadEntityDef(mpenEntities[e]);
  }
}


static void SaveSettings(void)
{
  ulong dw = SETTINGS_LABEL;
  ulong code = SaveLong(&dw, EEPROM_LABEL);

  if (code != 0)
    cwErrEntitySave++;

  uchar e;
  for (e = 0; e < bEntitiesSize; e++)
  {
    if (SaveEntity(mpenEntities[e]) != 0)
      cwErrEntitySave++;
  }
}



void InitSettings(void)
{
  ulong code = InitStorage();
  if (code == 0)
  {
    ulong dw = 0;
    LoadLong(&dw, EEPROM_LABEL);

    if (dw == SETTINGS_LABEL)
    {
      LoadSettings();
    }
    else
    {
      LoadSettingsDef();
      SaveSettings();
    }
  }
  else
  {
    cwErrStorageInit++;
    LoadSettingsDef();
  }
}


void ResetSettings(void)
{
  uchar e;
  for (e = 0; e < bEntitiesSize; e++)
  {
    const entity *pen = mpenEntities[e];
    if (((pen->dwFlags) & FLAG_DONT_RESET) == 0)
    {
      LoadEntityDef(pen);
    }
  }

  SaveSettings();
}



ulong GetBaud(uchar ibPort)
{
  uchar ibBaud = mibBaudRate[ibPort] < BAUD_RATE_COUNT ? mibBaudRate[ibPort] : DEFAULT_BAUD_RATE;
  ASSERT(ibBaud < BAUD_RATE_COUNT);
  return mdwBAUDS[ibBaud];
}


//! The timeout for the TCP connection used for the telnet session, specified in seconds.
//! A value of 0 indicates no timeout is to be used.
ulong getTelnetTimeout(uchar u)
{
  ASSERT(u < UART_COUNT);
  return mbConnectionTimeout[u]*60;
}
