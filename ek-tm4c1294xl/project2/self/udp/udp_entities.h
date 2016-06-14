/*------------------------------------------------------------------------------
udp_entities,h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



bool IsEnity(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast, entity const *pen);
