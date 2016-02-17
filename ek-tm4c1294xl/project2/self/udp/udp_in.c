/*------------------------------------------------------------------------------
UDP_IN.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "../settings_eeprom.h"
#include "../entity.h"
#include "driverlib/sysctl.h"
#include "../uart/log.h"
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
    case 4: PushString("AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*"); break;
    case 5: PushString("AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*"); break;

    case 6: PushString("AI=$CHANNEL1;D=Channel1;T=GROUP"); break;
    case 7: PushString(enConnectionTimeout0.szName); break;
    case 8: PushString(enRoutingMode0.szName); break;
    case 9: PushString(enPort0.szName); break;
    case 10: PushString(enDestinationIP0.szName); break;
    case 11: PushString(enDestinationPort0.szName); break;
    case 12: PushString(enBaudRate0.szName); break;

    case 13: PushString("AI=$CHANNEL2;D=Channel2;T=GROUP"); break;
    case 14: PushString(enConnectionTimeout1.szName); break;
    case 15: PushString(enRoutingMode1.szName); break;
    case 16: PushString(enPort1.szName); break;
    case 17: PushString(enDestinationIP1.szName); break;
    case 18: PushString(enDestinationPort1.szName); break;
    case 19: PushString(enBaudRate1.szName); break;

    case 20: PushString("AI=$DEBUG;D=Debug;T=GROUP"); break;
    case 21: PushString(enUdpDebugFlag.szName); break;
    case 22: PushString(enUdpDebugPort.szName); break;

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
  err_t err = PopIP(p, &dw);
  if (err != ERR_OK) return err;

  dwIP = dw;
  err = SaveIP();
  if (err != ERR_OK) return err;

  return ERR_OK;
}

err_t SGI(struct pbuf *p)
{
  ulong dw = 0;
  err_t err = PopIP(p, &dw);
  if (err != ERR_OK) return err;

  dwGateway = dw;
  err = SaveGateway();
  if (err != ERR_OK) return err;

  return ERR_OK;
}

err_t SNM(struct pbuf *p)
{
  ulong dw = 0;
  err_t err = PopIP(p, &dw);
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

static bool IsEnityCode(struct pbuf *p, uchar const bOperation, const char *szCode)
{
  uchar *pb = p->payload;
  uchar i = 0;

  if (i >= p->len) return false;
  if (pb[i++] != bOperation) return false;

  while (*szCode)
  {
    if (i >= p->len) return false;
    if (pb[i++] != *szCode++) return false;
  }

  return true;
}

static err_t PopEntity(struct pbuf *p, entity const *pen)
{
  switch (pen->eType)
  {
     case CHAR: return PopCharDec(p, pen->pbRAM, 3);
     case INT: return PopIntDec(p, pen->pbRAM, 3);
     case LONG: return PopIP(p, pen->pbRAM);
     default: ASSERT(false); return -1;
  }
}

err_t SetEntity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, entity const *pen)
{
  uint wSfx = 0;
  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = PopEntity(p, pen);
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
  if (IsEnityCode(p, 'G', pen->szCode))
  {
    switch (pen->eType)
    {
      case CHAR: CmdCharDec(pcb,p,addr,port,broadcast,*(uchar *)pen->pbRAM); break;
      case INT: CmdIntDec(pcb,p,addr,port,broadcast,*(uint *)pen->pbRAM); break;
      case LONG: CmdIP(pcb,p,addr,port,broadcast,*(ulong *)pen->pbRAM); break;
      default: ASSERT(false); break;
    }

    return true;
  }
  else if (IsEnityCode(p, 'S', pen->szCode))
  {
    SetEntity(pcb,p,addr,port,broadcast,pen);
    return true;
  }
  else
  {
    return false;
  }
}

void    UDP_In(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
{
  LOG(("broadcast: %d\n", broadcast));

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
    CmdString(pcb,p,addr,port,broadcast,"23");
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

  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout0)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enConnectionTimeout1)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode0)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enRoutingMode1)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort0)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enPort1)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP0)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationIP1)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort0)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enDestinationPort1)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate0)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enBaudRate1)) {
  }

  else if (IsEnity(pcb,p,addr,port,broadcast,&enUdpDebugFlag)) {
  }
  else if (IsEnity(pcb,p,addr,port,broadcast,&enUdpDebugPort)) {
  }

  else { // TODO
  }
}
