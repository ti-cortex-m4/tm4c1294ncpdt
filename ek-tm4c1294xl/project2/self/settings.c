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

uchar                   pbMAC[6];



uchar   InitSettings(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

  uchar err = EEPROMInit();
  if (err != EEPROM_INIT_OK) return err;

  return LoadSettings();
}



uchar    SaveSettings(void)
{
  uchar err = EEPROMProgram(&dwIP, EEPROM_ADDR_IP, 4);
  if (err != 0) return err;

  err = EEPROMProgram(&dwGateway, EEPROM_ADDR_GATEWAY, 4);
  if (err != 0) return err;

  err = EEPROMProgram(&dwNetmask, EEPROM_ADDR_NETMASK, 4);
  if (err != 0) return err;

  return 0;
}


uchar   LoadSettings(void)
{
  EEPROMRead(&dwIP, EEPROM_ADDR_IP, 4);

  EEPROMRead(&dwGateway, EEPROM_ADDR_GATEWAY, 4);

  EEPROMRead(&dwNetmask, EEPROM_ADDR_NETMASK, 4);

  return 0;
}



void    SetMAC(uchar *pb)
{
  pbMAC[0] = pb[0];
  pbMAC[1] = pb[1];
  pbMAC[2] = pb[2];
  pbMAC[3] = pb[3];
  pbMAC[4] = pb[4];
  pbMAC[5] = pb[5];
}
