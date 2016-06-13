/*------------------------------------------------------------------------------
udp_out_controls.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



extern const uint wControlsSize;



err_t OutFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
