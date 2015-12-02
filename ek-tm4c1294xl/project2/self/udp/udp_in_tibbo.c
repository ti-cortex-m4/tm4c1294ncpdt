/*------------------------------------------------------------------------------
UDP_IN_TIBBO.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
//#include "../delay.h"
#include "driverlib/sysctl.h"
#include "../uart/log.h"
#include                "lwip/inet.h"
#include "udp_out.h"
#include "udp_pop.h"
#include "udp_push.h"
#include "udp_in_tibbo.h"



err_t CommandString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *sz)
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

err_t CommandIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, ulong  dw)
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

err_t CommandX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
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


err_t CommandL(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
//  err_t err = CheckSize(p, 1+1+1+2);
//  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandV(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
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


err_t CommandH(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A1A");
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandCS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A7");
  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSfx(p, &wSfx);
  if (err != ERR_OK) return err;

  uint wNumber = 0;
  err = PopIntArg(p, &wNumber);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  if (wNumber == 0) {
    PushString("AI=$GENERAL;D=General;T=GROUP");
  } else if (wNumber == 1) {
    PushString("AI=ON;D=Owner name;T=STRING;C=EDIT;MAXLEN=8;F=R*");
  } else if (wNumber == 2) {
    PushString("AI=DN;D=Device name;T=STRING;C=EDIT;MAXLEN=8;F=R*");
  } else if (wNumber == 3) {
    PushString("AI=DH;D=DHCP;T=INT;C=STATIC;O=0- Disabled/0/1- Enabled/1;F=R");
  } else if (wNumber == 4) {
    PushString("AI=IP;D=IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*");
  } else if (wNumber == 5) {
    PushString("AI=GI;D=Gateway IP-address;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*");
  } else if (wNumber == 6) {
    PushString("AI=NM;D=Subnet mask;T=STRING;C=IPCTRL;S=DH==1?\"a\":\"e\";F=R*");
  }

  PushChar(0x0D);
  PushChar(0x0A);

  PushSfx(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

/*
err_t CommandGPW(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wSfx = 0;

  err_t err = PopSuffix(p, &wSfx);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A");
  PushSuffix(wSfx);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}
*/

err_t CommandGON(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
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

err_t CommandGDN(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
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


err_t CommandSON(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
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

err_t CommandSDN(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
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


void    UDP_InTibbo(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
{
  LOG(("broadcast: %d\n", broadcast));

  if (IsCmd(p,"X")) {
    CommandX(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"E")) {
    SysCtlReset();
  } else if (IsCmd(p,"L")) {
    CommandString(pcb,p,addr,port,broadcast,"A");
  } else if (IsCmd(p,"O")) {
    CommandString(pcb,p,addr,port,broadcast,"A");
  } else if (IsCmd(p,"V")) {
    CommandV(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"H")) {
    CommandH(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"CS")) {
    CommandCS(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"FS")) {
    CommandFS(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GPW")) {
    CommandString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"SPW")) {
    CommandString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"GON")) {
    CommandGON(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GDN")) {
    CommandGDN(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"GDH")) {
    CommandString(pcb,p,addr,port,broadcast,"0");
  } else if (IsCmd(p,"GIP")) {
    CommandIP(pcb,p,addr,port,broadcast,inet_addr("100.1.168.192"));
  } else if (IsCmd(p,"GGI")) {
    CommandIP(pcb,p,addr,port,broadcast,inet_addr("0.255.255.255"));
  } else if (IsCmd(p,"GNM")) {
    CommandIP(pcb,p,addr,port,broadcast,inet_addr("1.1.168.192"));
  } else if (IsCmd(p,"SON")) {
    CommandSON(pcb,p,addr,port,broadcast);
  } else if (IsCmd(p,"SDN")) {
    CommandSDN(pcb,p,addr,port,broadcast);
  }
}
