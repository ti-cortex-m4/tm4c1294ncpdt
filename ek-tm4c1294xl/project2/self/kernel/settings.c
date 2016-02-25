/*------------------------------------------------------------------------------
settings,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "../hardware/storage.h"
#include "entity.h"
#include "log.h"
#include "settings.h"



#define SETTINGS_LABEL  3



const ulong             mdwBaudRates[BAUD_RATE_COUNT] = {150,300,600,1200,2400,4800,9600,19200,28800,38400,57600,115200,230400,460800};



uchar                   pbMac[6];

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
uchar                   mibParity[UART_COUNT];
uchar                   mibDataBits[UART_COUNT];
uchar                   mibStopBits[UART_COUNT];

bool                    ibDebugMode;

ulong                   dwUdpDebugIP;
uint                    wUdpDebugPort;

bool                    fLwIpDebugFlag;
uint                    wLwIpDebugTimeout;


uint                    cwErrStorageInit;
uint                    cwErrIpLoad;
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
    const entity *pen = mpenEntities[e];
    if (((pen->dwFlags) & FLAG_DONT_RESET) == 0)
    {
      LoadEntityDef(pen);
    }
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
  const ulong code = InitStorage();
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

  if (dwIP == 0)
  {
    cwErrIpLoad++;

    LoadEntityDef(&enIP);
    if (code == 0)
    {
      SaveEntity(&enIP);
    }
  }
}


void ResetSettings(void)
{
  LoadSettingsDef();
  SaveSettings();
}
