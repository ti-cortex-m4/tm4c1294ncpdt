/*------------------------------------------------------------------------------
buzz.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/led.h"
#include "../hardware/delay.h"
#include "../kernel/wrappers.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "routing_status.h"
#include "buzz.h"



static void Buzz(void)
{
  InitLEDs();

  uchar i;
  for (i=0; i<8; i++)
  {
    OffLED0();
    OnLED1();
    DelayMilliSecond(100);

    OnLED0();
    OffLED1();
    DelayMilliSecond(100);
  }

  InitEthernetLEDs();
}


err_t OutBuzz(struct udp_pcb *pcb, struct pbuf *p, struct ip4_addr *addr, uint port, uchar broadcast)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  err_t err = Out(pcb,p,addr,port,broadcast);

  NextRoutingStatus();
  Buzz();

  return err;
}
