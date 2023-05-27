/*------------------------------------------------------------------------------
profile_interval.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "profile_interval.h"



bool                    boProfileInterval;
cache const             chProfileInterval = {PROFILE_INTERVAL, &boProfileInterval, sizeof(bool)};
uchar                   ibProfileIntervalDig;



void    InitProfileInterval(void)
{
  LoadCacheBool(&chProfileInterval, true);
  ibProfileIntervalDig = 0xFF;
}


void    ResetProfileInterval(void)
{
  SaveCacheBool(&chProfileInterval, true);
}



uchar   GetProfileIntervalTimeout(void)
{
  return diCurr.ibPhone == 0 ? 30 : 120;
}


bool    IsStopProfileInterval(void)
{
  uchar bTimeout = GetProfileIntervalTimeout();
  return ((tiCurr.bMinute % 30)*60 + tiCurr.bSecond >= (uint)30*60 - bTimeout);
}
