/*------------------------------------------------------------------------------
test_watchdog.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void TestWatchdog(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
