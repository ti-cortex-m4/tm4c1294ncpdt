/*------------------------------------------------------------------------------
udp_entities.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



bool AreEnities(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port, u8_t broadcast);
