/*------------------------------------------------------------------------------
udp_entities.h


------------------------------------------------------------------------------*/

bool IsSomeEnity(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port, u8_t broadcast);
