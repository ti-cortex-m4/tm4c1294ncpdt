/*------------------------------------------------------------------------------
UDP_IN,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/entities.h"
#include "../kernel/log.h"
#include "../kernel/settings.h"
#include "driverlib/sysctl.h"
#include "../hardware/storage.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_cmd.h"
#include "routing_status.h"
#include "udp_in.h"



typedef err_t (*in_fn)(struct pbuf *p);


typedef struct
{
  struct udp_pcb *pcb;
  struct pbuf *p;
  struct ip_addr *addr;
  uint port;
  uchar broadcast;
} udp_arg;



err_t CmdX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  if (p->len > 1)
  {
    err_t err = PopSfx(p, &wSfx);
    if (err != ERR_OK) return err;
  }

  InitPush();
  PushString("A");
  PushArrayString(pbMac, 6);
  PushString("/");
  PushString("000001001"); // TODO "000001001"
  PushString("/");
  PushString("N**M*"); // TODO "N**M*"
  PushString("/");
  PushString("**"); // TODO "**"
  PushString("/");
  PushString(szOwnerName);
  PushString("/");
  PushString(szDeviceName);
  PushString("/");
  PushCharDec(UART_COUNT);

  if (p->len > 1)
  {
    PushSfx(wSfx);
  }

  return PushOut(pcb,p,addr,port,broadcast);
}

err_t CmdW(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}

err_t CmdIn(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, in_fn in)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = in(p);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}


err_t CmdFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  uint wArg = 0;
  err = PopIntDec(p, &wArg, 2);
  if (err != ERR_OK) return err;

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
    case 63: PushString(enDebugMode.szName); break;
    case 64: PushString(enUdpDebugIP.szName); break;
    case 65: PushString(enUdpDebugPort.szName); break;
    case 66: PushString(enLwipDebugFlag.szName); break;
    case 67: PushString(enLwipDebugTimeout.szName); break;
    case 68: PushString(enDataDebugFlag.szName); break;
    case 69: PushString(enIOModeDebugFlag.szName); break;
    case 70: PushString(enLED0Mode.szName); break;
    case 71: PushString(enLED1Mode.szName); break;

    default: CONSOLE("WARNING unknown index %u\n", wArg); ASSERT(false); break; // TODO
  }

  PushChar(0x0D);
  PushChar(0x0A);
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}



static bool IsEnityCode(struct pbuf *p, uchar const bOperation, const char *szCode, uchar *pibStart)
{
//  const char *sz = szCode;

  uchar *pb = p->payload;
  uchar i = 0;

  if (i >= p->len) return false;
  if (pb[i++] != bOperation) return false;

  while (*szCode)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCode++) return false;
  }

//  CONSOLE_UART("code: %c%s %u\n", bOperation, sz, i);

  *pibStart = i;
  return true;
}

static err_t PopEntity(struct pbuf *p, entity const *pen, uchar *pibStart)
{
  uchar ibStart = *pibStart;

  if (ibStart == 0xFF)
  {
    CONSOLE_UART("WARNING index %u\n",ibStart);
    return -1;
  }
  else
  {
    switch (pen->eType)
    {
       case CHAR:
       {
         err_t err = PopCharDec(p, pen->pbRam, ibStart);
//         CONSOLE_UART("char[%u]=%u \n",ibStart,*(uchar *)pen->pbRAM);
         return err;
       }
       case INT:
       {
         err_t err = PopIntDec(p, pen->pbRam, ibStart);
//         CONSOLE_UART("int[%u]=%u \n",ibStart,*(uint *)pen->pbRAM);
         return err;
       }
       case IP:
       {
         err_t err = PopIP(p, pen->pbRam, ibStart);
//         CONSOLE_UART("long[%u]=%08x \n",ibStart,*(ulong *)pen->pbRAM);
         return err;
       }
       case STRING:
       {
         err_t err = PopString(p, (char *)pen->pbRam, NAME_SIZE, ibStart);
         return err;
       }
       default: ASSERT(false); return -1;
    }
  }
}

err_t SetEntity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, entity const *pen, uchar *pibStart)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = PopEntity(p, pen, pibStart);
  if (err != ERR_OK) return err;

  err = SaveEntity(pen);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}

static bool IsEnity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast, entity const *pen) // TODO check errors
{
  uchar ibStart = 0xFF;
  if (IsEnityCode(p, 'G', pen->szCode, &ibStart))
  {
    switch (pen->eType)
    {
      case CHAR: CmdCharDec(pcb,p,addr,port,broadcast,*(uchar *)pen->pbRam); break;
      case INT: CmdIntDec(pcb,p,addr,port,broadcast,*(uint *)pen->pbRam); break;
      case IP: CmdIP(pcb,p,addr,port,broadcast,*(ulong *)pen->pbRam); break;
      case STRING: CmdString(pcb,p,addr,port,broadcast,(const char *)pen->pbRam); break;
      default: ASSERT(false); break;
    }

    return true;
  }
  else if (IsEnityCode(p, 'S', pen->szCode, &ibStart))
  {
    SetEntity(pcb,p,addr,port,broadcast,pen,&ibStart);
    return true;
  }
  else
  {
    return false;
  }
}

void    UDPInput(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
{
//  CONSOLE_UART("broadcast: %d\n", broadcast);

  if (IsCmd(p,"X")) {
    CmdX(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"W")) {
    CmdW(pcb,p,addr,port,broadcast); // TODO
  } else if (IsCmd(p,"E")) {
    SysCtlReset();
  } else if (IsCmd(p,"L")) {
    CmdString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"I")) {
    ResetSettings();
    CmdString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"O")) {
    CmdString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"V")) {
    CmdString(pcb,p,addr,port,broadcast,"{ds1.0}");
  } else if (IsCmd(p,"H")) {
    CmdString(pcb,p,addr,port,broadcast,"1A");
  } else if (IsCmd(p,"CS")) {
    CmdString(pcb,p,addr,port,broadcast,"72");
  } else if (IsCmd(p,"FS")) {
    CmdFS(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsRoutingStatusSize(p)) {
    GetRouingStatusSize(pcb,p,addr,port,broadcast);
  }

  else if (IsEnity(pcb,p,addr,port,broadcast,&enOwnerName)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDeviceName)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enIP)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enGateway)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enNetmask)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate4)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity0)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enParity4)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits0)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataBits4)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits0)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits3)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enStopBits4)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enSerialNumber)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDebugMode)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enUdpDebugIP)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enUdpDebugPort)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enLwipDebugFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enLwipDebugTimeout)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDataDebugFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enIOModeDebugFlag)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enLED0Mode)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enLED1Mode)) {}

  else if (IsRoutingStatusContent(p)) {
    GetRouingStatusContent(pcb,p,addr,port,broadcast);
  }

  else { // TODO
    CONSOLE_UART("unknown command\n");
  }
}
