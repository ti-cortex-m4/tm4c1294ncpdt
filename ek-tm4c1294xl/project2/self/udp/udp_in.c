/*------------------------------------------------------------------------------
UDP_IN.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "driverlib/sysctl.h"
#include "../uart/log.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_in.h"



typedef err_t (*in_fn)(struct pbuf *p);



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
  err = PopIntHex(p, &wArg, 2);
  if (err != ERR_OK) return err;

  InitPush();

  switch (wArg)
  {
    case 0: PushString("AI=$GENERAL;D=General;T=GROUP"); break;
    case 1: PushString("AI=ON;D=Owner name;T=STRING;C=EDIT;MAXLEN=8;F=R*"); break;
    case 2: PushString("AI=DN;D=Device name;T=STRING;C=EDIT;MAXLEN=8;F=R*"); break;
    case 3: PushString("AI=DH;D=DHCP;T=INT;C=STATIC;O=0- Disabled/0/1- Enabled/1;F=R"); break;
    case 4: PushString("AI=IP;D=IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*"); break;
    case 5: PushString("AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*"); break;
    case 6: PushString("AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*"); break;
    case 7: PushString("AI=$CHANNEL1;D=Channel1;T=GROUP"); break;
    case 8: PushString("AI=PN;D=Port;T=INT;C=EDIT;V=PN>65534?\"Port number must be between 0 and 65534\":\"\""); // TODO S=RM!=2?"e":"i" break;
    case 9: PushString("AI=BR;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13"); break;
    case 10: PushString("AI=RM;D=Routing Mode;T=INT;C=STATIC;O=0- Server (Slave)/0/1- Server OR Client (Master)/1/2- Client only/2"); break;
    case 11: PushString("AI=PN;E=1;D=Port;T=INT;C=EDIT;V=PN>65534||PN==32767?\"Port number must be between 0 and 65534 (excluding 32767)\":\"\";S=RM!=2?\"e\":\"i\""); break;
    case 12: PushString("AI=DI;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM==1||RM==2||SF==1?\"e\":\"i\""); break;
    case 13: PushString("AI=DP;E=1;D=Destination port;T=INT;C=EDIT;S=RM!=0?\"e\":\"i\""); break;
    default: ASSERT(false); break;
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

err_t SPN(struct pbuf *p)
{
  uint w = 0;
  err_t err = PopIntDec(p, &w, 3);
  if (err != ERR_OK) return err;

  wPort = w;
  err = SavePort();
  if (err != ERR_OK) return err;

  return ERR_OK;
}

err_t SBR(struct pbuf *p)
{
  uchar b = 0;
  err_t err = PopCharDec(p, &b, 3);
  if (err != ERR_OK) return err;

  ibBaud = b;
  err = SaveBaud();
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
    CmdString(pcb,p,addr,port,broadcast,"10");
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
  } else if (IsCmd(p,"GDH")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"GIP")) {
    CmdIP(pcb,p,addr,port,broadcast,dwIP);
  } else if (IsCmd(p,"SIP")) {
    CmdIn(pcb,p,addr,port,broadcast,SIP);
  } else if (IsCmd(p,"GGI")) {
    CmdIP(pcb,p,addr,port,broadcast,dwGateway);
  } else if (IsCmd(p,"SGI")) {
    CmdIn(pcb,p,addr,port,broadcast,SGI);
  } else if (IsCmd(p,"GNM")) {
    CmdIP(pcb,p,addr,port,broadcast,dwNetmask);
  } else if (IsCmd(p,"SNM")) {
    CmdIn(pcb,p,addr,port,broadcast,SNM);
  } else if (IsCmd(p,"GPN")) {
    CmdIntDec(pcb,p,addr,port,broadcast,wPort);
  } else if (IsCmd(p,"SPN")) {
    CmdIn(pcb,p,addr,port,broadcast,SPN);
  } else if (IsCmd(p,"GBR")) {
    CmdCharDec(pcb,p,addr,port,broadcast,ibBaud);
  } else if (IsCmd(p,"SBR")) {
    CmdIn(pcb,p,addr,port,broadcast,SBR);
  }
}
