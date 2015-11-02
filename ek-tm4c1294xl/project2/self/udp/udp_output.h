/*------------------------------------------------------------------------------
UDP_OUTPUT.H


------------------------------------------------------------------------------*/

err_t UDPOutputX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);

err_t UDPOutputIP(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
err_t UDPOutputGateway(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
err_t UDPOutputNetmask(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
