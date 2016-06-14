/*------------------------------------------------------------------------------
controls.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "entities.h"
#include "controls.h"



static message pcszGeneral = "AI=$GENERAL;D=General;T=GROUP";
static message pcszChannel0 = "AI=$CHANNEL1;D=Channel1;T=GROUP";
static message pcszChannel1 = "AI=$CHANNEL2;D=Channel2;T=GROUP";
static message pcszChannel2 = "AI=$CHANNEL3;D=Channel3;T=GROUP";
static message pcszChannel3 = "AI=$CHANNEL4;D=Channel4;T=GROUP";
static message pcszChannel4 = "AI=$CHANNEL5;D=Channel5;T=GROUP";
static message pcszSettings = "AI=$SETTINGS;D=Settings;T=GROUP";



const message * const mppcszControls[] =
{
  &pcszGeneral,
  &enOwnerName.szName,
  &enDeviceName.szName,
  &enIP.szName,
  &enGateway.szName,
  &enNetmask.szName,

  &pcszChannel0,
  &enConnectionTimeout0.szName,
  &enRoutingMode0.szName,
  &enPort0.szName,
  &enConnectionMode0.szName,
  &enDestinationIP0.szName,
  &enDestinationPort0.szName,
  &enBaudRate0.szName,
  &enParity0.szName,
  &enDataBits0.szName,
  &enStopBits0.szName,

  &pcszChannel1,
  &enConnectionTimeout1.szName,
  &enRoutingMode1.szName,
  &enPort1.szName,
  &enConnectionMode1.szName,
  &enDestinationIP1.szName,
  &enDestinationPort1.szName,
  &enBaudRate1.szName,
  &enParity1.szName,
  &enDataBits1.szName,
  &enStopBits1.szName,

  &pcszChannel2,
  &enConnectionTimeout2.szName,
  &enRoutingMode2.szName,
  &enPort2.szName,
  &enConnectionMode2.szName,
  &enDestinationIP2.szName,
  &enDestinationPort2.szName,
  &enBaudRate2.szName,
  &enParity2.szName,
  &enDataBits2.szName,
  &enStopBits2.szName,

  &pcszChannel3,
  &enConnectionTimeout3.szName,
  &enRoutingMode3.szName,
  &enPort3.szName,
  &enConnectionMode3.szName,
  &enDestinationIP3.szName,
  &enDestinationPort3.szName,
  &enBaudRate3.szName,
  &enParity3.szName,
  &enDataBits3.szName,
  &enStopBits3.szName,

  &pcszChannel4,
  &enConnectionTimeout4.szName,
  &enRoutingMode4.szName,
  &enPort4.szName,
  &enConnectionMode4.szName,
  &enDestinationIP4.szName,
  &enDestinationPort4.szName,
  &enBaudRate4.szName,
  &enParity4.szName,
  &enDataBits4.szName,
  &enStopBits4.szName,

  &pcszSettings,
  &enSerialNumber.szName,
  &enWatchdogFlag.szName,
  &enDebugMode.szName,
  &enUDPDebugIP.szName,
  &enUDPDebugPort.szName,
  &enLwipDebugFlag.szName,
  &enLwipDebugTimeout.szName,
  &enDataDebugFlag.szName,
  &enIOModeDebugFlag.szName,
  &enLED0Mode.szName,
  &enLED1Mode.szName,
};


const uint wControlsSize = sizeof(mppcszControls) / sizeof(mppcszControls[0]);