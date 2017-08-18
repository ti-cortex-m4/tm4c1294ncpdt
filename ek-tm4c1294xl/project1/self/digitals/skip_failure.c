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



static bool             fSkipFailureEnbl;

cache const             chSkipFailureEnbl = {SKIP_FAILURE_ENBL, &fSkipFailureEnbl, sizeof(bool)};


static bool             fFailure;



void    InitSkipFailure(void)
{
  LoadCacheBool(&chSkipFailureEnbl, false);
}


void    ResetSkipFailure(void)
{
  SaveCacheBool(&chSkipFailureEnbl, false);
}



bool    SkipFailureEnbl(void) {
  return fSkipFailureEnbl;
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
  bool fResult = SkipFailureEnbl() & fFailure;
  if (fResult)
  {
    ShowLo("быстрый пропуск ");
    DelayInf();
  }

  return fResult;
}
