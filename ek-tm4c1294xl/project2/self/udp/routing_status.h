/*------------------------------------------------------------------------------
routing_status.h


------------------------------------------------------------------------------*/

void NextRoutingStatus(void);

bool IsRoutingStatusSize(struct pbuf *p);
err_t GetRoutingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast);

bool IsRoutingStatusContent(struct pbuf *p);
err_t GetRoutingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast);
