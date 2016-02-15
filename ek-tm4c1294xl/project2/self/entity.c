/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "generated/eeprom.h"
#include "settings.h"
#include "entity.h"



const entity            enConnectionTimeout = {EEPROM_CONNECTION_TIMEOUT, &bConnectionTimeout, 0, 255, 0, CHAR};
