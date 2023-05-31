/*------------------------------------------------------------------------------
realtime_indices.h


------------------------------------------------------------------------------*/

#ifndef __REALTIME_INDICES_H
#define __REALTIME_INDICES_H


#include "../main.h"


#define REALTIME_INDICES_SIZE   100


typedef struct
{
  time      tiCurr;

  uchar     ibSoftHou;
  uint      iwHardHou;

  uchar     ibSoftDay;
  uchar     ibHardDay;

  uchar     ibSoftMon;
  uchar     ibHardMon;
} realtime_indices;


#endif

/*
void    InitTimeoutHistogram35(void);
void    NextDayResetTimeoutHistogram35(void);

void    Timeout35(uint  wTimeout);

uchar   GetTimeoutDelta35(void);

void    OutTimeoutHistogramAll35(void);
void    OutResetTimeoutHistogramAll35(void);
void    OutResetTimeoutHistogramDay35(void);
*/
