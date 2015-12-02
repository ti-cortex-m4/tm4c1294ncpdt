/*------------------------------------------------------------------------------
UDP_OUTPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "udp_push.h"
#include "udp_out.h"



static bool             fActive;
static uint             wCode;



void InitUDP_Out(void)
{
  fActive = true;
}

// TODO
bool IsActive_UDPOutput(void)
{
  return fActive;
}



static err_t CheckSize(struct pbuf *p, uchar bSize)
{
  return (p->len != bSize) ? ERR_SIZE : ERR_OK;
}


static bool CheckMAC(struct pbuf *p, uchar i)
{
  uchar *pb = p->payload;

  return ((pb[0] == pbMAC[0]) &&
          (pb[1] == pbMAC[1]) &&
          (pb[2] == pbMAC[2]) &&
          (pb[3] == pbMAC[3]) &&
          (pb[4] == pbMAC[4]) &&
          (pb[5] == pbMAC[5]));
}



static uchar PopChar(struct pbuf *p, uchar i)
{
  uchar *pb = p->payload;
  return pb[i];
}


static uint PopIntLtl(struct pbuf *p, uchar i)
{
  return PopChar(p, i) + PopChar(p, i+1)*0x100;
}


static ulong PopLongLtl(struct pbuf *p, uchar i)
{
  combo32 cb;
  cb.mpbBuff[0] = PopChar(p, i+0);
  cb.mpbBuff[1] = PopChar(p, i+1);
  cb.mpbBuff[2] = PopChar(p, i+2);
  cb.mpbBuff[3] = PopChar(p, i+3);

  return cb.dwBuff;
}


static err_t PopCode(struct pbuf *p)
{
  uchar *pb = p->payload;

  if (pb[p->len-3] != '|') return ERR_CODE;
  wCode = PopIntLtl(p, p->len-2);

  return ERR_OK;
}



void UDPOutput2(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  p->tot_len = GetPushSize();
  p->len = GetPushSize();

//  if (addr->addr == IPADDR_BROADCAST)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
//  else
//    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
}


// TODO
void UDPOutput(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
//  if (addr->addr == IPADDR_BROADCAST)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
//  else
//    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
}


static err_t UDP_OutError(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast, uchar bError)
{
  err_t err = InitPush(&p, 1+1);
  if (err != ERR_OK) return err;

  PushChar('?');
  PushChar(bError);

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t UDP_OutInfo(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = InitPush(&p, 1+6+4);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushArray(pbMAC,6);
  PushLongLtl(dwIP);

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t UDP_OutGetSettings(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = CheckSize(p, 1+1+1+2);
  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  err = PopCode(p);
  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  err = InitPush(&p, 1+4+4+4+2+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushLongLtl(dwIP);
  PushLongLtl(dwGateway);
  PushLongLtl(dwNetmask);
  PushIntLtl(wPort);
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t UDP_OutSetSettings(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = CheckSize(p, 1+1+4+4+4+2+1+2);
  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  err = PopCode(p);
  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  dwIP = PopLongLtl(p, 2);
  dwGateway = PopLongLtl(p, 6);
  dwNetmask = PopLongLtl(p, 10);
  wPort = PopIntLtl(p, 14);

  err = InitPush(&p, 1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}




err_t UDP_OutBegin(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = CheckSize(p,1+6+1+2);
  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  fActive = CheckMAC(p, 1);
  if (fActive == false) { return ERR_SKIP; }

  err = InitPush(&p, 1+1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}


err_t UDP_OutEnd(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = CheckSize(p,1+1+2);
  if (err != ERR_OK) { UDP_OutError(pcb,p,addr,port,broadcast,err); return err; }

  fActive = true;

  err = InitPush(&p, 1+1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}



// TODO
err_t UDP_OutUnknown(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  err_t err = InitPush(&p, 1);
  if (err != ERR_OK) return err;

  PushChar('?');

  UDPOutput(pcb,p,addr,port,broadcast);
  return ERR_OK;
}
