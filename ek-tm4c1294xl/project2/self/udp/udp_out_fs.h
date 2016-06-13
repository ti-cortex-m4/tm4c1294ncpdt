/*------------------------------------------------------------------------------
udp_out_fs.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t OutFS(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
