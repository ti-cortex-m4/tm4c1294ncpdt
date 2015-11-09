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



ulong                   dwIP;
ulong                   dwGateway;
ulong                   dwNetmask;



void    InitSettings(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

  ulong error = EEPROMInit();
  if (error != EEPROM_INIT_OK)
  {
    while (1)
    {
//      TODO
    }
  }

  LoadSettings();
}



ulong    SaveSettings(void)
{
  ulong error;

  error = EEPROMProgram(&dwIP, EEPROM_ADDR_IP, 4);
  if (error != 0) return error;

  error = EEPROMProgram(&dwGateway, EEPROM_ADDR_GATEWAY, 4);
  if (error != 0) return error;

  error = EEPROMProgram(&dwNetmask, EEPROM_ADDR_NETMASK, 4);
  if (error != 0) return error;

  return 0;
}


ulong   LoadSettings(void)
{
  EEPROMRead(&dwIP, EEPROM_ADDR_IP, 4);

  EEPROMRead(&dwGateway, EEPROM_ADDR_GATEWAY, 4);

  EEPROMRead(&dwNetmask, EEPROM_ADDR_NETMASK, 4);

  return 0;
}
