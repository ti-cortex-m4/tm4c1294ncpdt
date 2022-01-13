/*------------------------------------------------------------------------------
controls.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "entities.h"
#include "controls.h"



static message szGeneral = "AI=$GENERAL;D=General;T=GROUP";
static message szCanal0 = "AI=$CANAL1;D=Canal1;T=GROUP";
#ifndef SINGLE_UART
static message szCanal1 = "AI=$CANAL2;D=Canal2;T=GROUP";
static message szCanal2 = "AI=$CANAL3;D=Canal3;T=GROUP";
static message szCanal3 = "AI=$CANAL4;D=Canal4;T=GROUP";
static message szCanal4 = "AI=$CANAL5;D=Canal5;T=GROUP";
#endif
static message szSetup = "AI=$SETUP;D=Setup;T=GROUP";



const message * const mppcszControls[] =
{
  &szGeneral,
  &enOwnerName.szName,
  &enDeviceName.szName,
  &enIP.szName,
  &enGateway.szName,
  &enNetmask.szName,

  &szCanal0,
  &enConnectionTimeout0.szName,
  &enRoutingMode0.szName,
  &enPort0.szName,
  &enConnectionMode0.szName,
  &enDestinationIP0.szName,
  &enDestinationPort0.szName,
  &enServerToModem0.szName,
  &enModemToServerTimeout0.szName,
  &enBaudRate0.szName,
  &enParity0.szName,
  &enDataBits0.szName,
  &enStopBits0.szName,
  &enLoopback0.szName,
  &enCustomerSettings0.szName,
  &enCustomerSetting1Delay0.szName,
  &enCustomerSetting1Timeout0.szName,

#ifndef SINGLE_UART
  &szCanal1,
  &enConnectionTimeout1.szName,
  &enRoutingMode1.szName,
  &enPort1.szName,
  &enConnectionMode1.szName,
  &enDestinationIP1.szName,
  &enDestinationPort1.szName,
  &enServerToModem1.szName,
  &enModemToServerTimeout1.szName,
  &enBaudRate1.szName,
  &enParity1.szName,
  &enDataBits1.szName,
  &enStopBits1.szName,
  &enLoopback1.szName,
  &enCustomerSettings1.szName,
  &enCustomerSetting1Delay1.szName,
  &enCustomerSetting1Timeout1.szName,

  &szCanal2,
  &enConnectionTimeout2.szName,
  &enRoutingMode2.szName,
  &enPort2.szName,
  &enConnectionMode2.szName,
  &enDestinationIP2.szName,
  &enDestinationPort2.szName,
  &enServerToModem2.szName,
  &enModemToServerTimeout2.szName,
  &enBaudRate2.szName,
  &enParity2.szName,
  &enDataBits2.szName,
  &enStopBits2.szName,
  &enLoopback2.szName,
  &enCustomerSettings2.szName,
  &enCustomerSetting1Delay2.szName,
  &enCustomerSetting1Timeout2.szName,

  &szCanal3,
  &enConnectionTimeout3.szName,
  &enRoutingMode3.szName,
  &enPort3.szName,
  &enConnectionMode3.szName,
  &enDestinationIP3.szName,
  &enDestinationPort3.szName,
  &enServerToModem3.szName,
  &enModemToServerTimeout3.szName,
  &enBaudRate3.szName,
  &enParity3.szName,
  &enDataBits3.szName,
  &enStopBits3.szName,
  &enLoopback3.szName,
  &enCustomerSettings3.szName,
  &enCustomerSetting1Delay3.szName,
  &enCustomerSetting1Timeout3.szName,

  &szCanal4,
  &enConnectionTimeout4.szName,
  &enRoutingMode4.szName,
  &enPort4.szName,
  &enConnectionMode4.szName,
  &enDestinationIP4.szName,
  &enDestinationPort4.szName,
  &enServerToModem4.szName,
  &enModemToServerTimeout4.szName,
  &enBaudRate4.szName,
  &enParity4.szName,
  &enDataBits4.szName,
  &enStopBits4.szName,
  &enLoopback4.szName,
  &enCustomerSettings4.szName,
  &enCustomerSetting1Delay4.szName,
  &enCustomerSetting1Timeout4.szName,
#endif

  &szSetup,
  &enSerialNumber.szName,
  &enWatchdogFlag.szName,
  &enDebugMode.szName,
  &enUDPDebugIP.szName,
  &enUDPDebugPort.szName,
  &enLWIPDebugFlag.szName,
  &enLWIPDebugTimeout.szName,
  &enTCPEchoFlag.szName,
  &enTCPEchoPort.szName,
  &enDataDebugFlag.szName,
  &enIOModeDebugFlag.szName,
  &enLED0Mode.szName,
  &enLED1Mode.szName,
};


const uint wControlsSize = sizeof(mppcszControls) / sizeof(mppcszControls[0]);
