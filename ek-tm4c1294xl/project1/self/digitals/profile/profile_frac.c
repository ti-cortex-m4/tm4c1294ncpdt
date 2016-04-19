/*------------------------------------------------------------------------------
PROFILE_FRAC!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "profile_frac.h"



bool    SaveProfileFrac6(uint  c)
{
  ASSERT(c < bCANALS);
  return SaveArrayX(PROFILE_FRAC_6, sizeof(mpdbEngFracDigCan[0]), c, mpdbEngFracDigCan[c]);
}


bool    LoadProfileFrac6(uint  c)
{
  ASSERT(c < bCANALS);
  return LoadArrayX(PROFILE_FRAC_6, sizeof(mpdbEngFracDigCan[0]), c, mpdbEngFracDigCan[c]);
}



void    SaveProfileFrac6_All(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    SaveProfileFrac6(c);
  }
}


void    LoadProfileFrac6_All(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadProfileFrac6(c);
  }
}
