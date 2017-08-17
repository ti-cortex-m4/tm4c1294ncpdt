/*------------------------------------------------------------------------------
skip_failure.c

Быстрый пропуск опроса отказавшего цифрового счетчика
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "skip_failure.h"



bool                    fSkipFailure;

cache const             chSkipFailure = {SKIP_FAILURE, &fSkipFailure, sizeof(bool)};


static bool             fFailure;



void    InitSkipFailure(void)
{
  LoadCacheBool(&chSkipFailure, false);
}


void    ResetSkipFailure(void)
{
  SaveCacheBool(&chSkipFailure, false);
}



void   SkipFailure_Start(void)
{
  fFailure = false;
}


void   SkipFailure_Failure(void)
{
  fFailure = true;
}


bool   SkipFailure_IsFailure(void)
{
  return fFailure;
}
