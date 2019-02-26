/*------------------------------------------------------------------------------
profile_frac8.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "profile_frac8.h"



bool    SaveProfileFrac8(uint  c)
{
  ASSERT(c < bCANALS);
  return SaveArrayX(PROFILE_FRAC_8, sizeof(mpdbEngFracDigCan8[0]), c, mpdbEngFracDigCan8[c]);
}


bool    LoadProfileFrac8(uint  c)
{
  ASSERT(c < bCANALS);
  return LoadArrayX(PROFILE_FRAC_8, sizeof(mpdbEngFracDigCan8[0]), c, mpdbEngFracDigCan8[c]);
}



void    SaveProfileFrac8_All(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    SaveProfileFrac8(c);
  }
}


void    LoadProfileFrac8_All(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadProfileFrac8(c);
  }
}
