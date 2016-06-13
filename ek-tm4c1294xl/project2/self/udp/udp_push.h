/*------------------------------------------------------------------------------
UDP_PUSH,H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void InitPush(void);
void PushChar(uchar b);
void PushString(const char *sz);
void PushArrayString(uchar *pb, uchar bSize);
void PushBuff(buff bf);
uchar PushCharDec(uchar b);
uchar PushIntDec(uint w);
uchar PushIntHex(uint w);
void PushIP(ulong dw);
void PushSfx(uint w);

err_t PushOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
