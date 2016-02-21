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
