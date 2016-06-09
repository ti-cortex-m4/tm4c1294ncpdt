/*------------------------------------------------------------------------------
routing_status.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "routing_status.h"



bool IsRoutingStatusSize(struct pbuf *p) {
  return false;
}


err_t GetRouingStatusSize(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  return ERR_OK;
}



bool IsRoutingStatusContent(struct pbuf *p) {
  return false;
}


err_t GetRouingStatusContent(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast) {
  return ERR_OK;
}
