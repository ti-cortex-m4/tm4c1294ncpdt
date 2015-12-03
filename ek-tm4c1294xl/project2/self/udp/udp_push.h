/*------------------------------------------------------------------------------
UDP_PUSH.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void InitPush(void);
void PushChar(uchar b);
void PushIntLtl(uint w);
void PushLongLtl(ulong dw);
void PushString(const char *sz);
uchar PushIntHex(uint w);
uchar PushCharDec(uchar b);
void PushIP(ulong dw);
void PushSfx(uint w);
void PushArray(uchar *pb, uchar bSize);
void PushArrayString(uchar *pb, uchar bSize);


err_t UDPOutput2(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
