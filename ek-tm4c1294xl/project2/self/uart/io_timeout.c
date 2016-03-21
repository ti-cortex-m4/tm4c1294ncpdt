/*------------------------------------------------------------------------------
io_timeout.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/entities_default.h"
#include "../kernel/settings.h"
#include "io_mode.h"
#include "io_timeout.h"



static const ulong      mdwBaudRateTimeouts[BAUD_RATE_COUNT] = {6667, 3333, 1667, 833, 417, 208, 104, 62, 35, 26, 17, 7, 4, 2}; // microseconds
static ulong            mdwTimeouts[UART_COUNT];



void InitIOTimeouts(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mdwTimeouts[u] = 0;
  }
}



void SetIOTimeout(uchar u)
{
  ASSERT(u < UART_COUNT);

  uchar ibBaudRate = mibBaudRate[u];
  ASSERT(ibBaudRate < BAUD_RATE_COUNT);

  ulong dwTimeout = mdwBaudRateTimeouts[ibBaudRate] / 10;
  if (dwTimeout == 0) dwTimeout = 1;

  mdwTimeouts[u] = dwTimeout;
}



void TimerIOTimeout(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mdwTimeouts[u] > 0)
    {
      if (--mdwTimeouts[u] == 0)
      {
        InputMode(u);
      }
    }
  }
}