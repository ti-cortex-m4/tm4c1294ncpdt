/*------------------------------------------------------------------------------
UDP_OUTPUT.H


------------------------------------------------------------------------------*/

void Init_UDPOutput(void);
bool IsActive_UDPOutput(void);

err_t UDPOutputM(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);

err_t UDPOutput_GetLong(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong dw);
err_t UDPOutput_SetLong(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong *pdw);

err_t UDPOutputB(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
err_t UDPOutputE(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
