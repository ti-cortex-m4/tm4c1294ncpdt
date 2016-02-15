/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "generated/eeprom.h"
#include "settings.h"
#include "entity.h"



const entity enConnectionTimeout = {
        EEPROM_CONNECTION_TIMEOUT, &bConnectionTimeout, sizeof(uchar), CHAR,
        0, 255, 0,
        "CT",
        "AI=CT;D=Connection timeout (min);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT>255?\"Maximum timeout is 255 minutes\":\"\"",
};
