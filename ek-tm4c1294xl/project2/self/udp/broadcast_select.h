/*------------------------------------------------------------------------------
broadcast_select.h


------------------------------------------------------------------------------*/

extern bool                    fBroadcastSelect;



void OutBroadcastSelect(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast);
