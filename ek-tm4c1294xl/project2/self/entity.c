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


const entity enBaud0 = {
        EEPROM_BAUD_0, &mibBaud[0], sizeof(uchar), CHAR,
        0, BAUDS_SIZE-1, DEFAULT_BAUD,
        "BR",
        "AI=BR;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaud1 = {
        EEPROM_BAUD_1, &mibBaud[1], sizeof(uchar), CHAR,
        0, BAUDS_SIZE-1, DEFAULT_BAUD,
        "BR@2",
        "AI=BR@2;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};
