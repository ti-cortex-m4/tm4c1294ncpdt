/*------------------------------------------------------------------------------
buzz.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/led.h"
#include "../hardware/delay.h"
#include "../kernel/wrappers.h"
#include "udp_pop.h"
#include "udp_out.h"
#include "buzz.h"



static void Buzz(void)
{
  InitLEDs();

  uchar i;
  for (i=0; i<10; i++)
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


err_t OutBuzz(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast)
{
  uint2 wSfx = PopSfx(p);
  if (InvalidInt2(wSfx)) return wSfx.err;

  Buzz();

  InitPush();
  PushChar('A');
  PushSfx(wSfx.w);

  return Out(pcb,p,addr,port,broadcast);
}
