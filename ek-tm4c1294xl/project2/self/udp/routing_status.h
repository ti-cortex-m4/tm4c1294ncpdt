/*------------------------------------------------------------------------------
routing_status.h


------------------------------------------------------------------------------*/

void NextRouingStatus(void);

bool IsRoutingStatusSize(struct pbuf *p);
err_t GetRouingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);

bool IsRoutingStatusContent(struct pbuf *p);
err_t GetRouingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
