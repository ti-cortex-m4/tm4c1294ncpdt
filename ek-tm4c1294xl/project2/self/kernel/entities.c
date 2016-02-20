/*------------------------------------------------------------------------------
entities,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "../settings.h"
#include "entities.h"



const entity * const mpenEntities[] = {
  &enIP,
  &enGateway,
  &enNetmask,

  &enDeviceName,
  &enOwnerName,

  &enConnectionTimeout0,
  &enConnectionTimeout1,
  &enConnectionTimeout2,

  &enRoutingMode0,
  &enRoutingMode1,
  &enRoutingMode2,

  &enPort0,
  &enPort1,
  &enPort2,

  &enConnectionMode0,
  &enConnectionMode1,
  &enConnectionMode2,

  &enDestinationIP0,
  &enDestinationIP1,
  &enDestinationIP2,

  &enDestinationPort0,
  &enDestinationPort1,
  &enDestinationPort2,

  &enBaudRate0,
  &enBaudRate1,
  &enBaudRate2,

  &enSerialNumber,

  &enDebugMode,

  &enUdpDebugIP,
  &enUdpDebugPort,

  &enLwIpDebugFlag,
  &enLwIpDebugTimeout,
};

const uchar bEntitiesSize = sizeof(mpenEntities) / sizeof(entity);



const entity enSerialNumber = {
  EEPROM_SERIAL_NUMBER, &wSerialNumber, sizeof(uint), INT,
  0, 65535, 0,
  "SRNM",
  "AI=SRNM;D=Serial number;T=INT;C=EDIT;V=SRNM>65535?\"Serial number must be between 0 and 65535\":\"\"",
};


const entity enDebugMode = {
  EEPROM_DEBUG_MODE, &ibDebugMode, sizeof(uchar), CHAR,
  0, 2, 1,
  "DBMD",
  "AI=DBMD;D=Debug mode;T=INT;C=STATIC;O=0-No/0/1-UDP/1/2-UART/2",
};



const entity enUdpDebugIP = {
  EEPROM_UDP_DEBUG_IP, &dwUdpDebugIP, sizeof(ulong), IP,
  0, MAX_LONG, 0xFFFFFFFF,
  "UDPDI",
  "AI=UDPDI;E=1;D=UDP debug IP-address;T=STRING;C=IPCTRL;S=DBMD==1?\"e\":\"i\"",
};

const entity enUdpDebugPort = {
  EEPROM_UDP_DEBUG_PORT, &wUdpDebugPort, sizeof(uint), INT,
  0, MAX_INT, 50000,
  "UDPDP",
  "AI=UDPDP;E=1;D=UDP debug port;T=INT;C=EDIT;S=DBMD==1?\"e\":\"i\"",
};


const entity enLwIpDebugFlag = {
  EEPROM_LWIP_DEBUG_FLAG, &fLwIpDebugFlag, sizeof(uchar), CHAR,
  0, 1, 0,
  "LWIPDF",
  "AI=LWIPDF;D=LwIP debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enLwIpDebugTimeout = {
  EEPROM_LWIP_DEBUG_TIMEOUT, &wLwIpDebugTimeout, sizeof(uint), INT,
  0, 3600, 60,
  "LWIPDT",
  "AI=LWIPDT;E=1;D=LwIP debug (seconds);T=INT;C=EDIT;V=LWIPDT>3600?\"Maximum timeout is 3600 seconds\":\"\";S=LWIPDF!=0?\"e\":\"i\"",
};
