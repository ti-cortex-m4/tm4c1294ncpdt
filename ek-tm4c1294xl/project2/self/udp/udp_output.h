/*------------------------------------------------------------------------------
UDP_OUTPUT.H


------------------------------------------------------------------------------*/

void Init_UDPOutput(void);
bool IsActive_UDPOutput(void);

err_t UDPOutput_MAC(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);

err_t UDPOutput_GetLong(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong dw);
err_t UDPOutput_Set3Long(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong *pdw1, ulong *pdw2, ulong *pdw3);

err_t UDPOutput_Begin(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
err_t UDPOutput_End(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);

err_t UDPOutput_Unknown(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
