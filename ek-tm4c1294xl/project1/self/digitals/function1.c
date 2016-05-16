/*------------------------------------------------------------------------------
!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "function1.h"



cache const             chDsblAnswer = {DSBL_ANSWER, &fDsblAnswer, sizeof(bool)};



void    InitFunction1(void)
{
  LoadCacheBool(&chDsblAnswer, false);
}


void    ResetFunction1(void)
{
  SaveCacheBool(&chDsblAnswer, false);
}
