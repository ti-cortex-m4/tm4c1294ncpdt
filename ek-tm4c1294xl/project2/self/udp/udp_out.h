/*------------------------------------------------------------------------------
udp_out,h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"
#include "udp_push.h"
#include "udp_push_numbers.h"



extern uint                    cwErrUPDPushAlloc;
extern uint                    cwErrUPDPushSendUnicast;
extern uint                    cwErrUPDPushSendBroadcast;

err_t UDPOut(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
