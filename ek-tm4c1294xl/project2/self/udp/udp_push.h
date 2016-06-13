/*------------------------------------------------------------------------------
udp_push.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



extern uint                    cwErrUPDPushOverflow;



void InitPush(void);
void PushChar(uchar b);
void PushString(const char *sz);
void PushBuff(buff bf);
uchar PushCharDec(uchar b);
uchar PushIntDec(uint w);
uchar PushIntHex(uint w);
void PushIP(ulong dw);
void PushArrayString(uchar *pb, uchar bSize);
void PushSuffix(uint w);

err_t UDPOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
