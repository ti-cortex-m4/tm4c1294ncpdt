/*------------------------------------------------------------------------------
udp_out_fs,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "../kernel/entities.h"
#include "../kernel/wrappers.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "udp_out_fs.h"



err_t OutFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  uint2 w2 = PopIntDec(p, 2);
  if (InvalidInt2(w2)) return w2.err;
  uint wArg = w2.w;

  InitPush();

  switch (wArg)
  {
    case 0: PushString("AI=$GENERAL;D=General;T=GROUP"); break;
    case 1: PushString(enOwnerName.szName); break;
    case 2: PushString(enDeviceName.szName); break;
    case 3: PushString(enIP.szName); break;
    case 4: PushString(enGateway.szName); break;
    case 5: PushString(enNetmask.szName); break;

    case 6: PushString("AI=$CHANNEL1;D=Channel1;T=GROUP"); break;
    case 7: PushString(enConnectionTimeout0.szName); break;
    case 8: PushString(enRoutingMode0.szName); break;
    case 9: PushString(enPort0.szName); break;
    case 10: PushString(enConnectionMode0.szName); break;
    case 11: PushString(enDestinationIP0.szName); break;
    case 12: PushString(enDestinationPort0.szName); break;
    case 13: PushString(enBaudRate0.szName); break;
    case 14: PushString(enParity0.szName); break;
    case 15: PushString(enDataBits0.szName); break;
    case 16: PushString(enStopBits0.szName); break;

    case 17: PushString("AI=$CHANNEL2;D=Channel2;T=GROUP"); break;
    case 18: PushString(enConnectionTimeout1.szName); break;
    case 19: PushString(enRoutingMode1.szName); break;
    case 20: PushString(enPort1.szName); break;
    case 21: PushString(enConnectionMode1.szName); break;
    case 22: PushString(enDestinationIP1.szName); break;
    case 23: PushString(enDestinationPort1.szName); break;
    case 24: PushString(enBaudRate1.szName); break;
    case 25: PushString(enParity1.szName); break;
    case 26: PushString(enDataBits1.szName); break;
    case 27: PushString(enStopBits1.szName); break;

    case 28: PushString("AI=$CHANNEL3;D=Channel3;T=GROUP"); break;
    case 29: PushString(enConnectionTimeout2.szName); break;
    case 30: PushString(enRoutingMode2.szName); break;
    case 31: PushString(enPort2.szName); break;
    case 32: PushString(enConnectionMode2.szName); break;
    case 33: PushString(enDestinationIP2.szName); break;
    case 34: PushString(enDestinationPort2.szName); break;
    case 35: PushString(enBaudRate2.szName); break;
    case 36: PushString(enParity2.szName); break;
    case 37: PushString(enDataBits2.szName); break;
    case 38: PushString(enStopBits2.szName); break;

    case 39: PushString("AI=$CHANNEL4;D=Channel4;T=GROUP"); break;
    case 40: PushString(enConnectionTimeout3.szName); break;
    case 41: PushString(enRoutingMode3.szName); break;
    case 42: PushString(enPort3.szName); break;
    case 43: PushString(enConnectionMode3.szName); break;
    case 44: PushString(enDestinationIP3.szName); break;
    case 45: PushString(enDestinationPort3.szName); break;
    case 46: PushString(enBaudRate3.szName); break;
    case 47: PushString(enParity3.szName); break;
    case 48: PushString(enDataBits3.szName); break;
    case 49: PushString(enStopBits3.szName); break;

    case 50: PushString("AI=$CHANNEL5;D=Channel5;T=GROUP"); break;
    case 51: PushString(enConnectionTimeout4.szName); break;
    case 52: PushString(enRoutingMode4.szName); break;
    case 53: PushString(enPort4.szName); break;
    case 54: PushString(enConnectionMode4.szName); break;
    case 55: PushString(enDestinationIP4.szName); break;
    case 56: PushString(enDestinationPort4.szName); break;
    case 57: PushString(enBaudRate4.szName); break;
    case 58: PushString(enParity4.szName); break;
    case 59: PushString(enDataBits4.szName); break;
    case 60: PushString(enStopBits4.szName); break;

    case 61: PushString("AI=$SETTINGS;D=Settings;T=GROUP"); break;
    case 62: PushString(enSerialNumber.szName); break;
    case 63: PushString(enWatchdogFlag.szName); break;
    case 64: PushString(enDebugMode.szName); break;
    case 65: PushString(enUDPDebugIP.szName); break;
    case 66: PushString(enUDPDebugPort.szName); break;
    case 67: PushString(enLwipDebugFlag.szName); break;
    case 68: PushString(enLwipDebugTimeout.szName); break;
    case 69: PushString(enDataDebugFlag.szName); break;
    case 70: PushString(enIOModeDebugFlag.szName); break;
    case 71: PushString(enLED0Mode.szName); break;
    case 72: PushString(enLED1Mode.szName); break;

    default: WARNING("unknown index %u\n", wArg); break; // TODO
  }

  PushChar(0x0D);
  PushChar(0x0A);
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}
