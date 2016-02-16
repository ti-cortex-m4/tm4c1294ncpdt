/*------------------------------------------------------------------------------
LOG2.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/inet.h"
#include "lwip/udp.h"
#include "log2.h"



static void            *pcb;

static bool             enabled = true;

static uint             cwErrors1, cwErrors2;



void InitLog2(void)
{
  if (enabled)
  {
    pcb = udp_new();
  }
}



void Log2(const char *sz)
{
  if (enabled)
  {
    uint wSize = strlen(sz);

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, wSize, PBUF_RAM);
    if (p == NULL)
    {
      cwErrors1++;
    }
    else
    {
      memcpy(p->payload, sz, wSize);

      err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, 50000);
      if (err != 0)
      {
        cwErrors2++;
      }
    }
  }
}
