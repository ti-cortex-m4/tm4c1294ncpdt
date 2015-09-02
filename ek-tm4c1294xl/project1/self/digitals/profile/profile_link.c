/*------------------------------------------------------------------------------
PROFILE_LINK.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "profile_link.h"



void    IncProfileLinkWrn(uchar  ibPrt, uchar  ibHhr)
{
  ASSERT(ibPrt < bPORTS);
  ASSERT(ibHhr < 48);
  mpcwProfileLinkWrn[ibPrt][ibHhr]++;
}


void    IncProfileLinkErr(uchar  ibPrt, uchar  ibHhr)
{
  ASSERT(ibPrt < bPORTS);
  ASSERT(ibHhr < 48);
  mpcwProfileLinkErr[ibPrt][ibHhr]++;
}
