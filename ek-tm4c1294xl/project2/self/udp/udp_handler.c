/*------------------------------------------------------------------------------
UDP_HANDLER.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/udp.h"
#include "udp_in_tibbo.h"
#include "udp_out.h"
#include "udp_handler.h"



void    InitUDP_Handler(void)
{
  InitUDP_Out();

  void *pcb = udp_new();
  udp_recv(pcb, UDP_InTibbo, NULL);
  udp_bind(pcb, IP_ADDR_ANY, 0xFFFF);
}
