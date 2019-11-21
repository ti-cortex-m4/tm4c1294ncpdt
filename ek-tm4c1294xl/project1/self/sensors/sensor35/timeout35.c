/*------------------------------------------------------------------------------
timeout35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "timeout35.h"



static uint             mwTimeoutHistogramAbs35[0x100],
                        mwTimeoutHistogramDay35[0x100];



void    InitTimeoutHistogram35(void)
{
  memset(&mwTimeoutHistogramAbs35, 0, sizeof(mwTimeoutHistogramAbs35));
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));
}


void    NextDayResetTimeoutHistogram35(void)
{
  memset(&mwTimeoutHistogramDay35, 0, sizeof(mwTimeoutHistogramDay35));
}



void    TimeoutHistogram35(uint  wTimeout)
{
  uchar i = wTimeout < 0x100 ? wTimeout : 0xFF;

  mwTimeoutHistogramAbs35[i]++;
  mwTimeoutHistogramDay35[i]++;
}



void    OutTimeoutHistogramAll35(void)
{
  InitPushCRC();
  Push(&mwTimeoutHistogramAbs35, sizeof(mwTimeoutHistogramAbs35));
  Push(&mwTimeoutHistogramDay35, sizeof(mwTimeoutHistogramDay35));
  Output(sizeof(mwTimeoutHistogramAbs35)+sizeof(mwTimeoutHistogramDay35));
}


void    OutResetTimeoutHistogramAll35(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    InitTimeoutHistogram35();
    LongResult(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}


void    OutResetTimeoutHistogramDay35(void)
{
  if (enGlobal == GLB_REPROGRAM)
  {
    NextDayResetTimeoutHistogram35();
    LongResult(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}
