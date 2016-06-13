/*------------------------------------------------------------------------------
udp_out,h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



extern uint                    cwErrUPDPushAlloc;
extern uint                    cwErrUPDPushSendUnicast;
extern uint                    cwErrUPDPushSendBroadcast;

err_t UDPOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
