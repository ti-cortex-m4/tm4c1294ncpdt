/*------------------------------------------------------------------------------
skip_failure.c

Быстрый пропуск опроса отказавшего цифрового счетчика
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "skip_failure.h"



static bool             fSkipFailure;

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



bool    SkipFailureEnbl(void) {
  return fSkipFailure;
}



void    SkipFailure_Start(void)
{
  SkipFailure_Success();
}


void    SkipFailure_Success(void)
{
  fFailure = false;
}


void    SkipFailure_Failure(void)
{
  fFailure = true;
}


bool    SkipFailure_IsFailure(void)
{
  bool fResult = fFailure & fSkipFailure;

  if (fResult)
  {
    SaveDisplay();

    ShowLo("быстрый пропуск ");
    DelayInf();

    LoadDisplay();
  }

  return fResult;
}
