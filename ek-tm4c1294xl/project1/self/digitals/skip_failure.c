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


uchar   SkipFailureRepeats(void) {
  return bSkipFailureRepeats;
}



void    SkipFailure_BeforeExtended(void) {
  fFailure = false;
  fFirstQuery = true;
}


void    SkipFailure_AfterExtended(void) {
  fFailure = true;
}



void    SkipFailure_InputStart(void) {
  fFailure = true;
}


void    SkipFailure_InputGoodCheck(void) {
  fFailure = false;
  fFirstQuery = false;
}



bool    SkipFailure_IsFailure(void) {
  return SkipFailureEnbl() & fFailure;
}


bool    SkipFailure_IsFailureMsg(void) {
  bool f = SkipFailure_IsFailure();

  if (f) {
    ShowLo("быстрый пропуск ");
    DelayInf();
  }

  return f;
}



bool    SkipFailure_IsReducedRepeats(void) {
  return SkipFailureEnbl() & fFirstQuery;
}
