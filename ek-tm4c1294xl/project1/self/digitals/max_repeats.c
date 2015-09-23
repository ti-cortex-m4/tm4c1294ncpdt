/*------------------------------------------------------------------------------
MAX_REPEATS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "max_repeats.h"



// максимальное количество повторов при ошибках обмена со счетчиками
uchar                   bMaxRepeats;

cache const             chMaxRepeats = {MAX_REPEATS, &bMaxRepeats, sizeof(uchar)};



void    InitMaxRepeats(void)
{
  LoadCacheChar(&chMaxRepeats, 1, 20, bMINORREPEATS);
}


void    ResetMaxRepeats(void)
{
  SaveCacheChar(&chMaxRepeats, bMINORREPEATS);
}


uchar   GetMaxRepeats(void)
{
  return bMaxRepeats;
}
