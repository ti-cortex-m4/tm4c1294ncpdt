/*------------------------------------------------------------------------------
udp_out_common.h


------------------------------------------------------------------------------*/

err_t OutStringZ(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const char *pcsz);
err_t OutBuff(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const buff bf);
err_t OutCharDec(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const uchar b);
err_t OutIntDec(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const uint w);
err_t OutIP(struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, uint port, uchar broadcast, const ulong dw);
