/*------------------------------------------------------------------------------
timeout35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "timeout35.h"



static uint             mwTimeoutHistogramAbs35[0x100],
                        mwTimeoutHistogramDay35[0x100];



void    ResetTimeoutHistogramAll35(void)
{
  memset(&mwTimeoutHistogramAbs35, 0, sizeof(mwTimeoutHistogramAbs35));
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));
}


void    ResetTimeoutHistogramDay35(void)
{
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));
}



void    TimeoutHistogramDay35(uint  wTimeout)
{
  uchar i = wTimeout < 0x100 ? wTimeout : 0xFF;

  mwTimeoutHistogramAbs35[i]++;
  mwTimeoutHistogramDay35[i]++;
}
