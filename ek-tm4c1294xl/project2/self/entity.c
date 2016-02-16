/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "generated/eeprom.h"
#include "settings.h"
#include "entity.h"



const entity enConnectionTimeout = {
        EEPROM_CONNECTION_TIMEOUT, &bConnectionTimeout, sizeof(uchar), CHAR,
        0, 255, DEFAULT_CONNECTION_TIMEOUT,
        "CT",
        "AI=CT;D=Connection timeout (min);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT>255?\"Maximum timeout is 255 minutes\":\"\"",
};

const entity enRoutingMode = {
        EEPROM_CONNECTION_TIMEOUT, &bRoutingMode, sizeof(uchar), CHAR,
        0, 2, DEFAULT_ROUTING_MODE, // TODO 2-> 1
        "RM",
		"AI=RM;D=Routing Mode;T=INT;C=STATIC;O=0-Server (Slave)/0/2-Client (Master)/2",
};
