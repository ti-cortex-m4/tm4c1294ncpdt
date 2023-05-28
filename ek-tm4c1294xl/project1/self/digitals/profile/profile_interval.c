/*------------------------------------------------------------------------------
profile_interval.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "profile_interval.h"



bool                    boProfileInterval;
cache const             chProfileInterval = {PROFILE_INTERVAL, &boProfileInterval, sizeof(bool)};

uchar                   bProfileIntervalDirect;
cache const             chProfileIntervalDirect = {PROFILE_INTERVAL_DIRECT, &bProfileIntervalDirect, sizeof(uchar)};

uchar                   bProfileIntervalModem;
cache const             chProfileIntervalModem = {PROFILE_INTERVAL_MODEM, &bProfileIntervalModem, sizeof(uchar)};



uchar                   ibProfileIntervalDig;



void    InitProfileInterval(void)
{
  LoadCacheBool(&chProfileInterval, true);
  LoadCacheChar(&chProfileIntervalDirect, 1, 250, 60);
  LoadCacheChar(&chProfileIntervalModem, 1, 250, 180);

  ibProfileIntervalDig = 0xFF;
}


void    ResetProfileInterval(void)
{
  SaveCacheBool(&chProfileInterval, true);
  SaveCacheChar(&chProfileIntervalDirect, 60);
  SaveCacheChar(&chProfileIntervalModem, 180);
}



uchar   GetProfileIntervalTimeout(void)
{
  return diCurr.ibPhone == 0 ? bProfileIntervalDirect : bProfileIntervalModem;
}


bool    IsFinishedProfileInterval(void)
{
  return ((tiCurr.bMinute % 30)*60 + tiCurr.bSecond >= (uint)30*60 - GetProfileIntervalTimeout());
}
