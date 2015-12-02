/*------------------------------------------------------------------------------
UDP_OUT.H


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void InitUDP_Out(void);
bool IsActive_UDPOutput(void);

err_t PopCode2(struct pbuf *p, uint *pw);
err_t PopNumber(struct pbuf *p, uchar x, uint *pw);

void UDPOutput2(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);

err_t UDP_OutInfo(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);

err_t UDP_OutGetSettings(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
err_t UDP_OutSetSettings(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);

err_t UDP_OutBegin(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
err_t UDP_OutEnd(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);

err_t UDP_OutUnknown(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
