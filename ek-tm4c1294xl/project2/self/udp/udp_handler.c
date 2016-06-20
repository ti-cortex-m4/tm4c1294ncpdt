/*------------------------------------------------------------------------------
udp_handler.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_in.h"
#include "udp_handler.h"



void InitUDPHandler(void)
{
  void *pcb = udp_new();
  udp_recv(pcb, UDPInput, NULL);
  udp_bind(pcb, IP_ADDR_ANY, 0xFFFF);
}
