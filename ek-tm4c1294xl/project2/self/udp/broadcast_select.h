/*------------------------------------------------------------------------------
broadcast_select.h


------------------------------------------------------------------------------*/

extern bool                    fBroadcastSelect;



void OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast);
