/*------------------------------------------------------------------------------
LOG2.Ñ


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/inet.h"
#include "lwip/udp.h"
#include "log2.h"



static void            *pcb;

static bool             enabled = false;

static uint             cwErrors1, cwErrors2;

//char                    mbLog2[1000];



void InitLog2(void)
{
#if false
  if (enabled)
  {
    pcb = udp_new();
  }
#endif
}



void Log2(const char *sz)
{
#if false
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
#endif
}

/*
void Log3(const char *sz, ...)
{
    va_list vaArgP;

    // Start the varargs processing.
    va_start(vaArgP, sz);

//    UARTvprintf(pcString, vaArgP);
	sprintf(mbLog2, sz, vaArgP);

    // We're finished with the varargs now.
    va_end(vaArgP);

    Log2(mbLog2);
}
*/
