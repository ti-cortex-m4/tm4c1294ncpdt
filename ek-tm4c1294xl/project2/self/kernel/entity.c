/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "../settings.h"
#include "entity.h"



const entity enConnectionTimeout0 = {
        EEPROM_CONNECTION_TIMEOUT_0, &mbConnectionTimeout[0], sizeof(uchar), CHAR,
        0, 255, DEFAULT_CONNECTION_TIMEOUT,
        "CT",
        "AI=CT;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT>255?\"Maximum timeout is 255 minutes\":\"\"",
};

const entity enConnectionTimeout1 = {
        EEPROM_CONNECTION_TIMEOUT_1, &mbConnectionTimeout[1], sizeof(uchar), CHAR,
        0, 255, DEFAULT_CONNECTION_TIMEOUT,
        "CT@2",
        "AI=CT@2;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT@2>255?\"Maximum timeout is 255 minutes\":\"\"",
};


const entity enRoutingMode0 = {
        EEPROM_ROUTING_MODE_0, &mbRoutingMode[0], sizeof(uchar), CHAR,
        0, 1, DEFAULT_ROUTING_MODE,
        "RM",
        "AI=RM;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};

const entity enRoutingMode1 = {
        EEPROM_ROUTING_MODE_1, &mbRoutingMode[1], sizeof(uchar), CHAR,
        0, 1, DEFAULT_ROUTING_MODE,
        "RM@2",
        "AI=RM@2;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};


const entity enPort0 = {
        EEPROM_PORT_0, &mwPort[0], sizeof(uint), INT,
        0, 65534, 1001,
        "PN",
        "AI=PN;E=1;D=Port;T=INT;C=EDIT;V=PN>65534?\"Port number must be between 0 and 65534\":\"\";S=RM!=1?\"e\":\"i\"",
};

const entity enPort1 = {
        EEPROM_PORT_1, &mwPort[1], sizeof(uint), INT,
        0, 65534, 1002,
        "PN@2",
        "AI=PN@2;E=1;D=Port;T=INT;C=EDIT;V=PN@2>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@2!=1?\"e\":\"i\"",
};


// http://docs.tibbo.com/soism/index.html?setting_cm.htm

const entity enConnectionMode0 = {
        EEPROM_CONNECTION_MODE_0, &mbConnectionMode[0], sizeof(uchar), CHAR,
        0, 1, DEFAULT_CONNECTION_MODE,
        "CM",
        "AI=CM;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM!=0?\"e\":\"i\"",
};

const entity enConnectionMode1 = {
        EEPROM_CONNECTION_MODE_1, &mbConnectionMode[1], sizeof(uchar), CHAR,
        0, 1, DEFAULT_CONNECTION_MODE,
        "CM@2",
        "AI=CM@2;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM@2!=0?\"e\":\"i\"",
};


// http://docs.tibbo.com/soism/index.html?setting_di.htm

const entity enDestinationIP0 = {
        EEPROM_DESTINATION_IP_0, &mdwDestinationIP[0], sizeof(ulong), LONG,
        0, MAX_LONG, DEFAULT_DESTINATION_IP,
        "DI",
        "AI=DI;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM==1?\"e\":\"i\"",
};

const entity enDestinationIP1 = {
        EEPROM_DESTINATION_IP_1, &mdwDestinationIP[1], sizeof(ulong), LONG,
        0, MAX_LONG, DEFAULT_DESTINATION_IP,
        "DI@2",
        "AI=DI@2;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM@2==1?\"e\":\"i\"",
};


// http://docs.tibbo.com/soism/index.html?setting_dp.htm

const entity enDestinationPort0 = {
        EEPROM_DESTINATION_PORT_0, &mwDestinationPort[0], sizeof(uint), INT,
        0, MAX_INT, DEFAULT_DESTINATION_PORT+0,
        "DP",
        "AI=DP;E=1;D=Destination port;T=INT;C=EDIT;S=RM!=0?\"e\":\"i\"",
};

const entity enDestinationPort1 = {
        EEPROM_DESTINATION_PORT_1, &mwDestinationPort[1], sizeof(uint), INT,
        0, MAX_INT, DEFAULT_DESTINATION_PORT+1,
        "DP@2",
        "AI=DP@2;E=1;D=Destination port;T=INT;C=EDIT;S=RM@2!=0?\"e\":\"i\"",
};


const entity enBaudRate0 = {
        EEPROM_BAUD_RATE_0, &mibBaudRate[0], sizeof(uchar), CHAR,
        0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
        "BR",
        "AI=BR;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaudRate1 = {
        EEPROM_BAUD_RATE_1, &mibBaudRate[1], sizeof(uchar), CHAR,
        0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
        "BR@2",
        "AI=BR@2;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};


const entity enUdpDebugFlag = {
        EEPROM_UDP_DEBUG_FLAG, &fUdpDebugFlag, sizeof(uchar), CHAR,
        0, 1, 0,
        "UDP#DF",
        "AI=UDP#DF;D=UDP debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enUdpDebugIP = {
        EEPROM_UDP_DEBUG_IP, &dwUdpDebugIP, sizeof(ulong), LONG,
        0, MAX_LONG, 0xFFFFFFFF,
        "UDP#DI",
        "AI=UDP#DI;E=1;D=UDP debug IP-address;T=STRING;C=IPCTRL;S=UDP#DF!=0?\"e\":\"i\"",
};

const entity enUdpDebugPort = {
        EEPROM_UDP_DEBUG_PORT, &wUdpDebugPort, sizeof(uint), INT,
        0, MAX_INT, 50000,
        "UDP#DP",
        "AI=UDP#DP;E=1;D=UDP debug port;T=INT;C=EDIT;S=UDP#DF!=0?\"e\":\"i\"",
};


const entity enUartDebugFlag = {
        EEPROM_UART_DEBUG_FLAG, &fUartDebugFlag, sizeof(uchar), CHAR,
        0, 1, 0,
        "UART#DF",
        "AI=UART#DF;D=UART debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enUartDebugPort = {
        EEPROM_UART_DEBUG_PORT, &bUartDebugPort, sizeof(uchar), CHAR,
        0, UART_COUNT-1, 0,
        "UART#DP",
        "AI=UART#DP;E=1;D=UDP debug port;T=INT;C=EDIT;S=UART#DF!=0?\"e\":\"i\"",
};
