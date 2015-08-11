/*------------------------------------------------------------------------------
NEXT_YEAR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../time/decret.h"



void    NextYear(void)
{
  Realtime1.cwYears++;

  MakeDecret();
}
