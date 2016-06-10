/*------------------------------------------------------------------------------
entities_setup.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
#include "entities.h"



const entity enSerialNumber = {
  EEPROM_SERIAL_NUMBER, &wSerialNumber, sizeof(uint), INT, FLAG_DONT_RESET,
  0, 65535, 0,
  "SRNM",
  "AI=SRNM;D=Serial number;T=INT;C=EDIT;V=SRNM>65535?\"Serial number must be between 0 and 65535\":\"\"",
};


const entity enWatchdogFlag = {
  EEPROM_WATCHDOG_FLAG, &fWatchdogFlag, sizeof(uchar), CHAR, 0,
  0, 1, 1,
  "WDT",
  "AI=WDT;D=Enable watchdog;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};
