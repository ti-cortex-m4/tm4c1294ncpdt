/*------------------------------------------------------------------------------
entities.c


------------------------------------------------------------------------------*/

#include "../main.h"
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
#ifndef SINGLE_UART
  &enConnectionTimeout1,
  &enConnectionTimeout2,
  &enConnectionTimeout3,
  &enConnectionTimeout4,
#endif

  &enRoutingMode0,
#ifndef SINGLE_UART
  &enRoutingMode1,
  &enRoutingMode2,
  &enRoutingMode3,
  &enRoutingMode4,
#endif

  &enPort0,
#ifndef SINGLE_UART
  &enPort1,
  &enPort2,
  &enPort3,
  &enPort4,
#endif

  &enConnectionMode0,
#ifndef SINGLE_UART
  &enConnectionMode1,
  &enConnectionMode2,
  &enConnectionMode3,
  &enConnectionMode4,
#endif

  &enDestinationIP0,
#ifndef SINGLE_UART
  &enDestinationIP1,
  &enDestinationIP2,
  &enDestinationIP3,
  &enDestinationIP4,
#endif

  &enDestinationPort0,
#ifndef SINGLE_UART
  &enDestinationPort1,
  &enDestinationPort2,
  &enDestinationPort3,
  &enDestinationPort4,
#endif

  &enServerToModem0,
#ifndef SINGLE_UART
  &enServerToModem1,
  &enServerToModem2,
  &enServerToModem3,
  &enServerToModem4,
#endif

  &enModemToServerTimeout0,
#ifndef SINGLE_UART
  &enModemToServerTimeout1,
  &enModemToServerTimeout2,
  &enModemToServerTimeout3,
  &enModemToServerTimeout4,
#endif

  &enBaudRate0,
#ifndef SINGLE_UART
  &enBaudRate1,
  &enBaudRate2,
  &enBaudRate3,
  &enBaudRate4,
#endif

  &enParity0,
#ifndef SINGLE_UART
  &enParity1,
  &enParity2,
  &enParity3,
  &enParity4,
#endif

  &enDataBits0,
#ifndef SINGLE_UART
  &enDataBits1,
  &enDataBits2,
  &enDataBits3,
  &enDataBits4,
#endif

  &enStopBits0,
#ifndef SINGLE_UART
  &enStopBits1,
  &enStopBits2,
  &enStopBits3,
  &enStopBits4,
#endif

  &enLoopback0,
#ifndef SINGLE_UART
  &enLoopback1,
  &enLoopback2,
  &enLoopback3,
  &enLoopback4,
#endif

  &enWatchdogFlag,
  &enDebugMode,

  &enUDPDebugIP,
  &enUDPDebugPort,

  &enLWIPDebugFlag,
  &enLWIPDebugTimeout,

  &enTCPEchoFlag,
  &enTCPEchoPort,

  &enDataDebugFlag,
  &enIOModeDebugFlag,

  &enLED0Mode,
  &enLED1Mode,

  &enPeriodicResetFlag,
  &enPeriodicResetPeriod,

  &enCustomerSettings0,
#ifndef SINGLE_UART
  &enCustomerSettings1,
  &enCustomerSettings2,
  &enCustomerSettings3,
  &enCustomerSettings4,
#endif

  &enCustomerSetting1Delay0,
#ifndef SINGLE_UART
  &enCustomerSetting1Delay1,
  &enCustomerSetting1Delay2,
  &enCustomerSetting1Delay3,
  &enCustomerSetting1Delay4,
#endif

  &enCustomerSetting1Timeout0,
#ifndef SINGLE_UART
  &enCustomerSetting1Timeout1,
  &enCustomerSetting1Timeout2,
  &enCustomerSetting1Timeout3,
  &enCustomerSetting1Timeout4,
#endif
};


const uchar bEntitiesSize = sizeof(mpenEntities) / sizeof(mpenEntities[0]);



const entity * const mpenRoutingModes[UART_COUNT] =
{
  &enRoutingMode0,
#ifndef SINGLE_UART
  &enRoutingMode1,
  &enRoutingMode2,
  &enRoutingMode3,
  &enRoutingMode4,
#endif
};
