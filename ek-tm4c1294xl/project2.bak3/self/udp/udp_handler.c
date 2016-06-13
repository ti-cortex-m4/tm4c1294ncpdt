/*------------------------------------------------------------------------------
udp_handler.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/udp.h"
#include "udp_in.h"
#include "udp_handler.h"



void InitUdpHandler(void)
{
  void *pcb = udp_new();
  udp_recv(pcb, UdpInput, NULL);
  udp_bind(pcb, IP_ADDR_ANY, 0xFFFF);
}