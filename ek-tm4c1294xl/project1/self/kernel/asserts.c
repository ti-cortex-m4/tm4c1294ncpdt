/*------------------------------------------------------------------------------
ASSERTS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../time/rtc.h"
#include "asserts.h"



ulong                   dwAssertsIdx;
assert                  mpAsserts[ASSERTS_SIZE];

cache const             chAssertsIdx = {ASSERTS_IDX, &dwAssertsIdx, sizeof(ulong)};
cache const             chAsserts = {ASSERTS, &mpAsserts, sizeof(mpAsserts)};



void    InitAsserts(void)
{
  LoadCache(&chAssertsIdx);
  LoadCache(&chAsserts);
}


void    ResetAsserts(void)
{
	dwAssertsIdx = 0;
  SaveCache(&chAssertsIdx);

  memset(&mpAsserts, 0, sizeof(mpAsserts));
  SaveCache(&chAsserts);
}



void    AddAssert(char  *pcFileName, ulong  dwLine)
{
  uchar i = dwAssertsIdx % ASSERTS_SIZE;

  dwAssertsIdx++;
  SaveCache(&chAssertsIdx);

  mpAsserts[i].iwEvent = i;
  mpAsserts[i].tiEvent = *GetCurrTimeDate();
  mpAsserts[i].dwLine = dwLine;

  memset(&mpAsserts[i].szFileName, 0, FILE_NAME_SIZE);
  strncpy(mpAsserts[i].szFileName, pcFileName, FILE_NAME_SIZE);

  SaveCache(&chAsserts);
}



void    OutAsserts(void)
{
  InitPushCRC();

  PushLong(dwAssertsIdx);

  uchar i;
  for (i=0; i<ASSERTS_SIZE; i++)
  {
    PushInt(mpAsserts[i].iwEvent);
    PushTime(mpAsserts[i].tiEvent);
    PushLong(mpAsserts[i].dwLine);
    Push(mpAsserts[i].szFileName, FILE_NAME_SIZE);
  }

  Output(4+sizeof(mpAsserts));
}
