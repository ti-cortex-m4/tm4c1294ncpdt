/*------------------------------------------------------------------------------
MAX_REPEATS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "max_repeats.h"



// максимальное количество повторов при ошибках обмена со счетчиками
uchar                   bMaxRepeats;

cache const             chMaxRepeats = {MAX_REPEATS, &bMaxRepeats, sizeof(uchar)};



void    InitMaxRepeats(void)
{
  LoadCache(&chMaxRepeats);
  if ((bMaxRepeats <= 0) || (bMaxRepeats > 20))
  {
    bMaxRepeats = bMINORREPEATS;
    SaveCache(&chMaxRepeats);
  }
}


void    ResetMaxRepeats(void)
{
  bMaxRepeats = bMINORREPEATS;
  SaveCache(&chMaxRepeats);
}


uchar   GetMaxRepeats(void)
{
  return bMaxRepeats;
}
