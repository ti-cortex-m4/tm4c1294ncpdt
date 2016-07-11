/*------------------------------------------------------------------------------
broadcast_select.h


------------------------------------------------------------------------------*/

err_t OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
