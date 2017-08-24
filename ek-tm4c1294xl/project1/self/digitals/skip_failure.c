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

static uchar            bSkipFailureRepeats;
cache const             chSkipFailureRepeats = {SKIP_FAILURE_REPEATS, &bSkipFailureRepeats, sizeof(uchar)};


static bool             fFirstQuery;
static bool             fFailure;



void    InitSkipFailure(void) {
  LoadCacheBool(&chSkipFailureEnbl, false);
  LoadCacheChar(&chSkipFailureRepeats, 1, 5, 2);
}


void    ResetSkipFailure(void) {
  SaveCacheBool(&chSkipFailureEnbl, false);
  SaveCacheChar(&chSkipFailureRepeats, 2);
}



bool    SkipFailureEnbl(void) {
  return fSkipFailureEnbl;
}



void    SkipFailure_BeforeExtended(void) {
  fFailure = false;
  fFirstQuery = true;
}


void    SkipFailure_AfterExtended(void) {
}



void    SkipFailure_InputStart(void) {
  fFailure = true;
}


void    SkipFailure_InputGoodCheck(void) {
  fFailure = false;
  fFirstQuery = false;
}



bool    SkipFailure_IsFailure(void) {
  bool fResult = SkipFailureEnbl() & fFailure;

  if (fResult) {
    ShowLo("быстрый пропуск ");
    DelayInf();
  }

  return fResult;
}



bool    SkipFailure_IsReducedRepeats(void) {
  return SkipFailureEnbl() & fFirstQuery;
}


uchar   MaxRepeatsSkipFailure(void) {
  return bSkipFailureRepeats;
}
