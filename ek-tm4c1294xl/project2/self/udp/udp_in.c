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
#include "udp_out.h"
#include "udp_out_fs.h"
#include "udp_cmd.h"
#include "routing_status.h"
#include "test_watchdog.h"
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
    uint2 w2 = PopSuffix(p);
    if (InvalidInt2(w2)) return w2.err;
    wSfx = w2.w;
  }

  InitPush();
  PushString("A");
  PushMAC(pbMac, 6);
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
    PushSuffix(wSfx);
  }

  return Out(pcb,p,addr,port,broadcast);
}

err_t CmdW(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}

err_t CmdIn(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, in_fn in)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  err_t err = in(p);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
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

//  WARNING("code: %c%s %u\n", bOperation, sz, i);

  *pibStart = i;
  return true;
}

static err_t PopEntity(struct pbuf *p, entity const *pen, uchar *pibStart)
{
  uchar ibStart = *pibStart;

  if (ibStart == 0xFF)
  {
    WARNING("index %u\n",ibStart);
    return -1;
  }
  else
  {
    switch (pen->eType)
    {
       case CHAR:
       {
         uchar2 b2 = PopCharDec(p, ibStart);
         if (!InvalidChar2(b2)) {
           (*(uchar *)pen->pbRam) = b2.b;
         }
//         WARNING("char[%u]=%u \n",ibStart,*(uchar *)pen->pbRAM);
         return b2.err;
       }
       case INT:
       {
         uint2 w2 = PopIntDec(p, ibStart);
         if (!InvalidInt2(w2)) {
           *(uint *)pen->pbRam = w2.w;
         }
//         WARNING("int[%u]=%u \n",ibStart,*(uint *)pen->pbRAM);
         return w2.err;
       }
       case IP:
       {
         ulong2 dw2 = PopIP(p, ibStart);
         if (!InvalidLong2(dw2)) {
           *(ulong *)pen->pbRam = dw2.dw;
         }
//         WARNING("long[%u]=%08x \n",ibStart,*(ulong *)pen->pbRAM);
         return dw2.err;
       }
       case STRING:
       {
         err_t err = PopBuff(p, (char *)pen->pbRam, NAME_SIZE, ibStart);
         return err;
       }
       default: ASSERT(false); return -1;
    }
  }
}

err_t SetEntity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, entity const *pen, uchar *pibStart)
{
  uint2 wSfx = PopSuffix(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  err_t err = PopEntity(p, pen, pibStart);
  if (err != ERR_OK) return err;

  err = SaveEntity(pen);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushSuffix(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
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
//  CONSOLE("broadcast: %d\n", broadcast);

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
    CmdString(pcb,p,addr,port,broadcast,"73");
  } else if (IsCmd(p,"FS")) {
    OutFS(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsRoutingStatusSize(p)) {
    GetRouingStatusSize(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"watchdog")) {
    TestWatchdog(pcb,p,addr,port,broadcast);
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

  else if (IsEnity(pcb,p,addr,port,broadcast,&enWatchdogFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDebugMode)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enUDPDebugIP)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enUDPDebugPort)) {}

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
    WARNING("unknown command\n");
  }
}
