/*------------------------------------------------------------------------------
MAX_REPEATS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "skip_failure.h"
#include "max_repeats.h"



// максимальное количество повторов при ошибках обмена со счетчиками
uchar                   bMaxRepeats;

cache const             chMaxRepeats = {MAX_REPEATS, &bMaxRepeats, sizeof(uchar)};



void    InitMaxRepeats(void)
{
  LoadCacheChar(&chMaxRepeats, 1, 20, bREPEATS);
}


void    ResetMaxRepeats(void)
{
  SaveCacheChar(&chMaxRepeats, bREPEATS);
}



uchar   MaxRepeats(void)
{
  return SkipFailure_IsReducedRepeats() ? MaxRepeatsSkipFailure() : MaxRepeatsFixed();
}


uchar   MaxRepeatsFixed(void)
{
  return bMaxRepeats;
}
