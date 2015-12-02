/*------------------------------------------------------------------------------
UDP_IN.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "driverlib/sysctl.h"
#include "lwip/inet.h" // TODO
#include "../uart/log.h"
#include "udp_out.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_in_tibbo.h"



err_t CmdString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *sz)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushString(sz);
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CmdIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, ulong  dw)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushIP(dw);
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CmdX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

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

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CmdV(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A{ds1.0}");
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CmdFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  uint wArg = 0;
  err = PopIntArg(p, &wArg);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  if (wArg == 0) {
    PushString("AI=$GENERAL;D=General;T=GROUP");
  } else if (wArg == 1) {
    PushString("AI=ON;D=Owner name;T=STRING;C=EDIT;MAXLEN=8;F=R*");
  } else if (wArg == 2) {
    PushString("AI=DN;D=Device name;T=STRING;C=EDIT;MAXLEN=8;F=R*");
  } else if (wArg == 3) {
    PushString("AI=DH;D=DHCP;T=INT;C=STATIC;O=0- Disabled/0/1- Enabled/1;F=R");
  } else if (wArg == 4) {
    PushString("AI=IP;D=IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*");
  } else if (wArg == 5) {
    PushString("AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*");
  } else if (wArg == 6) {
    PushString("AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*");
  }

  PushChar(0x0D);
  PushChar(0x0A);

  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CmdGON(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A");
  PushString(szOwnerName);
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CmdGDN(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A");
  PushString(szDeviceName);
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CmdSON(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = PopStringArg(p, (char *)szOwnerName, NAME_SIZE);
  if (err != ERR_OK) return err;

  err = SaveOwnerName();
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CmdSDN(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = PopStringArg(p, (char *)szDeviceName, NAME_SIZE);
  if (err != ERR_OK) return err;

  err = SaveDeviceName();
  if (err != ERR_OK) return err;


  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
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
    CmdString(pcb,p,addr,port,broadcast,"7");
  } else if (IsCmd(p,"FS")) {
    CmdFS(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"GON")) {
    CmdGON(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GDN")) {
    CmdGDN(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GDH")) {
    CmdString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"GIP")) {
    CmdIP(pcb,p,addr,port,broadcast,inet_addr("100.1.168.192"));
  } else if (IsCmd(p,"GGI")) {
    CmdIP(pcb,p,addr,port,broadcast,inet_addr("0.255.255.255"));
  } else if (IsCmd(p,"GNM")) {
    CmdIP(pcb,p,addr,port,broadcast,inet_addr("1.1.168.192"));
  } else if (IsCmd(p,"SON")) {
    CmdSON(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"SDN")) {
    CmdSDN(pcb,p,addr,port,broadcast);
  }
}
