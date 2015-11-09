/*------------------------------------------------------------------------------
UDP_HANDLER.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
//#include "../delay.h"
//#include <stdint.h>
//#include "utils/locator.h"
#include "utils/lwiplib_patched.h"
//#include "driverlib/sysctl.h"
//#include "lwip/udp.h"
//#include "../delay.h"
//#include "driverlib/sysctl.h"
//#include <self/udp/udp_out.h>
#include "udp_in.h"
#include "udp_handler.h"



void    InitUDP_Handler(void)
{
  void *pcb = udp_new();
  udp_recv(pcb, UDP_In, NULL);
  udp_bind(pcb, IP_ADDR_ANY, 0xFFFF);
}
