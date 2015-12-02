/*------------------------------------------------------------------------------
UDP_IN_TIBBO.C


------------------------------------------------------------------------------*/

#include "../main.h"
//#include "../settings.h"
//#include "../delay.h"
//#include "driverlib/sysctl.h"
#include "../uart/log.h"
#include                "lwip/inet.h"
#include "udp_out.h"
#include "udp_push.h"
#include "udp_in_tibbo.h"



err_t CommandString(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, const char *sz)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushString(sz);
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CommandIPCtrl(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, ulong  dw)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushIPString(dw);
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CommandX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A0.36.119.81.168.16/000001001/N**M*/**/Mikron/Eth-RS/4");

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandL(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
//  err_t err = CheckSize(p, 1+1+1+2);
//  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandV(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A{ds1.0}");
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandH(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A1A");
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandCS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A7");
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  uint wNumber = 0;
  err = PopNumber(p, 2, &wNumber);
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

  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandGPW(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("A");
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t CommandGON(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("AMikron");
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

err_t CommandGDN(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint wCode2 = 0;

  err_t err = PopSuffix(p, &wCode2);
  if (err != ERR_OK) return err;

  err = InitPush(&p, 100);
  if (err != ERR_OK) return err;

  PushString("AEth-RS");
  PushSuffix(wCode2);

  UDPOutput2(pcb,p,addr,port,broadcast);
  return ERR_OK;
}

void    UDP_InTibbo(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast)
{
  LOG(("broadcast: %d\n", broadcast));

  uchar *pbBuff = p->payload;

  if (pbBuff[0] == 'X') {
    CommandX(pcb,p,addr,port,broadcast);
  } else if (pbBuff[0] == 'L') {
    CommandString(pcb,p,addr,port,broadcast,"A");
  } else if (pbBuff[0] == 'O') {
    CommandString(pcb,p,addr,port,broadcast,"A");
  } else if (pbBuff[0] == 'V') {
    CommandV(pcb,p,addr,port,broadcast);
  } else if (pbBuff[0] == 'H') {
    CommandH(pcb,p,addr,port,broadcast);
  } else if ((pbBuff[0] == 'C') && (pbBuff[1] == 'S')) {
    CommandCS(pcb,p,addr,port,broadcast);
  } else if ((pbBuff[0] == 'F') && (pbBuff[1] == 'S')) {
    CommandFS(pcb,p,addr,port,broadcast);
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'P') && (pbBuff[2] == 'W')) {
    CommandGPW(pcb,p,addr,port,broadcast);
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'O') && (pbBuff[2] == 'N')) {
    CommandGON(pcb,p,addr,port,broadcast);
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'D') && (pbBuff[2] == 'N')) {
    CommandGDN(pcb,p,addr,port,broadcast);
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'D') && (pbBuff[2] == 'H')) {
    CommandString(pcb,p,addr,port,broadcast,"0");
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'I') && (pbBuff[2] == 'P')) {
    CommandIPCtrl(pcb,p,addr,port,broadcast,inet_addr("100.1.168.192"));
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'G') && (pbBuff[2] == 'I')) {
    CommandIPCtrl(pcb,p,addr,port,broadcast,inet_addr("0.255.255.255"));
  } else if ((pbBuff[0] == 'G') && (pbBuff[1] == 'N') && (pbBuff[2] == 'M')) {
    CommandIPCtrl(pcb,p,addr,port,broadcast,inet_addr("1.1.168.192"));
  }
}
