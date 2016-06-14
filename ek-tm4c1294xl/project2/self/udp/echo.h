/*------------------------------------------------------------------------------
echo.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



err_t CmdX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
