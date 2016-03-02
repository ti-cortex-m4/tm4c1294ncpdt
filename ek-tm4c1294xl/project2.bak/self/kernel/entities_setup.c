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
