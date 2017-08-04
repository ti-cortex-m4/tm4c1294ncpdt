/*------------------------------------------------------------------------------
ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "esc.h"



cache const             chMachinesEsc = {MACHINES_ESC, &bMachinesEsc, sizeof(uchar)};
cache const             chBlockEsc = {BLOCK_ESC, &boBlockEsc, sizeof(bool)};



void    InitEsc(void)
{
  LoadCacheChar(&chMachinesEsc, 1, bMAXMACHINES, bMAXMACHINES);
  LoadCacheBool(&chBlockEsc, false);
}


void    ResetEsc(void)
{
  bMachinesEsc = bMAXMACHINES;
  SaveCache(&chMachinesEsc);

  boBlockEsc = false;
  SaveCache(&chBlockEsc);
}
