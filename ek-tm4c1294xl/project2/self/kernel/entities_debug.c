/*------------------------------------------------------------------------------
entities_debug.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "../settings.h"
#include "entities_debug.h"



const entity enDebugMode = {
  EEPROM_DEBUG_MODE, &ibDebugMode, sizeof(uchar), CHAR, 0,
  0, 2, 1,
  "DBMD",
  "AI=DBMD;D=Debug mode;T=INT;C=STATIC;O=0-No/0/1-UDP/1/2-UART/2",
};



const entity enUdpDebugIP = {
  EEPROM_UDP_DEBUG_IP, &dwUdpDebugIP, sizeof(ulong), IP, 0,
  0, MAX_LONG, 0xFFFFFFFF,
  "UDPDI",
  "AI=UDPDI;E=1;D=UDP debug IP-address;T=STRING;C=IPCTRL;S=DBMD==1?\"e\":\"i\"",
};

const entity enUdpDebugPort = {
  EEPROM_UDP_DEBUG_PORT, &wUdpDebugPort, sizeof(uint), INT, 0,
  0, MAX_INT, 50000,
  "UDPDP",
  "AI=UDPDP;E=1;D=UDP debug port;T=INT;C=EDIT;S=DBMD==1?\"e\":\"i\"",
};


const entity enLwIpDebugFlag = {
  EEPROM_LWIP_DEBUG_FLAG, &fLwIpDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "LWIPDF",
  "AI=LWIPDF;D=LwIP debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enLwIpDebugTimeout = {
  EEPROM_LWIP_DEBUG_TIMEOUT, &wLwIpDebugTimeout, sizeof(uint), INT, 0,
  0, 3600, 60,
  "LWIPDT",
  "AI=LWIPDT;E=1;D=LwIP debug (seconds);T=INT;C=EDIT;V=LWIPDT>3600?\"Maximum timeout is 3600 seconds\":\"\";S=LWIPDF!=0?\"e\":\"i\"",
};
