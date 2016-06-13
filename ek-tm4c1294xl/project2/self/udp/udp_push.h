/*------------------------------------------------------------------------------
udp_push.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"
#include "udp_push_number.h"



extern uint                    cwErrUPDPushOverflow;



void InitPush(void);
void PushChar(uchar b);
void PushString(const char *sz);
void PushBuff(buff bf);

void PushIP(ulong dw);
void PushMAC(uchar *pb, uchar bSize);
void PushSuffix(uint w);

err_t UDPOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
