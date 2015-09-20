/*------------------------------------------------------------------------------
WDT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_program.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../hardware/watchdog.h"
#include "wdt.h"



cache const             chEnblWDT = {ENBL_WDT, &boEnblWatchdog, sizeof(bool)};



void    InitWDT(void)
{
  LoadCache(&chEnblWDT);

  if (boEnblWatchdog == true)
  {
    EnableWatchdog();
  }
}


void    ResetWDT(bool  fFull)
{
  if (fFull)
  {
    SaveCacheBool(&chEnblWDT, true);
  }
}
