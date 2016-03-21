/*------------------------------------------------------------------------------
io_timeout.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/entities_default.h"
#include "../kernel/settings.h"
#include "io_mode.h"
#include "io_timeout.h"



static const uint       mwBaudRateTimeouts[BAUD_RATE_COUNT] = {6667, 3333, 1667, 833, 417, 208, 104, 62, 35, 26, 17, 7, 4, 2}; // microseconds
static uint             mwTimeouts[UART_COUNT];



void InitIOTimeouts(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    mwTimeouts[u] = 0;
  }
}



void SetIOTimeout(uchar u)
{
  ASSERT(u < UART_COUNT);

  uchar ibBaudRate = mibBaudRate[u];
  ASSERT(ibBaudRate < BAUD_RATE_COUNT);

  uint wTimeout = mwBaudRateTimeouts[ibBaudRate] / 10;
  if (wTimeout == 0) wTimeout = 1;

  mwTimeouts[u] = wTimeout;
}



void TimerIOTimeout(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mwTimeouts[u] > 0)
    {
      if (--mwTimeouts[u] == 0)
      {
        InMode(u);
      }
    }
  }
}
