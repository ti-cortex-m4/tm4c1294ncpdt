/*------------------------------------------------------------------------------
udp_out_controls.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t OutControls(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
