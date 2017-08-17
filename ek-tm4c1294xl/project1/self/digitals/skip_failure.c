/*------------------------------------------------------------------------------
skip_failure.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "skip_failure.h"



bool                    fSkipFailure;

cache const             chSkipFailure = {SKIP_FAILURE, &fSkipFailure, sizeof(bool)};



void    InitSkipFailure(void)
{
  LoadCacheBool(&chSkipFailure, false);
}


void    ResetSkipFailure(void)
{
  SaveCacheBool(&chSkipFailure, false);
}
