/*------------------------------------------------------------------------------
udp_out.h


------------------------------------------------------------------------------*/

#include "udp_push.h"
#include "udp_push_numbers.h"



extern uint                    cwErrUPDOutPbufAlloc;
extern uint                    cwErrUPDOutSendUnicast;
extern uint                    cwErrUPDOutSendBroadcast;



err_t Out(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast);
