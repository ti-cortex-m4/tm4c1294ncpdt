/*------------------------------------------------------------------------------
UDP_OUT.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void InitUDP_Out(void);
bool IsActive_UDPOutput(void);

err_t UDPOut_MAC(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);

err_t UDPOut_GetLong3(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong dw1, ulong dw2, ulong dw3);
err_t UDPOut_SetLong3(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong *pdw1, ulong *pdw2, ulong *pdw3);

err_t UDPOut_Begin(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
err_t UDPOut_End(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);

err_t UDPOut_Unknown(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port);
