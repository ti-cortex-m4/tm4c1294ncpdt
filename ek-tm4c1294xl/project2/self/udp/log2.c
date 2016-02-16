/*------------------------------------------------------------------------------
LOG2.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/inet.h"
#include "lwip/udp.h"
#include "../log/log_stdio.h"
#include "log2.h"



static void            *pcb;

static bool             enabled = true;

static uint             cwErrors1, cwErrors2;



void InitLog2(void)
{
#if true
  if (enabled)
  {
    pcb = udp_new();
  }
#endif
}



void Log2(uchar *pb, uint wSize)
{
#if true
  if (enabled)
  {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, wSize, PBUF_RAM);
    if (p == NULL)
    {
      cwErrors1++;
    }
    else
    {
      memcpy(p->payload, pb, wSize);

      err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, 50000);
      if (err != 0)
      {
        cwErrors2++;
      }
    }
  }
#endif
}


