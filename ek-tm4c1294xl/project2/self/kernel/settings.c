/*------------------------------------------------------------------------------
settings.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "../hardware/storage.h"
#include "entity.h"
#include "log.h"
#include "settings.h"



#define SETTINGS_LABEL  4



const ulong             mdwBaudRates[BAUD_RATE_COUNT] = {150,300,600,1200,2400,4800,9600,19200,28800,38400,57600,115200,230400,460800};



uchar                   mbMAC[6];

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

bool                    mfServerToModem[UART_COUNT];
uchar                   mbModemToServerTimeout[UART_COUNT];

uchar                   mibBaudRate[UART_COUNT];
uchar                   mibParity[UART_COUNT];
uchar                   mibDataBits[UART_COUNT];
uchar                   mibStopBits[UART_COUNT];
bool                    mfLoopback[UART_COUNT];

bool                    fWatchdogFlag;
bool                    fWatchdogReset;

bool                    ibDebugMode;

ulong                   dwUDPDebugIP;
uint                    wUDPDebugPort;

bool                    fLWIPDebugFlag;
uint                    wLWIPDebugTimeout;

bool                    fTCPEchoFlag;
uint                    wTCPEchoPort;

bool                    fDataDebugFlag;
bool                    fIOModeDebugFlag;

ledMode                 bLED0Mode = LED_MODE_LINK;
ledMode                 bLED1Mode;

bool                    fPeriodicResetFlag;
uchar                   bPeriodicResetPeriod;
uint                    cwPowerUpResetCount;
uint                    cwWatchdogResetCount;

uchar                   mbCustomerSettings[UART_COUNT];
uchar                   mbCustomerSetting1_Delay[UART_COUNT];
uint                    mwCustomerSetting1_Timeout[UART_COUNT];

uint                    cwErrSettingsInitStorage;
uint                    cwErrSettingsSaveEntity;
uint                    cwErrSettingsLoadIP;



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
    if (((mpenEntities[e]->dwFlags) & FLAG_DONT_RESET) == 0)
    {
      LoadEntityDef(mpenEntities[e]);
    }
  }
}


static void SaveSettings(void)
{
  ulong dwLabel = SETTINGS_LABEL;
  const ulong code = SaveLong(&dwLabel, EEPROM_LABEL);
  if (code != 0)
    cwErrSettingsSaveEntity++;

  uchar e;
  for (e = 0; e < bEntitiesSize; e++)
  {
    SaveEntity(mpenEntities[e]);
  }
}



void InitSettings(void)
{
  const ulong code = InitStorage();
  if (code == 0)
  {
    ulong dwLabel = 0;
    LoadLong(&dwLabel, EEPROM_LABEL);

    if (dwLabel == SETTINGS_LABEL)
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
    cwErrSettingsInitStorage++;
    LoadSettingsDef();
  }

  if (dwIP == 0)
  {
    cwErrSettingsLoadIP++;

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
