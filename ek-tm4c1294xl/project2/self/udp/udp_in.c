/*------------------------------------------------------------------------------
UDP_IN,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "../settings_eeprom.h"
#include "../kernel/entities.h"
#include "../kernel/log.h"
#include "driverlib/sysctl.h"
#include "../uart/uart_log.h"
#include "udp_pop.h"
#include "udp_push.h"
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



err_t CmdString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *sz)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushString(sz);
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}


err_t CmdIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, ulong dw)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushIP(dw);
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}

err_t CmdCharDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, uchar b)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushCharDec(b);
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}

err_t CmdIntDec(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, uint w)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  InitPush();
  PushChar('A');
  PushIntDec(w);
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}


err_t CmdX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  InitPush();
  PushString("A");
  PushArrayString(pbMAC, 6);
  PushString("/");
  PushString("000001001");
  PushString("/");
  PushString("N**M*");
  PushString("/");
  PushString("**");
  PushString("/");
  PushString(szOwnerName);
  PushString("/");
  PushString(szDeviceName);
  PushString("/");
  PushString("4");

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
    case 1: PushString("AI=ON;D=Owner name;T=STRING;C=EDIT;MAXLEN=8;F=R*"); break;
    case 2: PushString("AI=DN;D=Device name;T=STRING;C=EDIT;MAXLEN=8;F=R*"); break;
    case 3: PushString("AI=IP;D=IP-address;T=STRING;C=IPCTRL;F=R*"); break;
    case 4: PushString("AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;F=R*"); break;
    case 5: PushString("AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;F=R*"); break;

    case 6: PushString("AI=$CHANNEL1;D=Channel1;T=GROUP"); break;
    case 7: PushString(enConnectionTimeout0.szName); break;
    case 8: PushString(enRoutingMode0.szName); break;
    case 9: PushString(enPort0.szName); break;
    case 10: PushString(enConnectionMode0.szName); break;
    case 11: PushString(enDestinationIP0.szName); break;
    case 12: PushString(enDestinationPort0.szName); break;
    case 13: PushString(enBaudRate0.szName); break;

    case 14: PushString("AI=$CHANNEL2;D=Channel2;T=GROUP"); break;
    case 15: PushString(enConnectionTimeout1.szName); break;
    case 16: PushString(enRoutingMode1.szName); break;
    case 17: PushString(enPort1.szName); break;
    case 18: PushString(enConnectionMode1.szName); break;
    case 19: PushString(enDestinationIP1.szName); break;
    case 20: PushString(enDestinationPort1.szName); break;
    case 21: PushString(enBaudRate1.szName); break;

    case 22: PushString("AI=$CHANNEL3;D=Channel3;T=GROUP"); break;
    case 23: PushString(enConnectionTimeout2.szName); break;
    case 24: PushString(enRoutingMode2.szName); break;
    case 25: PushString(enPort2.szName); break;
    case 26: PushString(enConnectionMode2.szName); break;
    case 27: PushString(enDestinationIP2.szName); break;
    case 28: PushString(enDestinationPort2.szName); break;
    case 29: PushString(enBaudRate2.szName); break;

    case 30: PushString("AI=$SETTINGS;D=Settings;T=GROUP"); break;
    case 31: PushString(enSerialNumber.szName); break;

    case 32: PushString("AI=$DEBUG;D=Debug;T=GROUP"); break;
    case 33: PushString(enDebugMode.szName); break;
    case 34: PushString(enUdpDebugIP.szName); break;
    case 35: PushString(enUdpDebugPort.szName); break;
    case 36: PushString(enLwIpDebugFlag.szName); break;
    case 37: PushString(enLwIpDebugTimeout.szName); break;

    default: ASSERT(false); break; // TODO
  }

  PushChar(0x0D);
  PushChar(0x0A);
  PushSfx(wSfx);

  return PushOut(pcb,p,addr,port,broadcast);
}


err_t SON(struct pbuf *p)
{
  err_t err = PopString(p, (char *)szOwnerName, NAME_SIZE);
  if (err != ERR_OK) return err;

  err = SaveOwnerName();
  if (err != ERR_OK) return err;

  return ERR_OK;
}


err_t SDN(struct pbuf *p)
{
  err_t err = PopString(p, (char *)szDeviceName, NAME_SIZE);
  if (err != ERR_OK) return err;

  err = SaveDeviceName();
  if (err != ERR_OK) return err;

  return ERR_OK;
}


err_t SIP(struct pbuf *p)
{
  ulong dw = 0;
  err_t err = PopIP(p, &dw, 3);
  if (err != ERR_OK) return err;

  dwIP = dw;
  err = SaveIP();
  if (err != ERR_OK) return err;

  return ERR_OK;
}

err_t SGI(struct pbuf *p)
{
  ulong dw = 0;
  err_t err = PopIP(p, &dw, 3);
  if (err != ERR_OK) return err;

  dwGateway = dw;
  err = SaveGateway();
  if (err != ERR_OK) return err;

  return ERR_OK;
}

err_t SNM(struct pbuf *p)
{
  ulong dw = 0;
  err_t err = PopIP(p, &dw, 3);
  if (err != ERR_OK) return err;

  dwNetmask = dw;
  err = SaveNetmask();
  if (err != ERR_OK) return err;

  return ERR_OK;
}

static bool IsCmd(struct pbuf *p, const char *szCmd)
{
  uchar *pb = p->payload;

  uchar i = 0;
  while (*szCmd)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCmd++) return false;
  }

  return true;
}

static bool IsEnityCode(struct pbuf *p, uchar const bOperation, const char *szCode, uchar *pibStart)
{
  const char *sz = szCode;

  uchar *pb = p->payload;
  uchar i = 0;

  if (i >= p->len) return false;
  if (pb[i++] != bOperation) return false;

  while (*szCode)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCode++) return false;
  }

  CONSOLE_UART("code: %c%s %u\n", bOperation, sz, i);

  *pibStart = i;
  return true;
}

static err_t PopEntity(struct pbuf *p, entity const *pen, uchar *pibStart)
{
  uchar ibStart = *pibStart;

  if (ibStart == 0xFF)
  {
    CONSOLE_UART("ERROR index %u\n",ibStart);
    return -1;
  }
  else
  {
    switch (pen->eType)
    {
       case CHAR:
       {
         err_t err = PopCharDec(p, pen->pbRAM, ibStart);
         CONSOLE_UART("char[%u]=%u \n",ibStart,*(uchar *)pen->pbRAM);
         return err;
       }
       case INT:
       {
         err_t err = PopIntDec(p, pen->pbRAM, ibStart);
         CONSOLE_UART("int[%u]=%u \n",ibStart,*(uint *)pen->pbRAM);
         return err;
       }
       case IP:
       {
         err_t err = PopIP(p, pen->pbRAM, ibStart);
         CONSOLE_UART("long[%u]=%08x \n",ibStart,*(ulong *)pen->pbRAM);
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
      case CHAR: CmdCharDec(pcb,p,addr,port,broadcast,*(uchar *)pen->pbRAM); break;
      case INT: CmdIntDec(pcb,p,addr,port,broadcast,*(uint *)pen->pbRAM); break;
      case IP: CmdIP(pcb,p,addr,port,broadcast,*(ulong *)pen->pbRAM); break;
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

void    UDP_In(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
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
  } else if (IsCmd(p,"O")) {
    CmdString(pcb,p,addr,port,broadcast,"");
  } else if (IsCmd(p,"V")) {
    CmdString(pcb,p,addr,port,broadcast,"{ds1.0}");
  } else if (IsCmd(p,"H")) {
    CmdString(pcb,p,addr,port,broadcast,"1A");
  } else if (IsCmd(p,"CS")) {
    CmdString(pcb,p,addr,port,broadcast,"38");
  } else if (IsCmd(p,"FS")) {
    CmdFS(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"GON")) {
    CmdString(pcb,p,addr,port,broadcast,szOwnerName);
  } else if (IsCmd(p,"SON")) {
    CmdIn(pcb,p,addr,port,broadcast,SON);
  } else if (IsCmd(p,"GDN")) {
    CmdString(pcb,p,addr,port,broadcast,szDeviceName);
  } else if (IsCmd(p,"SDN")) {
    CmdIn(pcb,p,addr,port,broadcast, SDN);
  }

  else if (IsCmd(p,"GIP")) {
    CmdIP(pcb,p,addr,port,broadcast,dwIP);
  } else if (IsCmd(p,"SIP")) {
    CmdIn(pcb,p,addr,port,broadcast,SIP);
  }

  else if (IsCmd(p,"GGI")) {
    CmdIP(pcb,p,addr,port,broadcast,dwGateway);
  } else if (IsCmd(p,"SGI")) {
    CmdIn(pcb,p,addr,port,broadcast,SGI);
  }

  else if (IsCmd(p,"GNM")) {
    CmdIP(pcb,p,addr,port,broadcast,dwNetmask);
  } else if (IsCmd(p,"SNM")) {
    CmdIn(pcb,p,addr,port,broadcast,SNM);
  }

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionMode0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate2)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate1)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate0)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enSerialNumber)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enDebugMode)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enUdpDebugIP)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enUdpDebugPort)) {}

  else if (IsEnity(pcb,p,addr,port,broadcast,&enLwIpDebugFlag)) {}
  else if (IsEnity(pcb,p,addr,port,broadcast,&enLwIpDebugTimeout)) {}

  else { // TODO
    CONSOLE_UART("unknown command: %d\n", broadcast);
  }
}
