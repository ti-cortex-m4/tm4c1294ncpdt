/*------------------------------------------------------------------------------
UDP_PUSH,H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void InitPush(void);
void PushChar(uchar b);
//void PushIntLtl(uint w);
//void PushLongLtl(ulong dw);
void PushString(const char *sz);
void PushBuff(buff bf);
uchar PushCharDec(uchar b);
//uchar PushCharHex(uchar b);
uchar PushIntDec(uint w);
uchar PushIntHex(uint w);
void PushIP(ulong dw);
void PushSfx(uint w);
//void PushArray(uchar *pb, uchar bSize);
void PushArrayString(uchar *pb, uchar bSize);

err_t PushOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
