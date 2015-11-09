/*------------------------------------------------------------------------------
UDP_OUTPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
//#include "lwip/udp.h"
//#include "lwip/ip_addr.h"
#include "udp_out.h"



static bool             fActive;
static uchar            *pbOut;
static uchar            ibOut;
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



static err_t InitPush(struct pbuf **pp, uchar bSize)
{
  *pp = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (pp == NULL) return ERR_MEM;

  pbOut = (*pp)->payload;
  ibOut = 0;

  return ERR_OK;
}


static void PushChar(uchar b)
{
  pbOut[ibOut++] = b;
}


static void PushIntLtl(uint w)
{
  PushChar(w % 0x100);
  PushChar(w / 0x100);
}


static void PushLongLtl(ulong dw)
{
  PushIntLtl(dw % 0x10000);
  PushIntLtl(dw / 0x10000);
}


static void PushMAC(uchar *pbMAC)
{
  PushChar(pbMAC[0]);
  PushChar(pbMAC[1]);
  PushChar(pbMAC[2]);
  PushChar(pbMAC[3]);
  PushChar(pbMAC[4]);
  PushChar(pbMAC[5]);
}


static void UDPOutput(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
//  if (addr->addr == IPADDR_BROADCAST)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
//  else
//    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
}


static err_t UDPOut_Error(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar bError)
{
  err_t err = InitPush(&p, 1+1);
  if (err != ERR_OK) return err;

  PushChar('?');
  PushChar(bError);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOut_MAC(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  err_t err = InitPush(&p, 1+6);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushMAC(pbMAC);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOut_GetLong3(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong dw1, ulong dw2, ulong dw3)
{
  err_t err = CheckSize(p, 1+1+1+2);
  if (err != ERR_OK) { UDPOut_Error(pcb, p, addr, port, err); return err; }

  err = PopCode(p);
  if (err != ERR_OK) { UDPOut_Error(pcb, p, addr, port, err); return err; }

  err = InitPush(&p, 1+4+4+4+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushLongLtl(dw1);
  PushLongLtl(dw2);
  PushLongLtl(dw3);
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOut_SetLong3(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong *pdw1, ulong *pdw2, ulong *pdw3)
{
  err_t err = CheckSize(p, 1+1+4+4+4+1+2);
  if (err != ERR_OK) { UDPOut_Error(pcb, p, addr, port, err); return err; }

  err = PopCode(p);
  if (err != ERR_OK) { UDPOut_Error(pcb, p, addr, port, err); return err; }

  *pdw1 = PopLongLtl(p, 2);
  *pdw2 = PopLongLtl(p, 6);
  *pdw3 = PopLongLtl(p, 10);

  err = InitPush(&p, 1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}




err_t UDPOut_Begin(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  err_t err = CheckSize(p,1+6+1+2);
  if (err != ERR_OK) { UDPOut_Error(pcb, p, addr, port, err); return err; }

  fActive = CheckMAC(p, 1);
  if (fActive == false) { return ERR_SKIP; }

  err = InitPush(&p, 1+1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOut_End(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  err_t err = CheckSize(p,1+1+2);
  if (err != ERR_OK) { UDPOut_Error(pcb, p, addr, port, err); return err; }

  fActive = true;

  err = InitPush(&p, 1+1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}



// TODO
err_t UDPOut_Unknown(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  err_t err = InitPush(&p, 1);
  if (err != ERR_OK) return err;

  PushChar('?');

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}
