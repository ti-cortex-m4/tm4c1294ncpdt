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

const entity enDestIP = {
        EEPROM_DEST_IP, &dwDestIP, sizeof(ulong), LONG,
        0, MAX_LONG, DEFAULT_DEST_IP,
        "DI",
        "AI=DI;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM==1||RM==2?\"e\":\"i\"", // TODO ||SF==1
};

const entity enDestPort = {
        EEPROM_DEST_PORT, &wDestPort, sizeof(uint), INT,
        0, MAX_INT, DEFAULT_DEST_PORT,
        "DP",
        "AI=DP;E=1;D=Destination port;T=INT;C=EDIT;S=RM!=0?\"e\":\"i\"",
};
