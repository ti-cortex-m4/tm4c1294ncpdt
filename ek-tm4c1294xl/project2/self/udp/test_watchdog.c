/*------------------------------------------------------------------------------
test_watchdog.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/log.h"
#include "udp_out.h"
#include "test_watchdog.h"



void TestWatchdog(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast)
{
  if (broadcast == 0)
  {
    CONSOLE("test watchdog\n");

    InitPush();
    PushChar('A');
    Out(pcb,p,addr,port,broadcast);

    while (1);
  }
}
