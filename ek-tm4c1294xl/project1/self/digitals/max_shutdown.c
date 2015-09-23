/*------------------------------------------------------------------------------
MAX_SHUTDOWN!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "max_shutdown.h"



// максимальная длительность выключения счечтика (в получасах)
uint                    wMaxShutdown;

cache const             chMaxShutdown = {MAX_SHUTDOWN, &wMaxShutdown, sizeof(uint)};



void    InitMaxShutdown(void)
{
  LoadCacheInt(&chMaxShutdown, 48, 480, 480);
}


void    ResetMaxShutdown(void)
{
  SaveCacheInt(&chMaxShutdown, 480);
}


uint    GetMaxShutdown(void)
{
  return wMaxShutdown;
}
