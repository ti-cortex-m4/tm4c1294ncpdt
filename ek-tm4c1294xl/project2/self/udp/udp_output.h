/*------------------------------------------------------------------------------
UDP_OUTPUT.H


------------------------------------------------------------------------------*/

void SetMAC(uchar *pb);

err_t UDPOutputX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
