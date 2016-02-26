/*------------------------------------------------------------------------------
entities,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
#include "entities.h"



const entity * const mpenEntities[] =
{
  &enSerialNumber,

  &enIP,
  &enGateway,
  &enNetmask,

  &enDeviceName,
  &enOwnerName,

  &enConnectionTimeout0,
  &enConnectionTimeout1,
  &enConnectionTimeout2,
  &enConnectionTimeout3,
  &enConnectionTimeout4,

  &enRoutingMode0,
  &enRoutingMode1,
  &enRoutingMode2,
  &enRoutingMode3,
  &enRoutingMode4,

  &enPort0,
  &enPort1,
  &enPort2,
  &enPort3,
  &enPort4,

  &enConnectionMode0,
  &enConnectionMode1,
  &enConnectionMode2,
  &enConnectionMode3,
  &enConnectionMode4,

  &enDestinationIP0,
  &enDestinationIP1,
  &enDestinationIP2,
  &enDestinationIP3,
  &enDestinationIP4,

  &enDestinationPort0,
  &enDestinationPort1,
  &enDestinationPort2,
  &enDestinationPort3,
  &enDestinationPort4,

  &enBaudRate0,
  &enBaudRate1,
  &enBaudRate2,
  &enBaudRate3,
  &enBaudRate4,

  &enParity0,
  &enParity1,
  &enParity2,
  &enParity3,
  &enParity4,

  &enDataBits0,
  &enDataBits1,
  &enDataBits2,
  &enDataBits3,
  &enDataBits4,

  &enStopBits0,
  &enStopBits1,
  &enStopBits2,
  &enStopBits3,
  &enStopBits4,

  &enDebugMode,

  &enUdpDebugIP,
  &enUdpDebugPort,

  &enLwipDebugFlag,
  &enLwipDebugTimeout,
};

const uchar bEntitiesSize = sizeof(mpenEntities) / sizeof(mpenEntities[0]);
