/*------------------------------------------------------------------------------
broadcast_select.h


------------------------------------------------------------------------------*/

extern bool                    fBroadcastSelect;



void OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
