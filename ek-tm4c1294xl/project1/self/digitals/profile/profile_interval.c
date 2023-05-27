/*------------------------------------------------------------------------------
profile_interval.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_digitals.h"
//#include "../../flash/files.h"
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
