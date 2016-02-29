/*------------------------------------------------------------------------------
entities_debug.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
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


const entity enLwipDebugFlag = {
  EEPROM_LWIP_DEBUG_FLAG, &fLwipDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 1,
  "LWIPDF",
  "AI=LWIPDF;D=TCP/IP stack debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enLwipDebugTimeout = {
  EEPROM_LWIP_DEBUG_TIMEOUT, &wLwipDebugTimeout, sizeof(uint), INT, 0,
  0, 3600, 300,
  "LWIPDT",
  "AI=LWIPDT;E=1;D=TCP/IP stack debug period (seconds);T=INT;C=EDIT;V=LWIPDT>3600?\"Maximum timeout is 3600 seconds\":\"\";S=LWIPDF!=0?\"e\":\"i\"",
};


const entity enDataDebugFlag = {
  EEPROM_DATA_DEBUG_FLAG, &fDataDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "DTDF",
  "AI=DTDF;D=Data debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};


const entity enLedMode1 = {
  EEPROM_LED_MODE_1, &bLedMode1, sizeof(uchar), CHAR, 0,
  0, 8, 1,
  "LEDMD",
  "AI=LEDMD;D=Debug mode;T=INT;C=STATIC;O=0-Link OK/0/1-RX.TX Activity/1/2-TX Activity/2/3-RX Activity/3/4-Collision/4/5-100-Base TX speed/5/6-10-Base TX speed/6/7-Full Duplex/7/8-Link OK,Blink on TX,RX Activity /8",
};
